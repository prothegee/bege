#include <bege/objects/bege_console.hh>

#include <godot_cpp/classes/os.hpp>

void bege_console::_bind_methods() {
    ClassDB::bind_method(D_METHOD("is_bege_console"), &bege_console::is_bege_console);

    ClassDB::bind_static_method(bege_console_CLASS, D_METHOD("log", "args"), &bege_console::log);
    ClassDB::bind_static_method(bege_console_CLASS, D_METHOD("log_debug", "args"), &bege_console::log_debug);

    ClassDB::bind_static_method(bege_console_CLASS, D_METHOD("warning", "args"), &bege_console::warning);
    ClassDB::bind_static_method(bege_console_CLASS, D_METHOD("warning_debug", "args"), &bege_console::warning_debug);

    ClassDB::bind_static_method(bege_console_CLASS, D_METHOD("error", "args"), &bege_console::error);
    ClassDB::bind_static_method(bege_console_CLASS, D_METHOD("error_debug", "args"), &bege_console::error_debug);
}

bege_console::bege_console() {
    is_debug = OS::get_singleton()->is_debug_build();
}

bege_console::~bege_console() {
}

bool_t bege_console::is_bege_console() {
    return true;
}

void bege_console::log(const Array& args) {
    std::vector<Variant> vars;

    for (int64_t  i = 0; i < args.size(); i++)
    {
        vars.push_back(args[i]);
    }

    if (vars.size() > 0) {
        String var = String(vars[0]);
        for (size_t  i = 1; i < vars.size(); ++i)
        {
            var += " " + String(vars[i]);
        }
        bege::console::log(var);
    }
}

void bege_console::log_debug(const Array& args) {
    if (!is_debug) { return; }

    std::vector<Variant> vars;

    for (int64_t  i = 0; i < args.size(); i++)
    {
        vars.push_back(args[i]);
    }

    if (vars.size() > 0) {
        String var = String(vars[0]);
        for (size_t  i = 1; i < vars.size(); ++i)
        {
            var += " " + String(vars[i]);
        }
        bege::console::log_debug(var);
    }
}

void bege_console::warning(const Array& args) {
    std::vector<Variant> vars;

    for (int64_t  i = 0; i < args.size(); i++)
    {
        vars.push_back(args[i]);
    }

    if (vars.size() > 0) {
        String var = String(vars[0]);
        for (size_t  i = 1; i < vars.size(); ++i)
        {
            var += " " + String(vars[i]);
        }
        bege::console::warning(var);
    }
}

void bege_console::warning_debug(const Array& args) {
    if (!is_debug) { return; }

    std::vector<Variant> vars;

    for (int64_t  i = 0; i < args.size(); i++)
    {
        vars.push_back(args[i]);
    }

    if (vars.size() > 0) {
        String var = String(vars[0]);
        for (size_t  i = 1; i < vars.size(); ++i)
        {
            var += " " + String(vars[i]);
        }
        bege::console::warning_debug(var);
    }
}

void bege_console::error(const Array& args) {
    std::vector<Variant> vars;

    for (int64_t  i = 0; i < args.size(); i++)
    {
        vars.push_back(args[i]);
    }

    if (vars.size() > 0) {
        String var = String(vars[0]);
        for (size_t  i = 1; i < vars.size(); ++i)
        {
            var += " " + String(vars[i]);
        }
        bege::console::error(var);
    }
}

void bege_console::error_debug(const Array& args) {
    if (!is_debug) { return; }

    std::vector<Variant> vars;

    for (int64_t  i = 0; i < args.size(); i++)
    {
        vars.push_back(args[i]);
    }

    if (vars.size() > 0) {
        String var = String(vars[0]);
        for (size_t  i = 1; i < vars.size(); ++i)
        {
            var += " " + String(vars[i]);
        }
        bege::console::error_debug(var);
    }
}