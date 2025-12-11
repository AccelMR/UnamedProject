#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body3d.hpp>

#include <godot_cpp/classes/animation_player.hpp> 
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/variant/dictionary.hpp>

#include <memory>

using namespace godot;

class InputManager;
class MouseMarker;
class PlayerUI;
class SkillFireCone;
class SkillSet;
class SkillResource;
class PlayerVM;

class PlayerData
{
 public:
  PlayerData() = default;
  ~PlayerData() = default;
  void CreateViewModel();
  std::weak_ptr<PlayerVM> GetViewModel() const { return m_viewModel; }

  int32_t GetHealth() const { return health; }
  void SetHealth(int32_t newHealth);

  int32_t GetMaxHealth() const { return maxHealth; }
  void SetMaxHealth(int32_t newMaxHealth)
  {
    maxHealth = newMaxHealth;
    health = Math::clamp(health, 0, maxHealth);
  }

  int32_t GetStamina() const { return stamina; }
  void SetStamina(int32_t newStamina)
  {
    stamina = Math::clamp(newStamina, 0, maxStamina);
  }

  int32_t GetMaxStamina() const { return maxStamina; }
  void SetMaxStamina(int32_t newMaxStamina)
  {
    maxStamina = newMaxStamina;
    stamina = Math::clamp(stamina, 0, maxStamina);
  }

 private:
  int32_t health = 100;
  int32_t maxHealth = 100;
  int32_t stamina = 100;
  int32_t maxStamina = 100;

  std::shared_ptr<PlayerVM> m_viewModel;
};

class Player : public CharacterBody3D
{
  GDCLASS(Player, CharacterBody3D);

 public:
  Player() = default;
  ~Player() = default;

  void _ready() override;
  // Changed _input to _unhandled_input to avoid consuming input events meant for other nodes
  // _input happens before GUI then _unhandled_input
  void _unhandled_input(const Ref<InputEvent>& event) override;
  void _physics_process(double delta) override;

  String GetMarkerScenePath() const { return m_markerScenePath; }
  void SetMarkerScenePath(const String& path) { m_markerScenePath = path; }

  void SetMoveButton(MouseButton button) { m_moveButton = button; }
  MouseButton GetMoveButton() const { return m_moveButton; }

  Ref<SkillSet> GetSkillSet() const { return m_skillSet; }
  void SetSkillSet(const Ref<SkillSet>& skillSet) { m_skillSet = skillSet; }

 protected:
  static void _bind_methods();

 private:
  Vector3 TryRayCastToGround(const Vector2& mousePosition);
  void SetTargetPosition(const Vector3& position, bool bShowMarker = false);
  
  void MoveToTarget(double delta);
  
 private:
  CollisionShape3D* m_collider;
  Camera3D* m_camera;
  AnimationPlayer* m_animationPlayer;
  InputManager* m_inputManager;
  PlayerUI* m_playerUI;

  // Custom class to manage Player state and logic
  std::shared_ptr<PlayerVM> m_viewModel;

  PlayerData m_playerData;

  int32_t m_maxSkillSlots = 4;
  float m_speed = 5.0f;

  bool m_bHasTarget = false;
  bool m_bIsMovementButtonPressed = false;
  Vector3 m_targetPosition;
  Vector3 m_forwardDirection;

  MouseMarker* m_targetMarker = nullptr;

  Dictionary m_skillExecutors;

  // Editor exposed variables
  String m_markerScenePath = "res://Scenes/Marker.tscn";
  MouseButton m_moveButton = MouseButton::MOUSE_BUTTON_LEFT;
  float m_distanceThreshold = 0.1f;
  float m_distanceToGroundRaycast = 10000.0f;

  // Resource Dependencies
  Ref<PackedScene> m_resourceMarkerScene;

  Ref<SkillSet> m_skillSet;
};

#endif

