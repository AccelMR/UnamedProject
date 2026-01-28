#include "AttackState.h"
#include <godot_cpp/variant/utility_functions.hpp>

AttackState::AttackState(const shared_ptr<FiniteStateMachine> &stateMachine,
                         Enemy* agent)
{
  m_finiteStateMachine = stateMachine;
  m_ptrAgent = agent;
}

void AttackState::OnEnter()
{
  godot::UtilityFunctions::print("Enter Attack State");
  m_ptrAgent->ExecuteAbility();
}

void AttackState::OnUpdate()
{

}

void AttackState::OnExit()
{
  godot::UtilityFunctions::print("Exit Attack State");
}