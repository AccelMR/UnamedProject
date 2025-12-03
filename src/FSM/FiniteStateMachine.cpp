#include "FiniteStateMachine.h"
#include "State.h"
#include "register_states.h"

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

  if (m_currentState != nullptr)
  {
    m_currentState->OnUpdate();
  }
}

void FiniteStateMachine::AddState(StateID state, State* newState)
{
  m_states[state] = newState;
}

void FiniteStateMachine::ChangeState(StateID toState)
{
  if(m_states.is_empty())
    return;

  // Exits from current state if exists
  if(m_currentState != nullptr)
    m_currentState->OnExit();

  // Cast to State object
  Variant v = m_states[toState];
  Object* o = v;   // Variant → Object*
  m_currentState = (State*)o;
  if (m_currentState != nullptr)
  {
    m_currentStateID = toState;

    m_currentState->OnEnter();
  }
}
