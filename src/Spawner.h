#pragma once

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

using namespace godot;

class Spawner : public Node3D
{
    GDCLASS(Spawner, Node3D);

public:
  // Start
  void _ready() override;

  // Update
  void _process(double delta) override;

  // Editor bind methods
  float GetSpawnTime() const { return m_spawnTime; }
  void SetSpawnTime(float time) { m_spawnTime = time; }

  void SpawnEnemy();

  // Callbacks
  void OnTimeOut();

protected:
  static void _bind_methods();

private:
  Timer* m_timer;
  bool m_isActive;

  Ref<PackedScene> m_enemyPrefab;

  // Editor exposed variables
  float m_spawnTime = 5.0f;
};