#pragma once

#include "Agent.h"

#include <godot_cpp/classes/navigation_agent3d.hpp>
#include <godot_cpp/variant/vector3.hpp>

class Enemy : public Agent
{
  GDCLASS(Enemy, Agent);

public:
  Enemy() = default;
  ~Enemy() = default;

  // Start
  void _ready() override;
  // Update
  void _process(double delta) override;

  virtual void dummyPureVirtualFunction() override;

protected:
  static void _bind_methods();

private:
  NavigationAgent3D* m_navigationAgent;
  Vector3 m_destination;
  Vector3 m_direction;
};
