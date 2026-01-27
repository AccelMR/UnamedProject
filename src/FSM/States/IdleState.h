#pragma once

#include "../State.h" 
#include "../FiniteStateMachine.h"

#include<memory>

class IdleState : public State
{
public:
  IdleState(const shared_ptr<FiniteStateMachine>& stateMachine);
  ~IdleState() = default;

public:
  void OnEnter() override;
  void OnUpdate() override;
  void OnExit() override;
};