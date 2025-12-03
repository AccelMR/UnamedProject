#pragma once

#include <godot_cpp/variant/dictionary.hpp>
#include "register_states.h"

class State;

using namespace godot;

class FiniteStateMachine
{
public:
  FiniteStateMachine() = default;
  ~FiniteStateMachine() = default;

public:
  void Initialize();
	void SetState(StateID id);
  void Update();
  void AddState(StateID state, State* newState);

private:
  void ChangeState(StateID toState);

private:
  Dictionary m_states;
  StateID m_currentStateID;
  StateID m_toStateID;
  State* m_currentState;
};
