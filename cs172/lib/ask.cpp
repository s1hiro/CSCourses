#include <iostream>
#include <string>

/**
 * @brief Prompts the user with a question and safely reads their input into the requested type.
 * 
 * @tparam T    The expected data type to return (e.g., int, double, std::string).
 * @param text  The question text you want to output.
 * @param width The maximum character width of the screen.
 * @param newLine Appends a trailing newline after the question text, if true. [Default: false]
 * 
 * @note 
 * - **WILL** word-wrap text at the nearest space (not by letter).
 * - **WILL NOT** accept a width of 0.
 **/
template <typename T>
T ask(std::string text, size_t width, bool newLine = false) { 
    // TODO: Add Answer checking compatibility. <- take in list of answers, and do ansList.includes(cinResp)
    if (width <= 0) {
        std::cerr << "Please return a width greater than 0! You input: " << width << std::endl;
        return T(); // Returns a default value for safety (e.g., 0, 0.0, or "")
    }

    // Print the wrapped question
    std::string formattedText = wrapText(text, width);
    std::cout << formattedText << (newLine ? "\n" : "");

    // Read the user input dynamically based on the requested type T
    T response;
    std::cin >> response;
    
    return response;
}