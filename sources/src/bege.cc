#include <bege/bege.hh>

using namespace godot;

void initialize_bege(ModuleInitializationLevel pLevel)
{
    if (pLevel != MODULE_INITIALIZATION_LEVEL_CORE) { return; }

    // entry primary
    {
    }

    // entry objects
    {
    }

    // entry nodes
    {
    }

    UtilityFunctions::print("-- [bege]: initialized");
}

void terminate_bege(ModuleInitializationLevel pLevel)
{
    if (pLevel != MODULE_INITIALIZATION_LEVEL_CORE) { return; }

    // entry primary
    {
    }

    // entry objects
    {
    }

    // entry nodes
    {
    }

    UtilityFunctions::print("-- [bege]: terminated");
}

extern "C"
{
    // bege runtime
    GDExtensionBool bege_entry_rt(GDExtensionInterfaceGetProcAddress get_proc_address, GDExtensionClassLibraryPtr library, GDExtensionInitialization *ptr_initialization)
    {
        GDExtensionBinding::InitObject init_object(get_proc_address, library, ptr_initialization);

        init_object.register_initializer(initialize_bege);
        init_object.register_terminator(terminate_bege);

        init_object.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_CORE);

        return init_object.init();
    }
}