#include "FiniteStateMachine.h"

#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/classes/object.hpp>

void FiniteStateMachine::Initialize()
{
  m_currentStateID = StateID::NONE;
  m_toStateID = StateID::NONE;
}

void FiniteStateMachine::SetState(StateID id)
{
  m_toStateID = id;
}

void FiniteStateMachine::Update()
{
  if (m_toStateID != m_currentStateID)
  {
    ChangeState(m_toStateID);
  }

  if (!m_currentState.expired())
  {
   (*m_currentState.lock()).OnUpdate();
  }
}

void FiniteStateMachine::AddState(StateID state, const shared_ptr<State>& newState)
{
  m_states.insert({state, newState});
}

void FiniteStateMachine::ChangeState(StateID toState)
{
  if(m_states.size() == 0)
    return;

  // Exits from current state if exists
  if(!m_currentState.expired())
  {
    (*m_currentState.lock()).OnExit();
  }

  // Set new state
  m_currentState = m_states.find(toState)->second;  

  // Enters new state
  if (!m_currentState.expired())
  {
    m_currentStateID = toState;

    (*m_currentState.lock()).OnEnter();
  }
}
