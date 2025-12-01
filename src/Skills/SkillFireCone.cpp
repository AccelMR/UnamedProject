#include "Skills/SkillFireCone.h"

#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/classes/box_shape3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/immediate_mesh.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/scene_tree_timer.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include "Skills/3DNodes/FireCone.h"

using namespace godot;

FireConeData& FireConeData::operator=(Ref<FireConeResource> resource)
{
  if (resource.is_valid())
  {
    coneAngle = resource->getConeAngle();
    coneLength = resource->getConeLength();
    fireDamage = resource->getFireDamage();
    duration = resource->getDuration();
    meshMaterial = resource->GetMeshMaterial();
    vfxMaterial = resource->GetVfxMaterial();
  }
  return *this;
}

void FireConeResource::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("setConeAngle", "angle"), &FireConeResource::setConeAngle);
  ClassDB::bind_method(D_METHOD("getConeAngle"), &FireConeResource::getConeAngle);

  ClassDB::bind_method(D_METHOD("setConeLength", "length"), &FireConeResource::setConeLength);
  ClassDB::bind_method(D_METHOD("getConeLength"), &FireConeResource::getConeLength);

  ClassDB::bind_method(D_METHOD("setFireDamage", "damage"), &FireConeResource::setFireDamage);
  ClassDB::bind_method(D_METHOD("getFireDamage"), &FireConeResource::getFireDamage);

  ClassDB::bind_method(D_METHOD("setDuration", "duration"), &FireConeResource::setDuration);
  ClassDB::bind_method(D_METHOD("getDuration"), &FireConeResource::getDuration);

  ClassDB::bind_method(D_METHOD("SetVfxMaterial", "material"), &FireConeResource::SetVfxMaterial);
  ClassDB::bind_method(D_METHOD("GetVfxMaterial"), &FireConeResource::GetVfxMaterial);

  ClassDB::bind_method(D_METHOD("SetMeshMaterial", "material"), &FireConeResource::SetMeshMaterial);
  ClassDB::bind_method(D_METHOD("GetMeshMaterial"), &FireConeResource::GetMeshMaterial);

  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "coneAngle"), "setConeAngle", "getConeAngle");
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "coneLength"), "setConeLength", "getConeLength");
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "fireDamage"), "setFireDamage", "getFireDamage");
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "duration"), "setDuration", "getDuration");

  ADD_PROPERTY(
      PropertyInfo(
          Variant::OBJECT,
          "vfxMaterial",
          PROPERTY_HINT_RESOURCE_TYPE, 
          "ParticleProcessMaterial"),
      "SetVfxMaterial",
      "GetVfxMaterial");

  ADD_PROPERTY(
      PropertyInfo(
          Variant::OBJECT,
          "meshMaterial",
          PROPERTY_HINT_RESOURCE_TYPE, 
          "StandardMaterial3D"),
      "SetMeshMaterial",
      "GetMeshMaterial");
}

void SkillFireCone::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("setSkillResource", "resource"), &SkillFireCone::setSkillResource);
  ClassDB::bind_method(D_METHOD("getSkillResource"), &SkillFireCone::getSkillResource);

  ADD_PROPERTY(
      PropertyInfo(Variant::OBJECT, "SkillResource", PROPERTY_HINT_RESOURCE_TYPE, "FireConeResource"),
      "setSkillResource", "getSkillResource");
}

SkillNode* FireConeResource::CreateSkillNodeForThisResource()
{
  UtilityFunctions::print("FireConeResource::CreateSkillNodeForThisResource called");
  SkillFireCone* skillNode = memnew(SkillFireCone);
  skillNode->setSkillResource(Ref<FireConeResource>(this));
  return skillNode;
}

void SkillFireCone::init(Node *owner)
{
  m_owner = owner;
  if (m_skillResource.is_valid())
  {
    m_fireConeData = m_skillResource;
  }
  else
  {
    UtilityFunctions::push_warning("SkillFireCone::init: SkillResource is not valid.");
  }

  // Create the FireCone node
  if (!m_fireConeNode && m_owner)
  {
    m_fireConeNode = memnew(FireCone);

    // Add the fire cone to the owner node
    m_owner->call_deferred("add_child", m_fireConeNode);

    m_fireConeNode->SetupCone(m_fireConeData);

    UtilityFunctions::print("SkillFireCone::init: FireCone node created and added to owner.");
    UtilityFunctions::print("  Cone Angle: " + String::num(m_fireConeData.coneAngle));
    UtilityFunctions::print("  Cone Length: " + String::num(m_fireConeData.coneLength));
    UtilityFunctions::print("  Fire Damage: " + String::num(m_fireConeData.fireDamage));
    UtilityFunctions::print("  Duration: " + String::num(m_fireConeData.duration));
  }
}

void SkillFireCone::execute()
{
  if (!m_fireConeNode)
  {
    UtilityFunctions::push_warning("SkillFireCone::execute: FireCone node is null.");
    return;
  }

  if (m_fireConeNode->IsActive())
  {
    UtilityFunctions::push_warning("SkillFireCone::execute: FireCone already active, ignoring.");
    return;
  }

  m_fireConeNode->ActivateFor(m_fireConeData.duration);
}
