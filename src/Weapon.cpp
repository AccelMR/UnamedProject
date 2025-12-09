#include "Weapon.h"
#include "Projectile.h"

#include <godot_cpp/classes/box_shape3d.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/string.hpp>

void Weapon::_bind_methods()
{
  //Register methods.
  ClassDB::bind_method(D_METHOD("setBaseDamage", "_newDamage"), &Weapon::SetBaseDamage);
  ClassDB::bind_method(D_METHOD("getBaseDamage"), &Weapon::GetBaseDamage);

  ClassDB::bind_method(D_METHOD("setWeaponType", "_newType"), &Weapon::SetWeaponType);
  ClassDB::bind_method(D_METHOD("getWeaponType"), &Weapon::GetWeaponType);

  //Add properties to the inspector.
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT,
               "baseDamage",
               PROPERTY_HINT_RANGE,
               "0,100,0.1"),
               "setBaseDamage",
               "getBaseDamage");

  ADD_PROPERTY(PropertyInfo(Variant::INT,
               "weaponType",
               PROPERTY_HINT_ENUM,
               "Melee:1,Range:2"),
               "setWeaponType",
               "getWeaponType");
}

void Weapon::_ready()
{
  //mesh = get_node<MeshInstance3D>("MeshInstance3D");
  //collision = get_node<CollisionShape3D>("CollisionShape3D");
  m_projectileSpawnPoint = get_node<Node3D>("ProjectileSpawnPoint");
}

void Weapon::_physics_process(double delta)
{
  
}

void Weapon::Attack(Vector3 direction)
{
  UtilityFunctions::print("Attacked!");

  if(m_weaponType == WEAPON_TYPE_MELEE)
  {
    UtilityFunctions::print("Attacked with melee weapon!");

    Ref<BoxShape3D> meleeCollider;
    meleeCollider.instantiate();
    meleeCollider->set_size(Vector3(1, 0.2f, 1));
    CollisionShape3D* meleeHitbox = memnew(CollisionShape3D());
    meleeHitbox->set_shape(meleeCollider);
    meleeHitbox->set_name("MeleeHitbox");
    meleeHitbox->set_global_transform(m_projectileSpawnPoint->get_global_transform());
    add_child(meleeHitbox);
    meleeHitbox->set_owner(this);
  }

  if(m_weaponType == WEAPON_TYPE_RANGE)
  {
    UtilityFunctions::print("Attacked with ranged weapon!");

    //Instantiate a projectile. Now it is a godot prefab/scene called Projectile.tscn
    godot::String projectileScenePath = "res://Prefabs/Projectile.tscn";
    Ref<PackedScene> projectileScene = ResourceLoader::get_singleton()->load(projectileScenePath);

    if (!projectileScene.is_valid())
    {
      UtilityFunctions::print("Failed to load projectile scene from path: " + projectileScenePath);
      return;
    }

    Node3D* projectileInstance = Object::cast_to<Node3D>(projectileScene->instantiate());

    if (!projectileInstance)
    {
      UtilityFunctions::print("Failed to instantiate projectile scene!");
      return;
    }

    UtilityFunctions::print("Projectile instantiated successfully.");

    //Cast the instance to Projectile type

    Projectile* projectile = Object::cast_to<Projectile>(projectileInstance);
    
    if (!projectile)
    {
      UtilityFunctions::print("Failed to cast projectile instance to Projectile type!");
      return;
    }
    
    //Set projectile position and direction
    projectile->set_global_transform(m_projectileSpawnPoint->get_global_transform());
    projectile->SetDirection(direction);
    projectile->SetSpeed(5.0f);

    //Add the projectile to the scene tree
    SceneTree* tree = get_tree();
    if(!tree)
    {
      UtilityFunctions::print("Failed to get SceneTree!");
      return;
    }
    
    tree->get_current_scene()->call_deferred("add_child", projectile);

    m_activeProjectiles.push_back(projectile);

    UtilityFunctions::print("Projectile launched!");
  }

}
