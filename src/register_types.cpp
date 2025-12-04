#include "register_types.h"

#include "CameraController.h"
#include "InputManager.h"
#include "MouseMarker.h"
#include "Player.h"
#include "CameraController.h"
#include "Agent.h"
#include "Enemy.h"
#include "MouseMarker.h"

#include "Skills/System/SkillBase.h"
#include "Skills/System/SkillSet.h"

#include "Skills/SkillFireCone.h"
#include "Skills/3DNodes/FireCone.h"

#include "UI/PlayerUI.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_example_module(ModuleInitializationLevel p_level)
{
  if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
  {
    return;
  }

  GDREGISTER_CLASS(SkillResource);
  GDREGISTER_CLASS(FireConeResource);
  GDREGISTER_CLASS(SkillSet);

  GDREGISTER_RUNTIME_CLASS(Agent);
  GDREGISTER_RUNTIME_CLASS(CameraController);
  GDREGISTER_RUNTIME_CLASS(Enemy);
  GDREGISTER_RUNTIME_CLASS(FireCone);
  GDREGISTER_RUNTIME_CLASS(InputManager);
  GDREGISTER_RUNTIME_CLASS(MouseMarker);
  GDREGISTER_RUNTIME_CLASS(Player);
  
  GDREGISTER_RUNTIME_CLASS(SkillNode);
  GDREGISTER_RUNTIME_CLASS(SkillFireCone);

  GDREGISTER_RUNTIME_CLASS(PlayerUI);
}

void uninitialize_example_module(ModuleInitializationLevel p_level)
{
  if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
  {
    return;
  }
}

extern "C"
{
  // Initialization.
  GDExtensionBool GDE_EXPORT example_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
  {
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

    init_obj.register_initializer(initialize_example_module);
    init_obj.register_terminator(uninitialize_example_module);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
  }
}