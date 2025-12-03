#ifndef WEAPON_H
#define WEAPON_H

#include <godot_cpp/classes/rigid_body3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

enum WeaponType
{
  WEAPON_TYPE_NONE = 0,
  WEAPON_TYPE_MELEE = 1,
  WEAPON_TYPE_RANGE = 2,
  WEAPON_TYPE_TOTAL = 3
};

class Weapon : public RigidBody3D
{
  GDCLASS(Weapon, RigidBody3D);

private:
  //CollisionShape3D* collision = nullptr;
  //MeshInstance3D* mesh = nullptr;

protected:
  static void _bind_methods();

  //Weapon's base damage.
  float m_baseDamage = 0.5f;

  //Weapon's attack type.
  WeaponType m_weaponType = WEAPON_TYPE_MELEE;

  Node3D* m_projectileSpawnPoint = nullptr;
  RigidBody3D* m_projectileBody = nullptr;
  MeshInstance3D* m_projectileMesh = nullptr;

public:
  Weapon() = default;
  virtual ~Weapon() = default;

  void _ready() override;
  void _physics_process(double delta) override;

  virtual void Attack();

  //Setters and Getters
  void SetBaseDamage(float _newDamage) { m_baseDamage = _newDamage; }
  float GetBaseDamage() const { return m_baseDamage; }

  void SetWeaponType(WeaponType _newType) { m_weaponType = _newType; }
  WeaponType GetWeaponType() const { return m_weaponType; }
};

VARIANT_ENUM_CAST(WeaponType);

#endif