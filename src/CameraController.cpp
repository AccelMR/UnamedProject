#include "CameraController.h"
#include <godot_cpp/classes/input.hpp>

using namespace godot;

void CameraController::_bind_methods() {}

void CameraController::_ready() {
    // Nada especial por ahora
}

void CameraController::_physics_process(double delta) {
    Input *input = Input::get_singleton();

    Vector3 movement;
    Transform3D t = get_global_transform();

    Vector3 right   = t.basis[0];   // +X local
    Vector3 forward = -t.basis[2];  // -Z local (forward real)

    if (input->is_action_pressed("camForward"))
    {
      movement += forward;
    }
    if (input->is_action_pressed("camBackward"))
    {
      movement -= forward;
    }
    if (input->is_action_pressed("camLeft"))
    {
      movement -= right;
    }
    if (input->is_action_pressed("camRight"))
    {
      movement += right;
    }

    if (movement.length() > 0.001f)
    {
      movement = movement.normalized() * (m_speed * (float)delta);
    }
    set_global_position(get_global_position() + movement);
}

