#include <iostream>
#include <string>
#include "my_funcs.hpp"

/**
 * @brief Safely logs and word-wraps text to the console.
 * 
 * Replaces clunky 'std::cout' streams with a clean, automatic wrapper.
 * 
 * @param text  The string content you want to output.
 * @param width The maximum character width of the screen. [Default: 80]
 * @param newLine Appends a trailing newline if true. [Default: false]
 * 
 * @note 
 * - WILL word-wrap text at the nearest space (not by letter).
 * @note
 * - WILL NOT accept a width of 0.
 **/
int log(std::string text, bool newLine, size_t width = 80) { 
    if (width <= 0) {
        std::cout << "Please return a width greater than 0! You input: " << width << std::endl;
        return 0;
    }

    // Call our extracted helper function to format the string
    std::string formattedText = wrapText(text, width);

    std::cout << formattedText << (newLine ? "\n" : "");

    return 0;
}