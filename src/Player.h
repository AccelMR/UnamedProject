#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body3d.hpp>

#include <godot_cpp/classes/animation_player.hpp> 
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include "InputManager.h"

using namespace godot;

class MouseMarker;
class InputManager;

class Player : public CharacterBody3D
{
  GDCLASS(Player, CharacterBody3D);

 public:
  Player() = default;
  ~Player() = default;

  void _ready() override;
  void _input(const Ref<InputEvent>& event) override;
  void _physics_process(double delta) override;

  String getMarkerScenePath() const { return m_markerScenePath; }
  void setMarkerScenePath(const String& path) { m_markerScenePath = path; }

  void setMoveButton(MouseButton button) { m_moveButton = button; }
  MouseButton getMoveButton() const { return m_moveButton; }

 protected:
  static void _bind_methods();

 private:
  Vector3 tryRayCastToGround(const Vector2& mousePosition);
  void setTargetPosition(const Vector3& position, bool bShowMarker = false);
  
  void moveToTarget(double delta);

  
 private:
  CollisionShape3D* m_collider;
  Camera3D* m_camera;
  AnimationPlayer* m_animationPlayer;
  InputManager* m_inputManager;

  float m_speed = 5.0f;

  bool m_bHasTarget = false;
  bool m_bIsMovementButtonPressed = false;
  Vector3 m_targetPosition;
  Vector3 m_forwardDirection;

  MouseMarker* m_targetMarker = nullptr;

  // Editor exposed variables
  String m_markerScenePath = "res://Scenes/Marker.tscn";
  MouseButton m_moveButton = MouseButton::MOUSE_BUTTON_LEFT;
  float m_distanceThreshold = 0.1f;
  float m_distanceToGroundRaycast = 10000.0f;

  // Resource Dependencies
  Ref<PackedScene> m_resourceMarkerScene;
};

#endif

