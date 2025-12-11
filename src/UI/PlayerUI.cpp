#include "UI/PlayerUI.h"

#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/input_event.hpp>

#include "Skills/System/SkillBase.h"
#include "Skills/System/SkillSet.h"

#include "UI/ViewModels/PlayerVM.h"

using namespace godot;

void PlayerUI::_bind_methods() 
{
  ClassDB::bind_method(D_METHOD("CreateSkillButton", "skillResource"), &PlayerUI::CreateSkillButton);
  ClassDB::bind_method(D_METHOD("OnHealthChanged", "newHealth"), &PlayerUI::OnHealthChanged);
}

void PlayerUI::_ready()
{
  m_skillList = get_node<ItemList>("SkillList");
  DEV_ASSERT(m_skillList);

  m_topBar = get_node<HBoxContainer>("TopBar");
  DEV_ASSERT(m_topBar);

  m_healthLabel = m_topBar->get_node<Label>("HealthLabel");
  DEV_ASSERT(m_healthLabel);
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

void PlayerUI::BindPlayerVM(const std::shared_ptr<PlayerVM>& viewModel)
{
  if (!viewModel)
  {
    UtilityFunctions::push_warning("PlayerUI: Invalid PlayerVM!");
    return;
  }
  // Subscribe to health changes
  viewModel->AddHealthChangedListener(Callable(this, "OnHealthChanged"));
  OnHealthChanged(viewModel->GetHealth());
}

void PlayerUI::CreateSkillButton(SkillNode* skillNode)
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
  
  int32_t itemIndex = -1;

  String skillName = skillResource->GetName();
  Ref<Texture2D> skillIcon = skillResource->GetIcon();
  if (skillIcon.is_valid())
  {
    itemIndex = m_skillList->add_item(skillName, skillIcon);
    UtilityFunctions::print("PlayerUI: Added skill button for " + skillName);
  }
  else
  {
    itemIndex = m_skillList->add_item(skillName);
    UtilityFunctions::push_warning("PlayerUI: SkillResource has no valid icon!");
  }

  m_skillItemIndices[skillNode] = itemIndex;

  if (itemIndex != -1)
  {
    skillNode->AddOnExecuteCallback(Callable(m_skillList, "set_item_disabled").bind(itemIndex, true));
    skillNode->AddOnCooldownCompleteCallback(Callable(m_skillList, "set_item_disabled").bind(itemIndex, false));
  }
}
