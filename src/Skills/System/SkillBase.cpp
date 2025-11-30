#include "SkillBase.h"

using namespace godot;

void SkillNode::_bind_methods() 
{
  UtilityFunctions::print("SkillNode::_bind_methods called");
}

void SkillResource::_bind_methods() {}

SkillNode::SkillNode() {}

void SkillNode::init(Node* owner) {}

void SkillNode::execute() {}