#include "IdleState.h"
#include <godot_cpp/variant/utility_functions.hpp>

void IdleState::OnEnter()
{
  godot::UtilityFunctions::print("Hello from C++!");
}

void IdleState::OnUpdate()
{
}

void IdleState::OnExit()
{
}
