#ifndef BEGE_BEGE_HH
#define BEGE_BEGE_HH
#include "base.hh"
#include "godot.hh"
#include "export.hh"
#ifdef bege_shared_EXPORTS
#include "export_shared.hh"
#else
#include "export_static.hh"
#endif

#include <bege/functions/date_and_time.hh>

#include <godot_cpp/variant/utility_functions.hpp>

namespace bege {
namespace console {
template<typename... Args>
static void log(const Args& ...args) {
    int32_t timezone = date_and_time_functions::local_timezone();
    std::string current_time = date_and_time_functions::utc::time_zone::to_string(timezone);

    godot::UtilityFunctions
    ::print("[bege - ", current_time.c_str(), "]: ", args...);
}
} // namespace console
} // namespace bege
#endif // BEGE_BEGE_HH
