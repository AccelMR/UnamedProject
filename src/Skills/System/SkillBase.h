#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/texture2d.hpp>

using namespace godot;

class SkillNode;

class SkillResource : public Resource
{
  GDCLASS(SkillResource, Resource);

 public:
  virtual SkillNode* CreateSkillNodeForThisResource(Node*) { return nullptr; }

  void SetName(const String& name) { m_name = name; }
  String GetName() const { return m_name; }

  void SetDescription(const String& description) { m_description = description; }
  String GetDescription() const { return m_description; }

  void SetIcon(const Ref<Texture2D>& icon) { m_icon = icon; }
  Ref<Texture2D> GetIcon() const { return m_icon; }

 protected:
  static void _bind_methods();

 private:
  String m_name;
  String m_description;
  Ref<Texture2D> m_icon;
};

class ISkillBase
{
 public:
  ISkillBase() = default;
  virtual ~ISkillBase() = default;

  virtual void Init(Node* owner) = 0;
  virtual void Execute() = 0;
  virtual Node* GetOwner() const = 0;
  virtual Ref<SkillResource> GetSkillResource() const = 0;
};

class SkillNode : public Node, public ISkillBase
{
  GDCLASS(SkillNode, Node);
 public:
  SkillNode();
  virtual ~SkillNode() = default;

  void Init(Node* owner) override;
  void Execute() override;
  Node* GetOwner() const override { return nullptr; }
  Ref<SkillResource> GetSkillResource() const override { return nullptr; }

 protected:
  static void _bind_methods();
};

class PassiveSkillNode : public SkillNode
{
  GDCLASS(PassiveSkillNode, SkillNode);
 public:
  PassiveSkillNode() = default;
  virtual ~PassiveSkillNode() = default;

 protected:
  static void _bind_methods();
};

class ActiveSkillNode : public SkillNode
{
  GDCLASS(ActiveSkillNode, SkillNode);
 public:
  ActiveSkillNode() = default;
  virtual ~ActiveSkillNode() = default;

 protected:
  static void _bind_methods();
};

