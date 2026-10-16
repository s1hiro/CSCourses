#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <typeinfo>
#include "my_funcs.hpp"

template <typename T>
T ask(std::string question, size_t width, std::vector<T> answerList, bool newLine = false) { 
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
            
            std::string typeError = "Please input a valid " + std::string(typeid(T).name()) + ": ";
            log(typeError, width);
            continue; 
        }

        // 3. If answerList is empty, we don't need to validate specific choices
        if (answerList.empty()) {
            break; 
        }

        // 4. Value validation: Check if 'response' exists inside 'answerList'
        if (std::find(answerList.begin(), answerList.end(), response) != answerList.end()) {
            break; // Found a valid answer! Exit loop.
        }

        std::cin.ignore(10000, '\n');

        // 5. Build the error string cleanly to pass to log() safely as a unified string
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
        errorMsg += " ";

        log(errorMsg, width, false);
    }

    return response;
}