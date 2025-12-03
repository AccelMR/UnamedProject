#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <godot_cpp/classes/rigid_body3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class Projectile : public RigidBody3D
{
  GDCLASS(Projectile, RigidBody3D);

public:
  Projectile() = default;
  ~Projectile() = default;
  void _ready() override;
  void _physics_process(double delta) override;

  void SetSpeed(float speed) { m_speed = speed; }
  float GetSpeed() const { return m_speed; }

  void SetLifetime(float lifetime) { m_lifetime = lifetime; }
  float GetLifetime() const { return m_lifetime; }

  void SetDirection(const Vector3& direction) { m_direction = direction.normalized(); }
  Vector3 GetDirection() const { return m_direction; }

  void SetVelocity(const Vector3& velocity) { m_velocity = velocity; }
  Vector3 GetVelocity() const { return m_velocity; }

protected:
  static void _bind_methods();
  CollisionShape3D* m_collider = nullptr;
  MeshInstance3D* m_mesh = nullptr;

private:
  float m_speed = 20.0f;
  float m_lifetime = 5.0f;

  Vector3 m_direction = Vector3(0, 0, -1);
  Vector3 m_velocity = Vector3::ZERO;
};

#endif // !PROJECTILE_H
