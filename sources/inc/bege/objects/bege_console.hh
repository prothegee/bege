#ifndef BEGE_CONSOLE_HH
#define BEGE_CONSOLE_HH
#include <bege/bege.hh>

#include <godot_cpp/classes/object.hpp>

using namespace godot;

class bege_console final : public Object {
private:
    GDCLASS(bege_console, Object);

    INLNSTTC bool_t is_debug;

    ///////////////////////////////////////////////////////////////

    static void _bind_methods();

public:
    bege_console(/* args */);
    ~bege_console();

    ///////////////////////////////////////////////////////////////

    /**
     * @brief tell if this object is bege console
     * 
     * @return bool_t 
     */
    bool_t is_bege_console();

    ///////////////////////////////////////////////////////////////

    /**
     * @brief show log to godot console
     * 
     * @param args array of args
     */
    static void log(const Array& args);

    /**
     * @brief show log to godot console in debug
     * 
     * @param args array of args
     */
    static void log_debug(const Array& args);

    /**
     * @brief show warning log to godot console
     * 
     * @param args array of args
     */
    static void warning(const Array& args);

    /**
     * @brief show warning log to godot console in debug
     * 
     * @param args array of args
     */
    static void warning_debug(const Array& args);

    /**
     * @brief show error log to godot console
     * 
     * @param args array of args
     */
    static void error(const Array& args);

    /**
     * @brief show error log to godot console in debug
     * 
     * @param args array of args
     */
    static void error_debug(const Array& args);
}; // class bege_console

static bege_console* p_bege_console;

INLNSTTCCNST chr_t* bege_console_CLASS = "bege_console";

#endif // BEGE_CONSOLE_HH
