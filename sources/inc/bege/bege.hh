#ifndef BEGE_BEGE_HH
#define BEGE_BEGE_HH
#include "base.hh"
#include "export.hh"
#include "godot.hh"

#ifdef bege_shared_EXPORTS
#include "export_shared.hh"
#else
#include "export_static.hh"
#endif

#include <bege/functions/date_and_time.hh>

namespace bege {
namespace console {
/**
 * @brief show log to godot console
 * 
 * @tparam Args 
 * @param args 
 */
template <typename... Args>
static void log(const Args&... args) {
    int32_t timezone = date_and_time_functions::local_timezone();
    std::string current_time = date_and_time_functions::utc::time_zone::to_string(timezone);

    godot::UtilityFunctions::print("[", current_time.c_str(), "] bege: ", args...);
}

/**
 * @brief show log to godot console in debug
 * 
 * @tparam Args 
 * @param args 
 */
template <typename... Args>
static void log_debug(const Args&... args) {
    if (!godot::OS::get_singleton()->is_debug_build()) { return; }

    int32_t timezone = date_and_time_functions::local_timezone();
    std::string current_time = date_and_time_functions::utc::time_zone::to_string(timezone);

    godot::UtilityFunctions::print("[", current_time.c_str(), "] bege - debug: ", args...);
}

/**
 * @brief show warning log to godot console
 * 
 * @tparam Args 
 * @param args 
 */
template <typename... Args>
static void warning(const Args&... args) {
    int32_t timezone = date_and_time_functions::local_timezone();
    std::string current_time = date_and_time_functions::utc::time_zone::to_string(timezone);

    godot::UtilityFunctions::push_warning("[", current_time.c_str(), "] bege: ", args...);
}

/**
 * @brief show warning log to godot console in debug
 * 
 * @tparam Args 
 * @param args 
 */
template <typename... Args>
static void warning_debug(const Args&... args) {
    if (!godot::OS::get_singleton()->is_debug_build()) { return; }

    int32_t timezone = date_and_time_functions::local_timezone();
    std::string current_time = date_and_time_functions::utc::time_zone::to_string(timezone);

    godot::UtilityFunctions::push_warning("[", current_time.c_str(), "] bege - debug: ", args...);
}

/**
 * @brief show error log to godot console
 * 
 * @tparam Args 
 * @param args 
 */
template <typename... Args>
static void error(const Args&... args) {
    int32_t timezone = date_and_time_functions::local_timezone();
    std::string current_time = date_and_time_functions::utc::time_zone::to_string(timezone);

    godot::UtilityFunctions::push_error("[", current_time.c_str(), "] bege: ", args...);
}

/**
 * @brief show error log to godot console in debug
 * 
 * @tparam Args 
 * @param args 
 */
template <typename... Args>
static void error_debug(const Args&... args) {
    if (!godot::OS::get_singleton()->is_debug_build()) { return; }

    int32_t timezone = date_and_time_functions::local_timezone();
    std::string current_time = date_and_time_functions::utc::time_zone::to_string(timezone);

    godot::UtilityFunctions::push_error("[", current_time.c_str(), "] bege - debug: ", args...);
}
} // namespace console
} // namespace bege
#endif // BEGE_BEGE_HH
