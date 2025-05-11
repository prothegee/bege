#include <bege/bege.hh>

#include <bege/objects/bege_console.hh>

#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void initialize_bege(ModuleInitializationLevel pLevel) {
    if (pLevel != MODULE_INITIALIZATION_LEVEL_CORE) {
        return;
    }

    // godot engine ptr
    auto p_engine = Engine::get_singleton();

    // entry primary
    {
    }

    // entry objects
    {
        GDREGISTER_CLASS(bege_console);
        if (!p_bege_console) { p_bege_console = memnew(bege_console); }
        p_engine->register_singleton(bege_console_CLASS, p_bege_console);
    }

    // entry nodes
    {
    }

    bege::console::log("initialized");
}

void terminate_bege(ModuleInitializationLevel pLevel) {
    if (pLevel != MODULE_INITIALIZATION_LEVEL_CORE) {
        return;
    }

    // godot engine ptr
    auto p_engine = Engine::get_singleton();

    // entry primary
    {
    }

    // entry objects
    {
        if (p_bege_console) { memdelete(p_bege_console); }
        p_engine->unregister_singleton(bege_console_CLASS);
    }

    // entry nodes
    {
    }

    bege::console::log("terminated");
}

extern "C" {
// bege entry runtime
GDExtensionBool GDE_EXPORT
bege_entry_rt(GDExtensionInterfaceGetProcAddress get_proc_address, GDExtensionClassLibraryPtr library, GDExtensionInitialization* ptr_initialization) {
    GDExtensionBinding::InitObject init_object(get_proc_address, library, ptr_initialization);

    init_object.register_initializer(initialize_bege);
    init_object.register_terminator(terminate_bege);

    init_object.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_CORE);

    return init_object.init();
}
} // extern "C"