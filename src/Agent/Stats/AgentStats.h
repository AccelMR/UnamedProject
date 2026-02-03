#pragma once

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/resource.hpp>

#include <functional>

using namespace godot;

class AgentBaseStatsResource : public Resource {
  GDCLASS(AgentBaseStatsResource, Resource);
 public:
  AgentBaseStatsResource() = default;
  ~AgentBaseStatsResource() = default;

  int32_t GetHealth() const { return m_health; }
  void SetHealth(int32_t health) { m_health = health; }

  int32_t GetStamina() const { return m_stamina; }
  void SetStamina(int32_t stamina) { m_stamina = stamina; }

  int32_t GetBaseDamage() const { return m_baseDamage; }
  void SetBaseDamage(int32_t damage) { m_baseDamage = damage; }

 protected:
  static void _bind_methods();

 private:
  int32_t m_health = 100;
  int32_t m_stamina = 100;
  int32_t m_baseDamage = 10;
};


class AgentBaseStats {
 public:
  AgentBaseStats() = default;
  ~AgentBaseStats() = default;

  bool Initialize(const Ref<AgentBaseStatsResource>& resource);

  int32_t GetHealth() const { return m_health; }
  void SetHealth(int32_t health) 
  { 
    m_health = health; 
    if (OnHealthChanged)
    {
      OnHealthChanged(m_health);
    }
  }

  int32_t GetStamina() const { return m_stamina; }
  void SetStamina(int32_t stamina) 
  { 
    m_stamina = stamina; 
    if (OnStaminaChanged)
    {
      OnStaminaChanged(m_stamina);
    }
  }

  int32_t GetBaseDamage() const { return m_baseDamage; }
  void SetBaseDamage(int32_t damage)
  {
    m_baseDamage = damage;
    if (OnBaseDamageChanged)
    {
      OnBaseDamageChanged(m_baseDamage);
    }
  }

  std::function<void(int32_t)> OnHealthChanged;
  std::function<void(int32_t)> OnStaminaChanged;
  std::function<void(int32_t)> OnBaseDamageChanged;

 private:
  int32_t m_health = 100;
  int32_t m_stamina = 100;
  int32_t m_baseDamage = 10;

  int32_t m_maxHealth = 100;
  int32_t m_maxStamina = 100;
};