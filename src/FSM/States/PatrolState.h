#pragma once

#include "../State.h" 
#include "../FiniteStateMachine.h"
#include "../../Agent/Specific/Enemy.h"

#include<memory>

class PatrolState : public State
{
public:
  PatrolState(const shared_ptr<FiniteStateMachine>& stateMachine,
              Enemy* agent);
  ~PatrolState() = default;

public:
  void OnEnter() override;
  void OnUpdate() override;
  void OnExit() override;

private:
    Enemy* m_ptrAgent;
};
