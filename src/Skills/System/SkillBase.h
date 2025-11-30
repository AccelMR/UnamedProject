#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class SkillResource : public Resource
{
  GDCLASS(SkillResource, Resource);
 protected:
  static void _bind_methods();
};

class ISkillBase
{
 public:
  ISkillBase() = default;
  virtual ~ISkillBase() = default;

  virtual void init(Node* owner) = 0;
  virtual void execute() = 0;
  virtual Node* getOwner() const = 0;
  virtual Ref<SkillResource> getSkillResource() const = 0;
};

class SkillNode : public Node, public ISkillBase
{
  GDCLASS(SkillNode, Node);
 public:
  SkillNode();
  virtual ~SkillNode() = default;

  void init(Node* owner) override;
  void execute() override;
  Node* getOwner() const override { return nullptr; }
  Ref<SkillResource> getSkillResource() const override { return nullptr; }

 protected:
  static void _bind_methods();
};