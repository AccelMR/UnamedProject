#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/input_event.hpp>  

using namespace godot;

class Player : public CharacterBody3D
{
  GDCLASS(Player, CharacterBody3D);

 public:
  Player() = default;
  ~Player() = default;

  void _ready() override;
  void _unhandled_input(const Ref<InputEvent>& event) override;
  void _physics_process(double delta) override;

 protected:
  static void _bind_methods();

 private:
  CollisionShape3D* m_collider;
  Camera3D* m_camera;

  float m_speed = 5.0f;

  bool m_bHasTarget = false;
  Vector3 m_targetPosition;

  Node3D* m_targetMarker = nullptr;
};

#endif
