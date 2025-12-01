#include "Skills/3DNodes/FireCone.h"

#include "Skills/SkillFireCone.h"

#include <godot_cpp/classes/box_shape3d.hpp>
#include <godot_cpp/classes/particle_process_material.hpp>
#include <godot_cpp/classes/gpu_particles3d.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>

using namespace godot;


void FireCone::_bind_methods() 
{
  ClassDB::bind_method(D_METHOD("ActivateFor", "duration"), &FireCone::ActivateFor);
  ClassDB::bind_method(D_METHOD("IsActive"), &FireCone::IsActive);

  ClassDB::bind_method(D_METHOD("OnTimerTimeout"), &FireCone::OnTimerTimeout);
}

void FireCone::SetupCone(const FireConeData& data)
{
  if (!m_damageArea)
  {
    m_damageArea = memnew(Area3D);
    call_deferred("add_child", m_damageArea);
  }

  if (!m_collisionShape)
  {
    m_collisionShape = memnew(CollisionShape3D);
    m_damageArea->call_deferred("add_child", m_collisionShape);
  }

  Ref<Shape3D> shape = m_collisionShape->get_shape();
  Ref<BoxShape3D> boxShape = shape;
  if (!boxShape.is_valid())
  {
    boxShape.instantiate();
    m_collisionShape->set_shape(boxShape);
  }

  const float halfAngleRad = Math::deg_to_rad(data.coneAngle * 0.5f);
  const float radius = data.coneLength * Math::tan(halfAngleRad);
  const float height = 1.0f;

  Vector3 boxExtents(radius * 2.0f, height, data.coneLength);
  boxShape->set_size(boxExtents);

  m_collisionShape->set_position(Vector3(0.0f, 0.0f, -data.coneLength * 0.5f));

  if (!m_timer)
  {
    m_timer = memnew(Timer);
    m_timer->set_one_shot(true);
    call_deferred("add_child", m_timer);

    m_timer->connect("timeout", Callable(this, "OnTimerTimeout"));
  }

  m_isActive = false;

  if (m_damageArea)
  {
    m_damageArea->set_monitorable(false);
    m_damageArea->set_monitoring(false);
  }
  if (m_collisionShape)
  {
    m_collisionShape->set_disabled(true);
  }

   if (!m_fireParticles)
  {
    m_fireParticles = memnew(GPUParticles3D);
    call_deferred("add_child", m_fireParticles);

    m_fireParticles->set_amount(1000);
    m_fireParticles->set_lifetime(1.0f);
    m_fireParticles->set_one_shot(false);
  }
  
  if (data.vfxMaterial.is_valid())
  {
    UtilityFunctions::print("FireCone::SetupCone: Setting up VFX Material for fire particles.");

    Ref<SphereMesh> sphereMesh;
    sphereMesh.instantiate();
    sphereMesh->set_radius(0.3f);
    sphereMesh->set_material(data.vfxMaterial);
  
    data.vfxMaterial->set_color(Color(1.0f, 0.5f, 0.2f, 0.8f));
    m_fireParticles->set_process_material(data.vfxMaterial);
    m_fireParticles->set_draw_pass_mesh(0, sphereMesh);
  }
  else
  {
    UtilityFunctions::push_warning("FireCone::SetupCone: No VFX Material provided for fire particles.");
  }

  m_fireParticles->set_position(m_collisionShape->get_position());
  m_fireParticles->set_emitting(false);
}

void FireCone::ActivateFor(float duration)
{
  if (!m_damageArea || !m_collisionShape || !m_timer)
  {
    UtilityFunctions::push_warning("FireCone::ActivateFor: Components not initialized.");
    return;
  }

  if (!m_timer->is_stopped())
  {
    UtilityFunctions::push_warning("FireCone::ActivateFor: Timer is already running.");
    return;
  }

  if (duration <= 0.0f)
  {
    UtilityFunctions::push_warning("FireCone::ActivateFor: Duration must be positive.");
    return;
  }

  m_isActive = true;
  m_damageArea->set_monitoring(true);
  m_damageArea->set_monitorable(true);
  m_collisionShape->set_disabled(false);

  UtilityFunctions::print("FireCone::ActivateFor: Activating cone for " + String::num(duration) + " seconds.");

  if (m_fireParticles)
  {
    m_fireParticles->set_emitting(true);
  }

  m_timer->start(duration);
}

void FireCone::OnTimerTimeout()
{
  m_isActive = false;

  if (m_damageArea)
  {
    m_damageArea->set_monitoring(false);
    m_damageArea->set_monitorable(false);
  }

  if (m_collisionShape)
  {
    m_collisionShape->set_disabled(true);
  }

  if (m_fireParticles)
  {
    m_fireParticles->set_emitting(false);
  }
}

