#pragma once // Prevents the header from being included multiple times
#include <string>
#include <vector>
#include <cxxabi.h>
#include <cstdlib>
#include <filesystem>
#include <variant>

/*
    Note:
        For functions reasonably complex, extract logic into new file 

    Purpose:
        This is because when we do #include my_funcs.hpp, it literally copies EVERYTHING 
        in here, including this comment, into the compiled executable, so we wouldn't 
        want hundreds of lines of logic.

    Example:
        void log() defined L17, but logic stored in lib/log.cpp. 
*/

template <typename T>
void writeFile(const std::filesystem::path target_dir, const T content);

int log(std::string text, bool newLine = false, size_t width = 80);

template <typename T>
T ask(std::string question, size_t width, bool newLine = false, double numMinimum = 0) {
    return ask<T, std::string>(question, width, std::vector<std::variant<std::string>>{}, newLine, numMinimum);
} 
// this is for when you do not pass in a answerList - the reason is because you cannot set defaults in param 
// templates, so we have to enforce it here. when you do pass in an answer list, it only matches the fn() 
// signature of the one below, so it bypasses the one above.

template <typename T, typename... VariantTypes>
T ask(std::string question, size_t width, std::vector<std::variant<VariantTypes...>> answerList, bool newLine = false, double numMinimum = 0);

std::string wrapText(std::string text, size_t width);

inline std::string repeatOneChar(std::string output, size_t num) {
    std::string final = "";
    for(; num > 0 ; num--) {
            final += output;
    };
    return final;
}

inline std::string getCleanTypeName(const std::string& mangledName) {
    int status = 0;
    // __cxa_demangle returns a raw C-string allocated with malloc
    char* demangled = abi::__cxa_demangle(mangledName.c_str(), nullptr, nullptr, &status);
    
    // If status is 0, the translation succeeded
    if (status == 0 && demangled != nullptr) {
        std::string result(demangled);
        std::free(demangled); // Clean up the memory allocated by the system
        return result;
    }
    
    // If it failed or couldn't decode, fall back to the original string
    return mangledName; 
}

inline void printBorder(size_t width, std::string borderChar) {
    log(repeatOneChar(borderChar, width), width, true);
};

inline std::string centerString(std::string text, int width, std::string emptySpaceChar = " ") {
	std::string spacing = repeatOneChar(emptySpaceChar, (width - text.length()) / 2);
	return spacing + text + spacing;
}

#include "./ask.tpp"
#include "./writeFile.tpp"