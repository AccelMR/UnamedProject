#pragma once

#include "Skills/System/SkillBase.h"

#include <godot_cpp/classes/particle_process_material.hpp>

using namespace godot;

class FireCone;

struct FireConeData
{
  float coneAngle = 45.0f;
  float coneLength = 10.0f;
  float fireDamage = 25.0f;
  float duration = 1.0f;

  Ref<ParticleProcessMaterial> vfxMaterial;
};

class FireConeResource : public SkillResource
{
  GDCLASS(FireConeResource, SkillResource);
 public:
  FireConeResource() = default;
  virtual ~FireConeResource() = default;

  float getConeAngle() const { return  m_data.coneAngle; }
  void setConeAngle(float angle) { m_data.coneAngle = angle; }

  float getConeLength() const { return m_data.coneLength; }
  void setConeLength(float length) { m_data.coneLength = length; }

  void setFireDamage(float damage) { m_data.fireDamage = damage; }
  float getFireDamage() const { return m_data.fireDamage; }

  float getDuration() const { return m_data.duration; }
  void setDuration(float duration) { m_data.duration = duration; }

  Ref<ParticleProcessMaterial> GetVfxMaterial() const { return m_data.vfxMaterial; }
  void SetVfxMaterial(const Ref<ParticleProcessMaterial>& material) { m_data.vfxMaterial = material; }

  SkillNode* CreateSkillNodeForThisResource() override;

 protected:
  static void _bind_methods();

 private:
  FireConeData m_data;
};

class SkillFireCone : public SkillNode
{
  GDCLASS(SkillFireCone, SkillNode);

 public:
  SkillFireCone() = default;
  ~SkillFireCone() override = default;

  void init(Node* owner) override;
  void execute() override;
  Node* getOwner() const override { return m_owner; }

  Ref<SkillResource> getSkillResource() const override { return m_skillResource; }
  void setSkillResource(const Ref<FireConeResource>& resource) { m_skillResource = resource; }

  // Debug:
  void drawDebugCone();

 protected:
  static void _bind_methods();

 private:
  Node* m_owner = nullptr;
  FireCone* m_fireConeNode = nullptr;
  Ref<FireConeResource> m_skillResource;
  FireConeData m_fireConeData;
};

