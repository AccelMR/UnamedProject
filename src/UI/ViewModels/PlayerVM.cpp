#include "UI/ViewModels/PlayerVM.h"

#include <godot_cpp/variant/variant.hpp>

using namespace godot;

PlayerVM::PlayerVM(){}

PlayerVM::~PlayerVM() {}

void PlayerVM::AddHealthChangedListener(Callable listener)
{
  m_onHealthChangedListeners.push_back(listener);
}

void PlayerVM::NotifyHealthChanged(int32_t newHealth)
{
  m_health = newHealth;
  for (const Callable& listener : m_onHealthChangedListeners)
  {
    if (listener.is_valid())
    {
      listener.call(m_health);
    }
  }
}
