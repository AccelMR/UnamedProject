#pragma once

class FiniteStateMachine;

class State
{
  protected:
    FiniteStateMachine* m_FiniteStateMachine;

  public:
    virtual void OnEnter() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnExit() = 0;
};
