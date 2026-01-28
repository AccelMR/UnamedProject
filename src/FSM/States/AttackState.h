#pragma once

#include "../State.h" 
#include "../FiniteStateMachine.h"
#include "../../Enemy.h"

#include<memory>

class AttackState : public State
{
public:
  AttackState(const shared_ptr<FiniteStateMachine>& stateMachine,
             Enemy* agent);
  ~AttackState() = default;

public:
  void OnEnter() override;
  void OnUpdate() override;
  void OnExit() override;

private:
  Enemy* m_ptrAgent;
};