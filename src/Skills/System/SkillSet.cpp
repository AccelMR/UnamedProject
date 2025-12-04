#include "Skills/System/SkillSet.h"

#include "Skills/System/SkillBase.h"

using namespace godot;

void SkillSet::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("GetSkills"), &SkillSet::GetSkills);
  ClassDB::bind_method(D_METHOD("SetSkills", "skills"), &SkillSet::SetSkills);

  ClassDB::bind_method(D_METHOD("ForEachSkillNode", "callback"), &SkillSet::ForEachSkillNode);
  ClassDB::bind_method(D_METHOD("InstantiateSkills", "owner"), &SkillSet::InstantiateSkills);

  ADD_PROPERTY(PropertyInfo(Variant::ARRAY,
                            "m_skills",
                            PROPERTY_HINT_ARRAY_TYPE,
                            "SkillResource"),
               "SetSkills",
               "GetSkills");
}

void SkillSet::InstantiateSkills(Node* owner)
{
  if (m_areSkillNodesInstantiated)
  {
    UtilityFunctions::print("SkillSet::InstantiateSkills: Skills already instantiated.");
    return;
  }

  if (!owner)
  {
    UtilityFunctions::push_warning("SkillSet::InstantiateSkills: Owner node is null!");
    return;
  }

  m_skillNodes.clear();

  for (int32_t i = 0; i < m_skills.size(); ++i)
  {
    Ref<SkillResource> skillRes = m_skills[i];
    if (skillRes.is_valid())
    {
      SkillNode* skillNode = skillRes->CreateSkillNodeForThisResource(owner);
      if (skillNode)
      {
        m_skillNodes.append(skillNode);
        owner->call_deferred("add_child", skillNode);
      }
    }
  }

  m_areSkillNodesInstantiated = true;
}

void SkillSet::ForEachSkillNode(const Callable& callback) const
{
  if (!callback.is_valid())
  {
    UtilityFunctions::push_warning("SkillSet::ForEachSkillNode: Invalid callback!");
    return;
  }

  if (!m_areSkillNodesInstantiated)
  {
    UtilityFunctions::push_warning("SkillSet::ForEachSkillNode: Skills not instantiated!");
    return;
  }

  for (int32_t i = 0; i < m_skillNodes.size(); ++i)
  {
    SkillNode* skillNode = Object::cast_to<SkillNode>(m_skillNodes[i]);
    if (skillNode)
    {
      callback.call(skillNode);
    }
  }
}
