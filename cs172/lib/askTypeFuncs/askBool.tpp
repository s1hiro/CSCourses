#include <iostream>
#include <string>

namespace ask_detail {
    inline bool readBool(bool& response, size_t width) {
        std::string input;
        if (!(std::cin >> input)) {
            recoverFromInputFailure();
            log("Please input true, false, 1, or 0: ", false, width);
            return false;
        }

        if (input == "true" || input == "1") {
            response = true;
            return true;
        }
        if (input == "false" || input == "0") {
            response = false;
            return true;
        }

        discardRemainingInput();
        log("Please input true, false, 1, or 0: ", false, width);
        return false;
    }
}

/**
 * @brief Prompts for a true-or-false answer.
 *
 * Accepted inputs are the lowercase words @c true and @c false, or the digits
 * @c 1 and @c 0. Other input is rejected and the user is prompted again.
 *
 * @param question The message shown before input is read.
 * @param width The display width passed to the logging function.
 * @param newLine Whether to put a newline after the question.
 * @return true or false, based on the user's response.
 *
 * @code
 * bool keepGoing = askBool("Continue? ", 80);
 * @endcode
 **/
inline bool askBool(std::string question, size_t width, bool newLine = false) {
    auto reader = [&](bool& response) {
        return ask_detail::readBool(response, width);
    };
    return ask_detail::runAsk<bool>(
        question,
        width,
        std::vector<std::variant<bool>>{},
        newLine,
        reader
    );
}