#include <iostream>
#include <string>
#include "my_funcs.hpp"

/**
 * @brief Safely logs and word-wraps text to the console.
 * 
 * Replaces clunky 'std::cout' streams with a clean, automatic wrapper.
 * 
 * @param text  The string content you want to output.
 * @param width The maximum character width of the screen.
 * @param newLine Appends a trailing newline if true. [Default: false]
 * 
 * @note 
 * - WILL word-wrap text at the nearest space (not by letter).
 * @note
 * - WILL NOT accept a width of 0.
 **/
void log(std::string text, size_t width, bool newLine = false) { 
    if (width <= 0) {
        std::cout << "Please return a width greater than 0! You input: " << width << std::endl;
        return;
    }

    // Call our extracted helper function to format the string
    std::string formattedText = wrapText(text, width);

    std::cout << formattedText << (newLine ? "\n" : "");
}