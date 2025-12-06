#pragma once

#include <godot_cpp/classes/control.hpp>

#include <godot_cpp/classes/item_list.hpp>
using namespace godot;

class SkillSet;
class SkillResource;
class SkillNode;

class PlayerUI : public Control
{
  GDCLASS(PlayerUI, Control);

 public:
  PlayerUI() = default;
  ~PlayerUI() = default;

  void _ready() override;

  void PopulateSkillList(const SkillSet* skillSet);

 protected:
  static void _bind_methods();

 private:
  void CreateSkillButton(SkillNode* skillNode);

 private:
  ItemList* m_skillList = nullptr;
  Dictionary m_skillItemIndices;
};