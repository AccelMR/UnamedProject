#include "Enemy.h"

#include <godot_cpp/classes/navigation_agent3d.hpp>  

void Enemy::_bind_methods() {}

void Enemy::_ready()
{
  m_navigationAgent = get_node<NavigationAgent3D>("NavigationAgent3D");

  if (m_navigationAgent != nullptr)
  {
    // Apparently just calculates the path to the point
    m_navigationAgent->set_target_position(Vector3(3.0f, 1.0f, 3.0f));
  }
}

void Enemy::_process(double delta)
{
  if (m_navigationAgent != nullptr)
  {
    m_destination = m_navigationAgent->get_next_path_position();
    m_direction = (m_destination - get_global_position()).normalized();

    set_velocity(m_direction * 5.0f);
    move_and_slide();
  }
}