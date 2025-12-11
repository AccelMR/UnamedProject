#pragma once

#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/templates/vector.hpp>

using namespace godot;

class PlayerData;

class PlayerVM
{
 public:
  ~PlayerVM();
  PlayerVM();
 
 void AddHealthChangedListener(Callable listener);
 int32_t GetHealth() const { return m_health; }
 
 protected:
  friend class PlayerData;

  void NotifyHealthChanged(int32_t newHealth);

 private:
  Vector<Callable> m_onHealthChangedListeners;

  int32_t m_health = 100;
};