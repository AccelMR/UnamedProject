#pragma once

#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/input_event.hpp>

using namespace godot;

class CameraController : public Camera3D
{
  GDCLASS(CameraController, Camera3D);

public:
  CameraController() = default;
  ~CameraController() = default;

  void _ready() override;
  void _physics_process(double delta) override;

  float getSpeed() const { return m_speed; }
  void setSpeed(float speed) { m_speed = speed; }

  float getZoomSpeed() const { return m_zoomSpeed; }
  void setZoomSpeed(float zoomSpeed) { m_zoomSpeed = zoomSpeed; }

protected:
  static void _bind_methods();

private:
  // Expose to editor
  float m_speed = 8.0f;
  float m_zoomSpeed = 4.0f;
};
