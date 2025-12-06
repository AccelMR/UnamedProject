#pragma once

#include "Skills/System/SkillBase.h"

#include <godot_cpp/classes/particle_process_material.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>

using namespace godot;

class FireCone;
class FireConeResource;

struct FireConeData
{
  float coneAngle = 45.0f;
  float coneLength = 10.0f;
  float fireDamage = 25.0f;
  float duration = 1.0f;

  Ref<StandardMaterial3D> meshMaterial;
  Ref<ParticleProcessMaterial> vfxMaterial;

  FireConeData& operator=(Ref<FireConeResource> resource);
};

class FireConeResource : public SkillResource
{
  GDCLASS(FireConeResource, SkillResource);
 public:
  FireConeResource() = default;
  virtual ~FireConeResource() = default;

  float GetConeAngle() const { return  m_data.coneAngle; }
  void SetConeAngle(float angle) { m_data.coneAngle = angle; }

  float GetConeLength() const { return m_data.coneLength; }
  void SetConeLength(float length) { m_data.coneLength = length; }

  void SetFireDamage(float damage) { m_data.fireDamage = damage; }
  float GetFireDamage() const { return m_data.fireDamage; }

  float GetDuration() const { return m_data.duration; }
  void SetDuration(float duration) { m_data.duration = duration; }

  Ref<StandardMaterial3D> GetMeshMaterial() const { return m_data.meshMaterial; }
  void SetMeshMaterial(const Ref<StandardMaterial3D>& material) { m_data.meshMaterial = material; }

  Ref<ParticleProcessMaterial> GetVfxMaterial() const { return m_data.vfxMaterial; }
  void SetVfxMaterial(const Ref<ParticleProcessMaterial>& material) { m_data.vfxMaterial = material; }

  SkillNode* CreateSkillNodeForThisResource(Node* owner) override;

 protected:
  static void _bind_methods();

 private:
  FireConeData m_data;
};

class SkillFireCone : public ActiveSkillNode
{
  GDCLASS(SkillFireCone, ActiveSkillNode);

 public:

  SkillFireCone() = default;
  ~SkillFireCone() override = default;

  void Execute() override;
  Node* GetOwner() const override { return m_owner; }
  
  Ref<SkillResource> GetSkillResource() const override { return m_skillResource; }
  void SetSkillResource(const Ref<FireConeResource>& resource) { m_skillResource = resource; }
  
 protected:
  friend class FireConeResource;

  static void _bind_methods();
  
  void Init(Node* owner) override;

 private:
  Node* m_owner = nullptr;
  FireCone* m_fireConeNode = nullptr;
  Ref<FireConeResource> m_skillResource;
  FireConeData m_fireConeData;
};

