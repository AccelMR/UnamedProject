#pragma once

#include "../State.h" 
#include "../FiniteStateMachine.h"
#include "../../Enemy.h"

#include<memory>

class PatrolState : public State
{
public:
  PatrolState(const shared_ptr<FiniteStateMachine>& stateMachine,
              const Enemy* agent);
  ~PatrolState() = default;

public:
  void OnEnter() override;
  void OnUpdate() override;
  void OnExit() override;

private:
    const Enemy* m_ptrAgent;
};