#include "UI/PlayerUI.h"

#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/input_event.hpp>

#include "Skills/System/SkillBase.h"
#include "Skills/System/SkillSet.h"

using namespace godot;

void PlayerUI::_bind_methods() 
{
  ClassDB::bind_method(D_METHOD("CreateSkillButton", "skillResource"), &PlayerUI::CreateSkillButton);
}

void PlayerUI::_ready()
{
  m_skillList = get_node<ItemList>("SkillList");
  if (!m_skillList)
  {
    UtilityFunctions::push_warning("PlayerUI: SkillList not found!");
    return;
  }
}

void PlayerUI::PopulateSkillList(const SkillSet* skillSet)
{
  if (!skillSet || !m_skillList)
  {
    UtilityFunctions::push_warning("PlayerUI: SkillSet not found!");
    return;
  }

  if (!skillSet->AreSkillsInstantiated())
  {
    UtilityFunctions::push_warning("PlayerUI: SkillSet skills not instantiated!");
    return;
  }

  m_skillList->clear();
  skillSet->ForEachSkillNode(Callable(this, "CreateSkillButton"));
}

void PlayerUI::CreateSkillButton(const SkillNode* skillNode)
{
  if (!skillNode)
  {
    UtilityFunctions::push_warning("PlayerUI: Invalid SkillNode!");
    return;
  }
  Ref<SkillResource> skillResource = skillNode->GetSkillResource();
  if (!skillResource.is_valid())
  {
    UtilityFunctions::push_warning("PlayerUI: SkillNode has invalid SkillResource!");
    return;
  }
  
  String skillName = skillResource->GetName();
  Ref<Texture2D> skillIcon = skillResource->GetIcon();
  if (!skillIcon.is_valid())
  {
    m_skillList->add_item(skillName, skillIcon);
    UtilityFunctions::print("PlayerUI: Added skill button for " + skillName);
  }
  else
  {
    m_skillList->add_item(skillName);
    UtilityFunctions::push_warning("PlayerUI: SkillResource has no valid icon!");
  }
}
