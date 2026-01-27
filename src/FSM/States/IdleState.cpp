#include "IdleState.h"
#include <godot_cpp/variant/utility_functions.hpp>

IdleState::IdleState(const shared_ptr<FiniteStateMachine> &stateMachine)
{
  m_finiteStateMachine = stateMachine;
}

void IdleState::OnEnter()
{
  godot::UtilityFunctions::print("Enter Idle State");
}

void IdleState::OnUpdate()
{
  m_finiteStateMachine->SetState(StateID::PATROL);
}

void IdleState::OnExit()
{
  godot::UtilityFunctions::print("Exit Idle State");
}
