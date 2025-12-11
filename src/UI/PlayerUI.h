#pragma once

#include <godot_cpp/classes/control.hpp>

#include <godot_cpp/classes/item_list.hpp>
#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/label.hpp>

#include <memory>

class PlayerVM;

using namespace godot;

class SkillSet;
class SkillResource;
class SkillNode;
class PlayerVM;

class PlayerUI : public Control
{
  GDCLASS(PlayerUI, Control);

 public:
  PlayerUI() = default;
  ~PlayerUI() = default;

  void _ready() override;

  void PopulateSkillList(const SkillSet* skillSet);

  void BindPlayerVM(const std::shared_ptr<PlayerVM>& viewModel);

 protected:
  static void _bind_methods();

 private:
  void CreateSkillButton(SkillNode* skillNode);

  void OnHealthChanged(int32_t newHealth)
  {
    if (m_healthLabel)
    {
      m_healthLabel->set_text("Health: " + String::num_int64(newHealth));
    }
  }

 private:
  ItemList* m_skillList = nullptr;
  Dictionary m_skillItemIndices;
  HBoxContainer* m_topBar = nullptr;
  Label* m_healthLabel = nullptr;
};