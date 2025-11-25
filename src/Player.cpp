#include "Player.h"
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/physics_direct_space_state3d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters3d.hpp>
#include <godot_cpp/classes/world3d.hpp>

using namespace godot;

void Player::_bind_methods() {}

void Player::_ready()
{
  m_collider = get_node<CollisionShape3D>("CollisionShape3D");
  m_camera = get_node<Camera3D>("../CameraController");
  m_targetMarker = get_node<Node3D>("../Marker");
}

void Player::_unhandled_input(const Ref<InputEvent> &event)
{
  if (!m_camera)
  {
    return;
  }

  Ref<InputEventMouseButton> mouseEvent = event;
  if (mouseEvent.is_valid() && mouseEvent->is_pressed() &&
      mouseEvent->get_button_index() == MouseButton::MOUSE_BUTTON_LEFT)
  {
    Vector2 mouse_pos = mouseEvent->get_position();
    Vector3 from = m_camera->project_ray_origin(mouse_pos);
    Vector3 to = from + m_camera->project_ray_normal(mouse_pos) * 10000.0f; // Ugly magic number

    PhysicsDirectSpaceState3D* space = get_world_3d()->get_direct_space_state();
    Ref<PhysicsRayQueryParameters3D> query = PhysicsRayQueryParameters3D::create(from, to);

    Dictionary hit = space->intersect_ray(query);
    if (!hit.is_empty())
    {
      m_targetPosition = hit["position"];
      m_bHasTarget = true;

      if (m_targetMarker)
      {
        m_targetMarker->set_global_position(m_targetPosition);
      }
    }
  }
}

void Player::_physics_process(double delta)
{
  Vector3 vel = get_velocity();

  if (m_bHasTarget)
  {
    Vector3 to_target = m_targetPosition - get_global_position();
    to_target.y = 0;

    float dist = to_target.length();
    if (dist < 0.1f)
    {
      m_bHasTarget = false;
      vel.x = 0;
      vel.z = 0;
    }
    else
    {
      Vector3 dir = to_target.normalized();
      vel = dir * m_speed;

      // Rotar opcional
      look_at(get_global_position() + dir);
    }
  }
  else
  {
    vel = Vector3(0, 0, 0);
  }

  // Gravity
  vel.y += get_gravity().y;

  set_velocity(vel);
  move_and_slide();
}
