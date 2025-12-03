#include <Weapon.h>
#include <godot_cpp/classes/sphere_mesh.hpp>

void Weapon::_bind_methods()
{
  //Register methods.
  ClassDB::bind_method(D_METHOD("setBaseDamage", "_newDamage"), &Weapon::SetBaseDamage);
  ClassDB::bind_method(D_METHOD("getBaseDamage"), &Weapon::GetBaseDamage);

  ClassDB::bind_method(D_METHOD("setWeaponType", "_newType"), &Weapon::SetWeaponType);
  ClassDB::bind_method(D_METHOD("getWeaponType"), &Weapon::GetWeaponType);

  //Add properties to the inspector.
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT,
               "baseDamage",
               PROPERTY_HINT_RANGE,
               "0,100,0.1"),
               "setBaseDamage",
               "getBaseDamage");

  ADD_PROPERTY(PropertyInfo(Variant::INT,
               "weaponType",
               PROPERTY_HINT_ENUM,
               "Melee:1,Range:2"),
               "setWeaponType",
               "getWeaponType");
}

void Weapon::_ready()
{
  //mesh = get_node<MeshInstance3D>("MeshInstance3D");
  //collision = get_node<CollisionShape3D>("CollisionShape3D");
  m_projectileSpawnPoint = get_node<Node3D>("ProjectileSpawnPoint");
}

void Weapon::_physics_process(double delta)
{
  
}

void Weapon::Attack()
{
  UtilityFunctions::print("Attacked!");

  if(m_weaponType == WEAPON_TYPE_RANGE)
  {

    UtilityFunctions::print("Attacked with ranged weapon!");
  }

}
