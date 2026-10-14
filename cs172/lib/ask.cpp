#include <iostream>
#include <string>
#include <vector>
#include "my_funcs.hpp"

/**
 * @brief Prompts the user with a question and safely reads their input into the requested type.
 * 
 * @tparam T    The expected data type to return (e.g., int, double, std::string).
 * @param text  The question text you want to output.
 * @param width The maximum character width of the screen.
 * @param newLine Appends a trailing newline after the question text, if true. [Default: false]
 * @param answerList The list of answers you'd like for it to validate against, enforced in the T param.
 * 
 * @note 
 * - **WILL** word-wrap text at the nearest space (not by letter).
 * - **WILL NOT** accept a width of 0.
 **/
template <typename T>
T ask(std::string question, size_t width, std::vector<T> answerList, bool newLine = false) { 
    // TODO: Add Answer checking compatibility. <- take in list of answers, and do ansList.includes(cinResp)
    if (width <= 0) {
        std::cerr << "Please return a width greater than 0! You input: " << width << std::endl;
        return T(); // Returns a default value for safety (e.g., 0, 0.0, or "")
    }

    // Print the wrapped question
    log(question, width, newLine);

    // Read the user input dynamically based on the requested type T
    T response;
    while (true) {
        // 1. Try to read the user input into type T
        std::cin >> response;

        // 2. Check if the type reading failed (e.g., text entered for an int)
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(10000, '\n'); // Discard the bad input stream up to newline
            
            std::cout << "Please input a T again: "; //TODO2 figure out how to print T
            continue; // Jump back to the start of the while loop to try again
        }

        // 3. If answerList is empty, we don't need to validate specific choices
        if (answerList.empty()) {
            break; 
        }

        // 4. Value validation: Check if 'response' exists inside 'answerList'
        // std::find returns an iterator. If it equals answerList.end(), it wasn't found.
        if (std::find(answerList.begin(), answerList.end(), response) != answerList.end()) {
            break; // Found it! Break out of the loop and return
        }

        // 5. If it wasn't found, print the allowed elements separated by a comma
        std::cout << "Please input one of these answers! [";
        for (size_t i = 0; i < answerList.size(); ++i) {
            std::cout << answerList[i];
            if (i < answerList.size() - 1) {
                std::cout << ", "; // Only add a comma if it's not the last element
            }
        }
        std::cout << "]: ";
    }

    return response;
}