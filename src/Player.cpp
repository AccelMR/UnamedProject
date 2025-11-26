#include "Player.h"
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/physics_direct_space_state3d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters3d.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/world3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/viewport.hpp>

#include "MouseMarker.h"

using namespace godot;

void Player::_bind_methods() 
{
  ClassDB::bind_method(D_METHOD("getMarkerScenePath"), &Player::getMarkerScenePath);
  ClassDB::bind_method(D_METHOD("setMarkerScenePath", "path"), &Player::setMarkerScenePath);

  ClassDB::bind_method(D_METHOD("setMoveButton", "button"), &Player::setMoveButton);
  ClassDB::bind_method(D_METHOD("getMoveButton"), &Player::getMoveButton);

  ADD_PROPERTY(PropertyInfo(Variant::STRING, "markerScenePath"), "setMarkerScenePath", "getMarkerScenePath");
  ADD_PROPERTY(PropertyInfo(Variant::INT, 
               "moveButton", 
               PROPERTY_HINT_ENUM, 
               "Left:1,Right:2,Middle:3"), 
               "setMoveButton", 
               "getMoveButton");
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
}

void Player::_unhandled_input(const Ref<InputEvent>& event)
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

void Player::_physics_process(double delta)
{
  if (m_bIsMovementButtonPressed)
  {
    setTargetPosition(tryRayCastToGround(get_viewport()->get_mouse_position()));
  }
  moveToTarget(delta);
}

Vector3 Player::tryRayCastToGround(const Vector2& mousePosition)
{
 Vector2 mouse_pos = get_viewport()->get_mouse_position();
  Vector3 from = m_camera->project_ray_origin(mouse_pos);
  Vector3 to = from + m_camera->project_ray_normal(mouse_pos) * m_distanceToGroundRaycast;

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
