#pragma once

#include <godot_cpp/variant/dictionary.hpp>

#include <memory>
#include <map>

#include "State.h"

using namespace godot;
using namespace std;

enum StateID
{
  NONE = 0,
  IDLE,
  PATROL,
  PURSUIT,
  ATTACK
};

class FiniteStateMachine
{
public:
  FiniteStateMachine() = default;
  ~FiniteStateMachine() = default;

public:
  void Initialize();
	void SetState(StateID id);
  void Update();
  void AddState(StateID state, const shared_ptr<State>& newState);

private:
  void ChangeState(StateID toState);

private:
  map<StateID, shared_ptr<State>> m_states;
  StateID m_currentStateID;
  StateID m_toStateID;
  weak_ptr<State> m_currentState;
};
