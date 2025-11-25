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

protected:
  static void _bind_methods();

private:
  float m_speed = 8.0f;
};
