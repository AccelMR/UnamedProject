#pragma once

#include<memory>

using namespace std;

class FiniteStateMachine;

class State
{
public:
  State() = default;
  virtual ~State() = default;

protected:
    shared_ptr<FiniteStateMachine> m_finiteStateMachine;

public:
    virtual void OnEnter() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnExit() = 0;
};
