#include "PatrolState.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/vector3.hpp>

PatrolState::PatrolState(const shared_ptr<FiniteStateMachine> &stateMachine,
                         const Enemy* agent)
{
  m_finiteStateMachine = stateMachine;
  m_ptrAgent = agent;
}

void PatrolState::OnEnter()
{
  godot::UtilityFunctions::print("Enter Patrol State");
}

void PatrolState::OnUpdate()
{
  const_cast<Enemy*>(m_ptrAgent)->MoveTo(Vector3(2.f,2.f,2.f));
}

void PatrolState::OnExit()
{
  godot::UtilityFunctions::print("Exit Patrol State");
}
