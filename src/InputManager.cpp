#include "InputManager.h"

#include <godot_cpp/core/object.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_joypad_button.hpp>
#include <godot_cpp/classes/input_event_joypad_motion.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>


using namespace godot;

InputManager* InputManager::getGlobalInputManager(Node* context)
{
  if (!context)
  {
    UtilityFunctions::push_warning("InputManager::getGlobalInputManager: context node is null");
    return nullptr;
  }

  InputManager* inputManager = context->get_node<InputManager>("/root/GlobalInputManager");
  if (!inputManager)
  {
    UtilityFunctions::push_warning("Player: Could not find GlobalInputManager node");
    return nullptr;
  }

  return inputManager;
}

void InputManager::_bind_methods()
{
  ADD_SIGNAL(MethodInfo("onModeChanged", 
                        PropertyInfo(Variant::INT, "new_mode"),
                        PropertyInfo(Variant::INT, "old_mode")));
}

void InputManager::SetInputMode(InputMode mode)
{
  if (m_inputMode != mode)
  {
    InputMode oldMode = m_inputMode;
    m_inputMode = mode;
    UtilityFunctions::print("Input mode changed to ", m_inputMode == INPUT_MODE_KVM ? "KVM" : "GAMEPAD");

    // TODO: this emitter doesn't work or I didn't connect it properly(?)
    emit_signal("onModeChanged",
                static_cast<int>(m_inputMode),
                static_cast<int>(oldMode));
  }
}
void InputManager::_input(const Ref<InputEvent> &event)
{
  if (InputEventJoypadButton* joyButton = Object::cast_to<InputEventJoypadButton>(event.ptr()))
  {
    SetInputMode(INPUT_MODE_GAMEPAD);
  }
  else if (InputEventJoypadMotion* joyAxis = Object::cast_to<InputEventJoypadMotion>(event.ptr()))
  {
    // Only change it if there's significant movement
    if (Math::abs(joyAxis->get_axis_value()) > m_gamepadDeadzone)
    {
      SetInputMode(INPUT_MODE_GAMEPAD);
    }
  }

  else if (InputEventKey* key = Object::cast_to<InputEventKey>(event.ptr()))
  {
    SetInputMode(INPUT_MODE_KVM);
  }
  else if (InputEventMouseButton* mouseButton = Object::cast_to<InputEventMouseButton>(event.ptr()))
  {
    SetInputMode(INPUT_MODE_KVM);
  }
  else if (InputEventMouseMotion* mouseMotion = Object::cast_to<InputEventMouseMotion>(event.ptr()))
  {
    SetInputMode(INPUT_MODE_KVM);
  }
}
