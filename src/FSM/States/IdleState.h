#pragma once

#include "../State.h" 

class IdleState : public State
{
public:
  IdleState() = default;
  ~IdleState() = default;

public:
  void OnEnter() override;
  void OnUpdate() override;
  void OnExit() override;
};