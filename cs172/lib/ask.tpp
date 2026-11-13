#include <format>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

namespace ask_detail {
    inline void discardRemainingInput() {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    inline void recoverFromInputFailure() {
        if (std::cin.bad()) {
            throw std::runtime_error("Input stream failed.");
        }
        if (std::cin.eof()) {
            throw std::runtime_error("Input ended before a valid response was entered.");
        }
        std::cin.clear();
        discardRemainingInput();
    }

    template <typename>
    inline constexpr bool unsupportedAskType = false;

    /**
     * @brief Runs the shared prompt and validation steps for an ask function.
     *
     * The type-specific reader handles how one value is read. This function
     * handles the parts shared by all types: showing the question, retrying after
     * invalid input, and checking an optional list of allowed answers.
     *
     * @tparam T The type of value returned to the caller.
     * @tparam Reader A function that reads one value and reports success or failure.
     * @tparam VariantTypes The types that may appear in the allowed-answer list.
     * @param question The message shown before input is read.
     * @param width The display width passed to the logging function.
     * @param answerList Optional answers the user is allowed to enter.
     * @param newLine Whether to put a newline after the question.
     * @param reader The type-specific function used to read the response.
     * @return The response after it has been read and validated.
     *
     * @note A width of 0 is rejected and returns a default-initialized value.
     *       If the input stream ends or fails, a std::runtime_error is thrown.
     **/
    template <typename T, typename Reader, typename... VariantTypes>
    T runAsk(
        std::string question,
        size_t width,
        std::vector<std::variant<VariantTypes...>> answerList,
        bool newLine,
        Reader reader
    ) {
        if (width == 0) {
            std::cerr << "Please return a width greater than 0!" << std::endl;
            return T{};
        }

        log(question, newLine, width);

        T response{};
        while (true) {
            //this loop is for answerlist checking

            if (!reader(response)) continue;

            if (answerList.empty()) break;

            bool foundMatch = false;
            for (const auto& answer : answerList) {
                std::visit([&](const auto& value) {
                   //^ runs lambda on curr val stored in a variant (answer from answerList)

                    using VariantType = std::decay_t<decltype(value)>;
                    //^ alias for "answer"'s type

                    if constexpr (std::is_same_v<T, VariantType>) {
                        foundMatch = response == value;
                    } else if constexpr (
                        std::is_same_v<T, std::string> &&
                        std::is_same_v<VariantType, int>
                    ) {
                        foundMatch = response == std::to_string(value);
                    }
                }, answer);
                 //^ ANSWER PASSED HERE FROM LINE L74

                if (foundMatch) break;
            }

            if (foundMatch) break;
            
            //at this point, no match has been found through common
            //translation of str to int, so we 

            if constexpr (!std::is_same_v<T, std::string>) {
                discardRemainingInput();
            }

            std::vector<std::string> formattedAnswers;
            for (const auto& answer : answerList) {
                formattedAnswers.push_back(std::visit([](const auto& value) {
                    return std::format("{}", value);
                    //format used to account for non-number answers
                    //eg; to_string(string ...) won't compile but,
                    //format will
                }, answer));
            }
            log(
                "Please input one of these answers! " +
                    separateBy(formattedAnswers, ", ") + ": ",
                false,
                width
            );
        }

        return response;
    }
}

#include "askTypeFuncs/askStr.tpp"
#include "askTypeFuncs/askNum.tpp"
#include "askTypeFuncs/askBool.tpp"

/**
 * @brief Reads a typed response using the shared ask flow.
 *
 * This is the general interface used by existing calls such as
 * @c ask<int>(...). It chooses the string, boolean, or arithmetic reader
 * based on @c T. An optional answer list can restrict which values are accepted.
 *
 * @tparam T The type to read, such as int, double, bool, or std::string.
 * @tparam VariantTypes The types stored in the optional answer list.
 * @param question The message shown before input is read.
 * @param width The display width passed to the logging function.
 * @param answerList Optional allowed answers.
 * @param newLine Whether to put a newline after the question.
 * @param numMinimum The lowest accepted value for arithmetic types.
 * @return The response after it has been read and validated.
 **/
template <typename T, typename... VariantTypes>
T ask(
    std::string question,
    size_t width,
    std::vector<std::variant<VariantTypes...>> answerList,
    bool newLine,
    T numMinimum
) {
    auto reader = [&](T& response) {
        if constexpr (std::is_same_v<T, std::string>) {
            return ask_detail::readString(response, width);
        } else if constexpr (std::is_same_v<T, bool>) {
            return ask_detail::readBool(response, width);
        } else if constexpr (std::is_arithmetic_v<T>) {
            return ask_detail::readNumber(response, width, numMinimum, false);
        } else {
            static_assert(
                ask_detail::unsupportedAskType<T>,
                "ask<T> supports strings, booleans, and arithmetic types."
            );
        }
    };

    return ask_detail::runAsk<T>(
        question,
        width,
        answerList,
        newLine,
        reader
    );
}
