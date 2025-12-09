#include "Projectile.h"

void Projectile::_ready()
{
  // Initialization code here
  m_collider = get_node<CollisionShape3D>("Collider");
  m_mesh = get_node<MeshInstance3D>("Mesh");
  set_gravity_scale(0.0f);
}

void Projectile::_physics_process(double delta)
{
  // Update position based on velocity and direction
  m_velocity = m_direction * m_speed;
  Vector3 new_position = get_global_position() + m_velocity * static_cast<float>(delta);
  set_global_position(new_position);
}

void Projectile::_bind_methods()
{
  // Method binding code here
}
