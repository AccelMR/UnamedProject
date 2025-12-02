#pragma once

#include "Agent.h"

namespace godot 
{
  class NavigationAgent3D;
  
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
  
  protected:
    static void _bind_methods();
  
  private:
    NavigationAgent3D* m_navigationAgent;
    Vector3 m_destination;
    Vector3 m_direction;
  };
}
