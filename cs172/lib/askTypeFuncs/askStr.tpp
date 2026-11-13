#include <iostream>
#include <string>

namespace ask_detail {
    inline bool readString(std::string& response, size_t width) {
        if (std::getline(std::cin >> std::ws, response)) {
            // getline succeeded, so the complete response line is available.
            return true;
        }

        recoverFromInputFailure();
        log("Please input a valid string: ", false, width);
        return false;
    }
}

/**
 * @brief Prompts for a line of text.
 *
 * Leading whitespace is skipped before the line is read. Spaces inside the
 * response are kept, so an input such as @c "Ada Lovelace" is read as one string.
 *
 * @param question The message shown before input is read.
 * @param width The display width passed to the logging function.
 * @param newLine Whether to put a newline after the question.
 * @return The text entered by the user.
 *
 * @code
 * std::string name = askStr("Your name: ", 80);
 * @endcode
 **/
inline std::string askStr(
    std::string question,
    size_t width,
    bool newLine = false
) {
    auto reader = [&](std::string& response) {
        return ask_detail::readString(response, width);
    };
    return ask_detail::runAsk<std::string>(
        question,
        width,
        std::vector<std::variant<std::string>>{},
        newLine,
        reader
    );
}