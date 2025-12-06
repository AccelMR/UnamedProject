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

  ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "SetName", "GetName");
  ADD_PROPERTY(PropertyInfo(Variant::STRING, "description"), "SetDescription", "GetDescription");
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "SetIcon", "GetIcon");
}

SkillNode::SkillNode() {}

void SkillNode::Init(Node *owner) {}

void SkillNode::Execute() {}