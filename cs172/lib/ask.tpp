#include <iostream>
#include <string>
#include <vector>
#include <variant>
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
template <typename T, typename... VariantTypes>
T ask(std::string question, size_t width, std::vector<std::variant<VariantTypes...>> answerList, bool newLine = false, double numMinimum = 0) { 
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

        bool foundMatch = false;
        // 5. Value validation: Use std::visit to see if 'response' matches the active variant type
        // 5.1. Loop through every variant item inside your answerList vector
        for (const auto var : answerList) {
            // 5.2. Open the variant box 'var' using std::visit
            std::visit([&](auto arg) {
               //^func to inspect variants & exec code based on it                
               //[&] scopes all used local vars to this visit's lambda fn()

                // 5.3. Extract the exact datatype name of whatever is currently inside 'arg'
                using VariantType = std::decay_t<decltype(arg)>;
                                       //^cleans type names eg; int& -> int
                                       //decltyp() = "get me this thing's type"

                // 5.4. Case A: Is the type the user entered (T) identical to the type inside the variant?
                if constexpr (std::is_same_v<T, VariantType>) {
                    // Since they are the exact same type, compare them directly!
                    if (response == arg) {
                        foundMatch = true;
                    }
                } 

                // 5.5. Case B: Did the user type a string, but the variant holds an integer?
                else if constexpr (std::is_same_v<T, std::string> && std::is_same_v<VariantType, int>) {
                    // Convert the integer 'arg' to a string so they can be safely compared!
                    if (response == std::to_string(arg)) {
                        foundMatch = true;
                    }
                }
            }, var); // End of std::visit

            // 5.6. If we found a match, stop looking and break out of the vector loop
            if (foundMatch) break;
        }

        if (foundMatch) break; // Exits the 'while(true)' loop because a valid answer was found!
        

        std::cin.ignore(10000, '\n');

        // 6. Build the error string cleanly by extracting values from variants using std::visit
        std::string errorMsg = "Please input one of these answers! ";
        for (size_t i = 0; i < answerList.size(); ++i) {
            std::visit([&errorMsg](auto&& arg) {
                using VariantType = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<VariantType, std::string>) {
                    errorMsg += arg;
                } else {
                    errorMsg += std::to_string(arg); // Convert int, double, etc. to string safely
                }
            }, answerList[i]);
            
            if (i < answerList.size() - 1) {
                errorMsg += ", ";
            }
        }
        errorMsg += ": ";

        log(errorMsg, width, false);
    }

    return response;
}
