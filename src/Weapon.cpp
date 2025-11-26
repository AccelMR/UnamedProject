#include <Weapon.h>

void Weapon::_bind_methods()
{
  //Register methods.
  ClassDB::bind_method(D_METHOD("SetBaseDamage", "_newDamage"), &Weapon::SetBaseDamage);
  ClassDB::bind_method(D_METHOD("GetBaseDamage"), &Weapon::GetBaseDamage);

  //Add properties to the inspector.
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "BaseDamage", PROPERTY_HINT_RANGE, "0,100,0.1"),
               "SetBaseDamage",
               "GetBaseDamage");
}

void Weapon::_ready()
{
  mesh = get_node<MeshInstance3D>("MeshInstance3D");
  collision = get_node<CollisionShape3D>("CollisionShape3D");
}

void Weapon::_physics_process(double delta)
{
  
}

void Weapon::SetBaseDamage(float _newDamage)
{
  m_baseDamage = _newDamage;
}

float Weapon::GetBaseDamage() const
{
  return m_baseDamage;
}
