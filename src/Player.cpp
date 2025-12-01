#include "Player.h"

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/input_event_joypad_motion.hpp>
#include <godot_cpp/classes/physics_direct_space_state3d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters3d.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/world3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/viewport.hpp>

#include "InputManager.h"
#include "MouseMarker.h"

// Skills
#include "Skills/SkillFireCone.h"

using namespace godot;

void Player::_bind_methods() 
{
  ClassDB::bind_method(D_METHOD("getMarkerScenePath"), &Player::getMarkerScenePath);
  ClassDB::bind_method(D_METHOD("setMarkerScenePath", "path"), &Player::setMarkerScenePath);

  ClassDB::bind_method(D_METHOD("setMoveButton", "button"), &Player::setMoveButton);
  ClassDB::bind_method(D_METHOD("getMoveButton"), &Player::getMoveButton);

  ClassDB::bind_method(D_METHOD("GetSkillSet"), &Player::GetSkillSet);
  ClassDB::bind_method(D_METHOD("SetSkillSet", "skillSet"), &Player::SetSkillSet);

  ClassDB::bind_method(D_METHOD("OnSkillInSet", "skillResource"), &Player::OnSkillInSet);

  ADD_PROPERTY(PropertyInfo(Variant::STRING, "markerScenePath"), 
               "setMarkerScenePath", "getMarkerScenePath");

  ADD_PROPERTY(PropertyInfo(Variant::INT, 
               "moveButton", 
               PROPERTY_HINT_ENUM, 
               "Left:1,Right:2,Middle:3"), 
               "setMoveButton", 
               "getMoveButton");


  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
                            "skillSet",
                            PROPERTY_HINT_RESOURCE_TYPE, 
                            "SkillSet"), 
               "SetSkillSet", "GetSkillSet");
}

void Player::_ready()
{
  m_collider = get_node<CollisionShape3D>("CollisionShape3D");
  m_camera = get_node<Camera3D>("../CameraController");
  m_animationPlayer = get_node<AnimationPlayer>("Model/AnimationPlayer");

  // Load resources
  m_resourceMarkerScene = ResourceLoader::get_singleton()->load(m_markerScenePath);
  if (!m_resourceMarkerScene.is_valid())
  {
    UtilityFunctions::push_warning("No Marker resource");
    return;
  }
  m_targetMarker = Object::cast_to<MouseMarker>(m_resourceMarkerScene->instantiate());
  if (!m_targetMarker)
  {
    UtilityFunctions::push_warning("Could not instance Marker scene");
    return;
  }

  SceneTree* tree = get_tree();
  if (tree)
  {
    tree->get_current_scene()->call_deferred("add_child", m_targetMarker);
  }

  // Check happens inside getGlobalInputManager so if it fails we get a warning
  m_inputManager = InputManager::getGlobalInputManager(this);
  m_inputManager->connect("onModeChanged",
                          Callable(this, "onInputModeChanged"));


  // Iterate over skillset
  if (!m_skillSet.is_valid())
  {
    UtilityFunctions::push_warning("Player has no SkillSet assigned");
    return;
  }

  Callable skillsetCallable(this, "OnSkillInSet");
  m_skillSet->ForEachSkill(skillsetCallable);
}

void Player::_input(const Ref<InputEvent>& event)
{
  InputManager::InputMode currentInputMode = m_inputManager->getInputMode();
  if (currentInputMode == InputManager::InputMode::INPUT_MODE_KVM)
  {
    if (event->is_action_pressed("moveClick")) 
    {
      m_bIsMovementButtonPressed = true;
      setTargetPosition(tryRayCastToGround(get_viewport()->get_mouse_position()), true);
    } 
    else if (event->is_action_released("moveClick")) 
    {
      m_bIsMovementButtonPressed = false;
    }
  }
}

void Player::_physics_process(double delta)
{
  if (m_bIsMovementButtonPressed)
  {
    setTargetPosition(tryRayCastToGround(get_viewport()->get_mouse_position()));
  }
  if (m_inputManager->getInputMode() == InputManager::InputMode::INPUT_MODE_GAMEPAD)
  {
    Vector2 axisInput = Input::get_singleton()->get_vector("moveLeft", 
                                                           "moveRight", 
                                                           "moveForward", 
                                                           "moveBackward");
    if (axisInput.length() > 0.1f)
    {
      Vector3 moveDirection = Vector3(axisInput.x, 0, axisInput.y);
      m_forwardDirection += moveDirection.normalized();
      m_forwardDirection = m_forwardDirection.normalized();
      
      setTargetPosition(get_global_position() + m_forwardDirection, true);
    }
  }

  if (Input::get_singleton()->is_action_just_pressed("skill_1"))
  {
    if (m_skillFireCone)
    {
      m_skillFireCone->execute();
    }
  }
  
  moveToTarget(delta);
}

Vector3 Player::tryRayCastToGround(const Vector2& mousePosition)
{
  Vector3 from = m_camera->project_ray_origin(mousePosition);
  Vector3 to = from + m_camera->project_ray_normal(mousePosition) * m_distanceToGroundRaycast;

  PhysicsDirectSpaceState3D* space = get_world_3d()->get_direct_space_state();
  // We only want to hit the ground, which is layer 2 (set in Editor)
  Ref<PhysicsRayQueryParameters3D> query = PhysicsRayQueryParameters3D::create(from, to, 2);

  Dictionary hit = space->intersect_ray(query);
  if (!hit.is_empty())
  {
    return hit["position"];
  }

  UtilityFunctions::push_warning("Raycast to ground failed, mouse position: " + mousePosition);
  return this->get_position();
}

void Player::setTargetPosition(const Vector3& position, bool bShowMarker /*= false*/)
{
  m_targetPosition = position;
  m_bHasTarget = true;
  if (m_targetMarker && bShowMarker)
  {
    m_targetMarker->updateMarkerPosition(position);
  }
}

void Player::moveToTarget(double delta)
{
  Vector3 velocity = get_velocity();
  Vector3 globalPosition = get_global_position();

  if (m_bHasTarget)
  {
    Vector3 toTarget = m_targetPosition - globalPosition;
    toTarget.y = 0;

    float dist = toTarget.length();
    if (dist < m_distanceThreshold)
    {
      m_bHasTarget = false;
      velocity.x = 0;
      velocity.z = 0;
    }
    else
    {
      Vector3 dir = toTarget.normalized();
      velocity = dir * m_speed;

      // Optional rotation
      look_at(globalPosition + dir);
    }
  }
  else
  {
    velocity = Vector3(0, 0, 0);
  }

  if (velocity.length() > 0.1)
  {
    if (m_animationPlayer && m_animationPlayer->get_current_animation() != "Run/mixamo_com")
    {
      m_animationPlayer->play("Run/mixamo_com");
    }
  }
  else
  {
    if (m_animationPlayer && m_animationPlayer->get_current_animation() != "Idle/mixamo_com")
    {
      m_animationPlayer->play("Idle/mixamo_com");
    }
  }

  // Gravity
  velocity.y += get_gravity().y * delta;

  // Calculate Forward Direction
  m_forwardDirection = -get_global_transform().basis.get_column(2).normalized();

  set_velocity(velocity);
  move_and_slide();
}

void Player::OnSkillInSet(const Ref<SkillResource> skillResource)
{
  if (!skillResource.is_valid())
  {
    UtilityFunctions::push_warning("Invalid SkillResource in SkillSet");
    return;
  }

  SkillNode* skillNode = skillResource->CreateSkillNodeForThisResource();
  if (!skillNode)
  {
    UtilityFunctions::push_warning("Could not create SkillNode for SkillResource");
    return;
  }

  call_deferred("add_child", skillNode);

  // TODO:  delete!!!! TEsting only hehehe
  if (SkillFireCone* skillFireCone = Object::cast_to<SkillFireCone>(skillNode))
  {
    skillFireCone->init(this);
    m_skillFireCone = skillFireCone;
  }
}
