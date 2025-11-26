#include "CameraController.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>

using namespace godot;

void CameraController::_bind_methods() 
{
  ClassDB::bind_method(D_METHOD("setSpeed", "speed"), &CameraController::setSpeed);
  ClassDB::bind_method(D_METHOD("getSpeed"), &CameraController::getSpeed);

  ClassDB::bind_method(D_METHOD("setZoomSpeed", "zoomSpeed"), &CameraController::setZoomSpeed);
  ClassDB::bind_method(D_METHOD("getZoomSpeed"), &CameraController::getZoomSpeed);

  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "setSpeed", "getSpeed");
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "zoomSpeed"), "setZoomSpeed", "getZoomSpeed");
}

void CameraController::_ready()
{
  // Nada especial por ahora
}
void CameraController::_physics_process(double delta)
{
  Input *input = Input::get_singleton();

  Vector3 movement;
  Transform3D transform = get_global_transform();

  const Vector3 world_right(1, 0, 0);
  const Vector3 world_forward(0, 0, -1);

  // get_column(2) is the forward vector in Godot
  Vector3 view_forward = -transform.basis.get_column(2).normalized();

  if (input->is_action_pressed("camForward"))
  {
    movement += world_forward * m_speed * static_cast<float>(delta);
  }
  if (input->is_action_pressed("camBackward"))
  {
    movement -= world_forward * m_speed * static_cast<float>(delta);
  }
  if (input->is_action_pressed("camLeft"))
  {
    movement -= world_right * m_speed * static_cast<float>(delta);
  }
  if (input->is_action_pressed("camRight"))
  {
    movement += world_right * m_speed * static_cast<float>(delta);
  }

  // Zoom controls, scroll wheel up/down needs to be called through 
  // just_released since pressed doesn't register for scroll or something dunno
  if (input->is_action_just_released("camZoomIn"))
  {
    movement += view_forward * m_zoomSpeed * static_cast<float>(delta);
  }
  if (input->is_action_just_released("camZoomOut"))
  {
    movement -= view_forward * m_zoomSpeed * static_cast<float>(delta);
  }

  if (movement.length() > 0.001f)
  {
    movement = movement.normalized() * (m_speed * static_cast<float>(delta));
  }

  set_global_position(get_global_position() + movement);
}
