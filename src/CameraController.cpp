#include "CameraController.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>

using namespace godot;

void CameraController::_bind_methods() 
{
  ClassDB::bind_method(D_METHOD("SetSpeed", "speed"), &CameraController::SetSpeed);
  ClassDB::bind_method(D_METHOD("GetSpeed"), &CameraController::GetSpeed);

  ClassDB::bind_method(D_METHOD("SetZoomSpeed", "zoomSpeed"), &CameraController::SetZoomSpeed);
  ClassDB::bind_method(D_METHOD("GetZoomSpeed"), &CameraController::GetZoomSpeed);

  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "SetSpeed", "GetSpeed");
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "zoomSpeed"), "SetZoomSpeed", "GetZoomSpeed");
}

void CameraController::_ready()
{
  m_inputManager = InputManager::getGlobalInputManager(this);
}

void CameraController::_physics_process(double delta)
{
  Input* input = Input::get_singleton();

  Vector3 panMovement;
  Vector3 zoomMovement;
  Transform3D transform = get_global_transform();

  const Vector3 worldRight(1, 0, 0);
  const Vector3 worldForward(0, 0, -1);

  // get_column(2) is the forward vector in Godot
  Vector3 viewForward = -transform.basis.get_column(2).normalized();

  if (m_inputManager->GetInputMode() == InputManager::INPUT_MODE_KVM)
  {
    if (input->is_action_pressed("camForward"))
    {
      panMovement += worldForward;
    }
    if (input->is_action_pressed("camBackward"))
    {
      panMovement -= worldForward;
    }
    if (input->is_action_pressed("camLeft"))
    {
      panMovement -= worldRight;
    }
    if (input->is_action_pressed("camRight"))
    {
      panMovement += worldRight;
    }
  }
  else if (m_inputManager->GetInputMode() == InputManager::INPUT_MODE_GAMEPAD)
  {
    Vector2 camMovement = input->get_vector("camLeft", "camRight", "camBackward", "camForward");
    panMovement += worldRight * camMovement.x;
    panMovement += worldForward * camMovement.y;
  }

  // Zoom controls, scroll wheel up/down needs to be called through 
  // just_released since pressed doesn't register for scroll or something dunno
  if (input->is_action_just_released("camZoomIn") || input->is_action_pressed("camZoomIn"))
  {
    zoomMovement += viewForward * m_zoomSpeed * static_cast<float>(delta);
  }
  if (input->is_action_just_released("camZoomOut") || input->is_action_pressed("camZoomOut"))
  {
    zoomMovement -= viewForward * m_zoomSpeed * static_cast<float>(delta);
  }

  if (panMovement.length() > 0.001f)
  {
    panMovement = panMovement.normalized() * (m_speed * static_cast<float>(delta));
  }
  else
  {
    panMovement = Vector3(0, 0, 0);
  }

  set_global_position(get_global_position() + panMovement + zoomMovement);
}
