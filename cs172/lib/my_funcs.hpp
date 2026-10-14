#pragma once // Prevents the header from being included multiple times
#include <string>

void log(std::string text, size_t width, bool newLine = false); // defaults MUST be at the end
inline std::string repeatOneChar(std::string output, int num) {
    std::string final = "";
    for(; num > 0 ; num--) {
            final += output;
    };
    return final;
}