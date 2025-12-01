#include "SkillBase.h"

using namespace godot;

void SkillNode::_bind_methods()
{
  UtilityFunctions::print("SkillNode::_bind_methods called");
}

void SkillResource::_bind_methods() {}

void SkillSet::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("GetSkills"), &SkillSet::GetSkills);
  ClassDB::bind_method(D_METHOD("SetSkills", "skills"), &SkillSet::SetSkills);

  ClassDB::bind_method(D_METHOD("ForEachSkill", "func"), &SkillSet::ForEachSkill);

  ADD_PROPERTY(PropertyInfo(Variant::ARRAY,
                            "m_skills",
                            PROPERTY_HINT_ARRAY_TYPE,
                            "SkillResource"),
               "SetSkills",
               "GetSkills");
}

SkillNode::SkillNode() {}

void SkillNode::init(Node *owner) {}

void SkillNode::execute() {}

void SkillSet::ForEachSkill(const Callable& func) const
{
  if (!func.is_valid())
  {
    UtilityFunctions::push_warning("SkillSet::ForEachSkill called with invalid Callable");
    return;
  }

  for (int i = 0; i < m_skills.size(); ++i)
  {
    Variant skillVariant = m_skills[i];
    func.call(skillVariant);
  }
}