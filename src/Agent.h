#pragma once

#include <godot_cpp/classes/character_body3d.hpp>

using namespace godot;

class Agent : public CharacterBody3D
{
  GDCLASS(Agent, CharacterBody3D);

public:
  Agent() = default;
  ~Agent() = default;

protected:
  static void _bind_methods();
};
