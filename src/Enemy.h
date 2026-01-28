#pragma once

#include <godot_cpp/classes/navigation_agent3d.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include <memory>

#include "IAgent.h"
#include "FSM/FiniteStateMachine.h"
#include "Skills/System/SkillSet.h"
#include "Player.h"

using namespace godot;
using namespace std;

class Enemy : public CharacterBody3D, public IAgent
{
  GDCLASS(Enemy, CharacterBody3D);
  
public:
  // Start
  void _ready() override;

  // Update
  void _process(double delta) override;

  void MoveTo(const Vector3& position);

  void ExecuteAbility();

  Ref<SkillSet> GetSkillSet() const { return m_skillSet; }
  void SetSkillSet(const Ref<SkillSet>& skillSet) { m_skillSet = skillSet; }

  inline Player* GetPlayer() const { return m_player; }
  
protected:
  static void _bind_methods();

  void OnNavigationFinished();
  
private:
  NavigationAgent3D* m_navigationAgent;
  Player* m_player;

  shared_ptr<FiniteStateMachine> m_fsm;
  
  Vector3 m_destination;
  Vector3 m_direction;

  Ref<SkillSet> m_skillSet;
};
