#include "Spawner.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

void Spawner::_bind_methods()
{
  // Callbacks
  ClassDB::bind_method(D_METHOD("OnTimeOut"), &Spawner::OnTimeOut);

  // Exposed variables  
  ClassDB::bind_method(D_METHOD("GetSpawnTime"), &Spawner::GetSpawnTime);
  ClassDB::bind_method(D_METHOD("SetSpawnTime", "time"), &Spawner::SetSpawnTime);

  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spawnTime"), 
               "SetSpawnTime", "GetSpawnTime");
}

void Spawner::_ready()
{
    // Create timer
    m_timer = memnew(Timer);
    m_timer->set_wait_time(m_spawnTime);
    m_timer->set_one_shot(false);
    add_child(m_timer);
    m_timer->connect("timeout", Callable(this, "OnTimeOut"));

    m_isActive = false;

    m_enemyPrefab = ResourceLoader::get_singleton()->load("res://Prefabs//enemy.tscn");
}

void Spawner::_process(double delta)
{
    if(!m_isActive)
    {
        m_timer->start();
        m_isActive = true;
    }
}

void Spawner::SpawnEnemy()
{
        Node *instance = m_enemyPrefab->instantiate();
        
        // VERY IMPORTANT: Make it saved in the scene
        Node *scene_root = get_tree()->get_current_scene();
        if (scene_root)
            scene_root->add_child(instance);
}

void Spawner::OnTimeOut()
{
    SpawnEnemy();
}
