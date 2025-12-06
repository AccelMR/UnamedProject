#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/typed_array.hpp>

using namespace godot;

class ActiveSkillNode;
class SkillResource;
class SkillNode;

class SkillSet : public Resource
{
  GDCLASS(SkillSet, Resource);

 public:

  TypedArray<SkillResource> GetSkills() const { return m_skills; }
  void SetSkills(const TypedArray<SkillResource>& skills) { m_skills = skills; }

  bool AreSkillsInstantiated() const { return m_areSkillNodesInstantiated; }
  void InstantiateSkills(Node* owner);

  void ForEachSkillNode(const Callable& callback) const;

  Vector<ActiveSkillNode*> GetActiveSkills() const;

 protected:
  static void _bind_methods();

 private:
  TypedArray<SkillResource> m_skills;
  Vector<SkillNode*> m_skillNodes;

  bool m_areSkillNodesInstantiated = false;
};