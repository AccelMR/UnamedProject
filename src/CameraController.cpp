#include "CameraController.h"
#include <godot_cpp/classes/input.hpp>

using namespace godot;

void CameraController::_bind_methods() {}

void CameraController::_ready() {
    // Nada especial por ahora
}
void CameraController::_physics_process(double delta) {
    Input* input = Input::get_singleton();

    Vector3 movement;
    Transform3D t = get_global_transform();

    const Vector3 world_right = Vector3(1, 0, 0);   // Pan along world X
    const Vector3 world_forward = Vector3(0, 0, -1); // Pan along world Z
    const Vector3 view_forward = (-t.basis[2]).normalized(); // Zoom along view

    if (input->is_action_pressed("camForward"))
    {
      movement += world_forward;
    }
    if (input->is_action_pressed("camBackward"))
    {
      movement -= world_forward;
    }
    if (input->is_action_pressed("camLeft"))
    {
      movement -= world_right;
    }
    if (input->is_action_pressed("camRight"))
    {
      movement += world_right;
    }
    if (input->is_action_pressed("camZoomMin"))
    {
      movement += view_forward;
    }
    if (input->is_action_pressed("camZoomMax"))
    {
      movement -= view_forward;
    }

    if (movement.length() > 0.001f)
    {
      movement = movement.normalized() * (m_speed * (float)delta);
    }
    set_global_position(get_global_position() + movement);
}
