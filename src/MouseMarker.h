#pragma once

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>

using namespace godot;

class MouseMarker : public Node3D
{
  GDCLASS(MouseMarker, Node3D);

 public:
  MouseMarker() = default;
  ~MouseMarker() = default;

  void _ready() override;
  void _process(double delta) override;

  void UpdateMarkerPosition(const Vector3& position);

  float GetMarkShrinkSpeed() const { return m_markShrinkSpeed; }
  void SetMarkShrinkSpeed(float speed) { m_markShrinkSpeed = speed; }

 protected:
  static void _bind_methods();

 private:
  bool m_bIsMarkJustPlaced = false;

  float m_markShrinkSpeed = 1.0f;
};
