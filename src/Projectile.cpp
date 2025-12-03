#include "Projectile.h"

void Projectile::_ready()
{
  // Initialization code here
  m_collider = get_node<CollisionShape3D>("Collider");
  m_mesh = get_node<MeshInstance3D>("Mesh");
}

void Projectile::_physics_process(double delta)
{
  // Physics processing code here
}

void Projectile::_bind_methods()
{
  // Method binding code here
}
