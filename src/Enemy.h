#pragma once

#include "IAgent.h"
#include <godot_cpp/classes/navigation_agent3d.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include "FSM/FiniteStateMachine.h"

using namespace godot;

class Enemy : public CharacterBody3D, public IAgent
{
  GDCLASS(Enemy, CharacterBody3D);
  
public:
  // Start
  void _ready() override;
  // Update
  void _process(double delta) override;
  
protected:
  static void _bind_methods();
  
private:
  NavigationAgent3D* m_navigationAgent;
  Vector3 m_destination;
  Vector3 m_direction;
  FiniteStateMachine* m_fsm;
};
