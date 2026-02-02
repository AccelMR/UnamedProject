#include "PatrolState.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include "../../Agent/Specific/Player.h"

PatrolState::PatrolState(const shared_ptr<FiniteStateMachine> &stateMachine,
                         Enemy* agent)
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
  Player* player = m_ptrAgent->GetPlayer();

  m_ptrAgent->MoveTo(player->get_position());
  //m_ptrAgent->MoveTo(Vector3(3.f,1.f,3.f));
}

void PatrolState::OnExit()
{
  godot::UtilityFunctions::print("Exit Patrol State");
}
