#include "AgentStats.h"

using namespace godot;

void AgentBaseStatsResource::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("GetHealth"), &AgentBaseStatsResource::GetHealth);
  ClassDB::bind_method(D_METHOD("SetHealth", "health"), &AgentBaseStatsResource::SetHealth);
  ClassDB::bind_method(D_METHOD("GetStamina"), &AgentBaseStatsResource::GetStamina);
  ClassDB::bind_method(D_METHOD("SetStamina", "stamina"), &AgentBaseStatsResource::SetStamina);
  ClassDB::bind_method(D_METHOD("GetBaseDamage"), &AgentBaseStatsResource::GetBaseDamage);
  ClassDB::bind_method(D_METHOD("SetBaseDamage", "damage"), &AgentBaseStatsResource::SetBaseDamage);

  ADD_PROPERTY(PropertyInfo(Variant::INT, "health"), "SetHealth", "GetHealth");
  ADD_PROPERTY(PropertyInfo(Variant::INT, "stamina"), "SetStamina", "GetStamina");
  ADD_PROPERTY(PropertyInfo(Variant::INT, "baseDamage"), "SetBaseDamage", "GetBaseDamage");
}

bool AgentBaseStats::Initialize(const Ref<AgentBaseStatsResource>& resource)
{
  if (!resource.is_valid())
  {
    UtilityFunctions::print("Invalid AgentBaseStatsResource provided to AgentBaseStats::Initialize");
    return false;
  }
  m_health = resource->GetHealth();
  m_stamina = resource->GetStamina();
  m_baseDamage = resource->GetBaseDamage();

  m_maxHealth = m_health;
  m_maxStamina = m_stamina;

  return true;
}

