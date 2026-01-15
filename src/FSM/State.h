#pragma once

class FiniteStateMachine;

class State
{
public:
  State() = default;
  ~State() = default;

  protected:
    FiniteStateMachine* m_FiniteStateMachine;

  public:
    virtual void OnEnter() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnExit() = 0;
};
