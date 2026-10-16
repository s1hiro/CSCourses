#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <typeinfo>
#include "my_funcs.hpp"

/**
 * @brief Safely prompts the user for input and handles strict type validation.
 * 
 * Replaces complex 'std::cin' boilerplate with an automatic, typesafe loop.
 * 
 * @tparam T          The expected data type of the user's response.
 * @param question    The prompt message displayed to the user.
 * @param width       The maximum character width of the screen.
 * @param answerList  An optional list of allowed choices to restrict input validation. [Default: {}]
 * @param newLine     Appends a trailing newline to the initial prompt if true. [Default: {}]
 * @param numMinimum  The lowest a number answer can be. [Default: 0]
 * 
 * @return T          The validated, type-matching user input.
 * 
 * @note 
 * - WILL automatically catch, clear, and loop past invalid type entries (e.g., text for an int).
 * @note
 * - WILL reject inputs that are not explicitly present in 'answerList' if a list is provided.
 * @note
 * - WILL NOT accept a screen width of 0 or lower.
 **/
template <typename T>
T ask(std::string question, size_t width, double numMinimum, std::vector<T> answerList, bool newLine) { 
    if (width <= 0) {
        std::cerr << "Please return a width greater than 0! You input: " << width << std::endl;
        return T();
    }

    // Print the question
    log(question, width, newLine);

    T response;
    while (true) {
        // 1. Try to read the user input into type T
        std::cin >> response;

        // 2. Check if the type reading failed (e.g., text entered for an int)
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(10000, '\n'); // Dump what's left in stream
            
            std::string typeError = "Please input a valid " + getCleanTypeName(std::string(typeid(T).name())) + ": ";
            log(typeError, width);
            continue; 
        }

        // 3. If it's a number ...
        if constexpr (std::is_arithmetic_v<T>) {
            // If it's less than the required min ...
            if (response < numMinimum) {
                std::cin.ignore(10000, '\n');
                std::string rangeError = "Value cannot be negative! Please enter a number >= 0: ";
                log(rangeError, width);
                continue; // Restart loop to prompt again
            }
        }

        // 4. If answerList is empty, we don't need to validate specific choices
        if (answerList.empty()) {
            break; 
        }

        // 5. Value validation: Check if 'response' exists inside 'answerList'
        if (std::find(answerList.begin(), answerList.end(), response) != answerList.end()) {
            break; // Found a valid answer! Exit loop.
        }

        std::cin.ignore(10000, '\n');

        // 6. Build the error string cleanly to pass to log() safely as a unified string
        std::string errorMsg = "Please input one of these answers! ";
        for (size_t i = 0; i < answerList.size(); ++i) {
            if constexpr (std::is_same_v<T, std::string>) {
                errorMsg += answerList[i];
            } else {
                errorMsg += std::to_string(answerList[i]); // Safeguard against non-string types
            }
            
            if (i < answerList.size() - 1) {
                errorMsg += ", ";
            }
        }
        errorMsg += ": ";

        log(errorMsg, width, false);
    }

    return response;
}