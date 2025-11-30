#pragma once

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/timer.hpp>

using namespace godot;

struct FireConeData;

class FireCone : public Node3D
{
  GDCLASS(FireCone, Node3D);

 public:
  FireCone() = default;
  ~FireCone() = default;

  // Setup the cone parameters, must be called before using the cone
  void SetupCone(const FireConeData& data);

  void ActivateFor(float duration);

  bool IsActive() const { return m_isActive; }

 protected:
  static void _bind_methods();

  void OnTimerTimeout();

 private:
  Area3D* m_damageArea = nullptr;
  CollisionShape3D* m_collisionShape = nullptr;
  Timer* m_timer = nullptr;
  bool m_isActive = false;
};