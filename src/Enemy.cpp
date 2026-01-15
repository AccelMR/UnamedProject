#include "Enemy.h"
// #include "FSM/FiniteStateMachine.h"
// #include "FSM/register_states.h"
// #include "FSM/State.h"
// #include "FSM/States/IdleState.h"

#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

void Enemy::_bind_methods() 
{
  UtilityFunctions::print("Enemy::_bind_methods called");
}

void Enemy::_ready()
{
  m_navigationAgent = get_node<NavigationAgent3D>("NavigationAgent3D");

  if (m_navigationAgent != nullptr)
  {
    // Apparently just calculates the path to the point
    m_navigationAgent->set_target_position(Vector3(3.0f, 1.0f, 3.0f));
  }

  // Create Finite state machine
  m_fsm = new FiniteStateMachine;
  m_fsm->Initialize();
  delete m_fsm;

  //m_fsm->AddState(StateID::IDLE, memnew(IdleState));
  //m_fsm->SetState(StateID::IDLE);
}

void Enemy::_process(double delta)
{
  if (m_navigationAgent != nullptr)
  {
    m_destination = m_navigationAgent->get_next_path_position();
    m_direction = (m_destination - get_global_position()).normalized();

    set_velocity(m_direction * 5.0f);
    move_and_slide();
  }

  // if (m_fsm != nullptr)
  // {
  //   m_fsm->Update();
  // }
}