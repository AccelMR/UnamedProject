#include "Enemy.h"
#include "FSM/State.h"
#include "FSM/States/IdleState.h"
#include "FSM/States/PatrolState.h"

#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

void Enemy::_bind_methods() 
{
  UtilityFunctions::print("Enemy::_bind_methods called");
}

void Enemy::_ready()
{
  m_navigationAgent = get_node<NavigationAgent3D>("NavigationAgent3D");
  DEV_ASSERT(m_navigationAgent);

  // Apparently just calculates the path to the point
  m_navigationAgent->set_target_position(Vector3(3.0f, 1.0f, 3.0f));
  
  // Create and initialize finite state machine
  m_fsm = make_shared<FiniteStateMachine>();
  DEV_ASSERT(m_fsm);

  m_fsm->Initialize();
  
  // Subscribe states
  shared_ptr<IdleState> ptrIdleState = make_shared<IdleState>(m_fsm);
  m_fsm->AddState(StateID::IDLE, ptrIdleState);
  shared_ptr<PatrolState> ptrPatrolState = make_shared<PatrolState>(m_fsm, this);
  m_fsm->AddState(StateID::PATROL, ptrPatrolState);

  // Ste initial state
  m_fsm->SetState(StateID::IDLE);
}

void Enemy::_process(double delta)
{
  // Update State Machine
  m_fsm->Update();
}

void Enemy::MoveTo(const Vector3 &position)
{
  // Move agent to position
  m_destination = m_navigationAgent->get_next_path_position();
  m_direction = (m_destination - get_global_position()).normalized();

  set_velocity(m_direction * 5.0f);
  move_and_slide();
}
