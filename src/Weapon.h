#ifndef WEAPON_H
#define WEAPON_H

#include <godot_cpp/classes/rigid_body3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class Weapon : public RigidBody3D
{
  GDCLASS(Weapon, RigidBody3D);

private:
  CollisionShape3D* collision = nullptr;
  MeshInstance3D* mesh = nullptr;

protected:
  static void _bind_methods();

  //Weapon's base damage.
  float m_baseDamage = 0.5f;

public:
  Weapon() = default;
  virtual ~Weapon() = default;

  void _ready() override;
  void _physics_process(double delta) override;

  //Setters and Getters
  void SetBaseDamage(float _newDamage);
  float GetBaseDamage() const;
};

#endif