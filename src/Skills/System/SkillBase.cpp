#include "Skills/System/SkillBase.h"

using namespace godot;

void SkillNode::_bind_methods()
{
  UtilityFunctions::print("SkillNode::_bind_methods called");
}

void SkillResource::_bind_methods() 
{
  ClassDB::bind_method(D_METHOD("SetName", "name"), &SkillResource::SetName);
  ClassDB::bind_method(D_METHOD("GetName"), &SkillResource::GetName);

  ClassDB::bind_method(D_METHOD("SetDescription", "description"), &SkillResource::SetDescription);
  ClassDB::bind_method(D_METHOD("GetDescription"), &SkillResource::GetDescription);

  ClassDB::bind_method(D_METHOD("SetIcon", "icon"), &SkillResource::SetIcon);
  ClassDB::bind_method(D_METHOD("GetIcon"), &SkillResource::GetIcon);

  ClassDB::bind_method(D_METHOD("SetCooldownTime", "cooldown_time"), &SkillResource::SetCooldownTime);
  ClassDB::bind_method(D_METHOD("GetCooldownTime"), &SkillResource::GetCooldownTime);

  ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "SetName", "GetName");
  ADD_PROPERTY(PropertyInfo(Variant::STRING, "description"), "SetDescription", "GetDescription");
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "SetIcon", "GetIcon");
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "cooldownTime"), "SetCooldownTime", "GetCooldownTime");
}

void PassiveSkillNode::_bind_methods() {}

void ActiveSkillNode::_bind_methods() {}

SkillNode::SkillNode() {}

void SkillNode::Init(Node *owner) {}

void SkillNode::Execute() 
{
  for (const Callable &callback : m_onExecuteCallbacks)
  {
    if (callback.is_valid())
    {
      callback.call();
    }
  }
}

void SkillNode::AddOnExecuteCallback(const Callable &callback)
{
  if (!callback.is_valid())
  {
    UtilityFunctions::push_warning("SkillNode::AddOnExecuteCallback: Invalid callback!");
    return;
  }

  if (!m_onExecuteCallbacks.has(callback))
  {
    m_onExecuteCallbacks.push_back(callback);
  }
}

void SkillNode::RemoveOnExecuteCallback(const StringName &callbackName)
{
  for (int i = 0; i < m_onExecuteCallbacks.size(); ++i)
  {
    const Callable &callback = m_onExecuteCallbacks[i];
    if (callback.is_valid() && callback.get_method() == callbackName)
    {
      m_onExecuteCallbacks.remove_at(i);
      return;
    }
  }
}

void SkillNode::ClearOnExecuteCallbacks()
{
  m_onExecuteCallbacks.clear();
}

void SkillNode::AddOnCooldownCompleteCallback(const Callable &callback)
{
  if (!callback.is_valid())
  {
    UtilityFunctions::push_warning("SkillNode::AddOnCooldownCompleteCallback: Invalid callback!");
    return;
  }

  if (!m_onCooldownCompleteCallbacks.has(callback))
  {
    m_onCooldownCompleteCallbacks.push_back(callback);
  }
}

void SkillNode::RemoveOnCooldownCompleteCallback(const StringName &callbackName)
{
  for (int i = 0; i < m_onCooldownCompleteCallbacks.size(); ++i)
  {
    const Callable &callback = m_onCooldownCompleteCallbacks[i];
    if (callback.is_valid() && callback.get_method() == callbackName)
    {
      m_onCooldownCompleteCallbacks.remove_at(i);
      return;
    }
  }
}

void SkillNode::ClearOnCooldownCompleteCallbacks()
{
  m_onCooldownCompleteCallbacks.clear();
}
