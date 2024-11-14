#ifndef DEBUG_INFO_H
#define DEBUG_INFO_H

#include <iostream>
#include <fstream>
#include <cstdarg>

namespace genesis_log {

enum class OutputType {
    Console,
    File
};

#define DEBUG_TYPE 1
#define RELEASE_TYPE 2

// extern OutputType debug_output_type;

static inline void debug(const char* format, ...) {
#ifdef CMAKE_BUILD_TYPE
#if CMAKE_BUILD_TYPE == DEBUG_TYPE
    va_list args;
    va_start(args, format);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);

    // if (debug_output_type == OutputType::Console) {
    std::cout << buffer << std::endl;
    // } else {
    // std::ofstream outfile("/tmp/genesis_debug_info.log", std::ios_base::app);
    // if (outfile.is_open()) {
    //     outfile << buffer << std::endl;
    //     outfile.close();
    // }
    // }
#elif CMAKE_BUILD_TYPE == RELEASE_TYPE
    return;
#endif
#endif
}

} // namespace genesis_log

#endif // DEBUG_INFO_H