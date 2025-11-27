#pragma once

#include <godot_cpp/classes/node.hpp>

using namespace godot;
class InputManager : public Node
{
  GDCLASS(InputManager, Node);

 public:

 enum InputMode {
    INPUT_MODE_KVM,
    INPUT_MODE_GAMEPAD
  };

  InputManager() = default;
  ~InputManager() = default;

  InputMode getInputMode() const { return m_inputMode; }
  void setInputMode(InputMode mode);

  void _input(const Ref<InputEvent>& event) override;

 protected:
  static void _bind_methods();

 private:
  InputMode m_inputMode = INPUT_MODE_KVM;

  float m_gamepadDeadzone = 0.2f;
};