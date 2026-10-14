#pragma once // Prevents the header from being included multiple times
#include <string>

/*
    Note:
        For functions reasonably complex, extract logic into new file 

    Purpose:
        This is because when we do #include my_funcs.cpp, it literally copies EVERYTHING 
        in here, including this comment, into the compiled executable, so we wouldn't 
        want hundreds of lines of logic.

    Example:
        void log() defined L17, but logic stored in lib/log.cpp. 
*/

void log(std::string text, size_t width, bool newLine = false);
inline std::string repeatOneChar(std::string output, int num) {
    std::string final = "";
    for(; num > 0 ; num--) {
            final += output;
    };
    return final;
}