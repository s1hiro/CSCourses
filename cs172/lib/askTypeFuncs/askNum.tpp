#include <format>
#include <iostream>
#include <string>
#include <type_traits>
#include <typeinfo>

namespace ask_detail {
    /**
     * @brief Reports whether a numeric limit was given as the false sentinel.
     *
     * A false boolean means that the limit is not set. A true boolean is not a
     * numeric limit and is rejected.
     **/
    template <typename Bound>
    bool isUnlimited(Bound bound) {
        if constexpr (std::is_same_v<std::decay_t<Bound>, bool>) {
            if (bound) {
                throw std::invalid_argument("Boolean numeric bounds must be false.");
            }
            return true;
        }
        return false;
    }

    /**
     * @brief Reads one number and checks its optional minimum and maximum.
     *
     * A false boolean skips that limit. Numeric limits are inclusive, so a
     * value equal to the minimum or maximum is accepted.
     **/
    template <typename T, typename Min, typename Max>
        requires (
            std::is_arithmetic_v<T> &&
            !std::is_same_v<T, bool> &&
            std::is_arithmetic_v<Min> &&
            std::is_arithmetic_v<Max>
        )
    bool readNumber(T& response, size_t width, Min numMin, Max numMax) {
        const bool minUnlimited = isUnlimited(numMin);
        const bool maxUnlimited = isUnlimited(numMax);

        if (!(std::cin >> response)) {
            recoverFromInputFailure();
            const auto typeName = getCleanTypeName(typeid(T).name());
            log("Please input a valid " + typeName + ": ", false, width);
            return false;
        }

        const bool outsideBounds = !minUnlimited && !maxUnlimited
            ? !isBetween(response, numMin, numMax)
            : (!minUnlimited && isLessThan(response, numMin)) ||
              (!maxUnlimited && isGreaterThan(response, numMax));
        if (outsideBounds) {
            discardRemainingInput();
            std::string rangeError = "Value must be";
            if (!minUnlimited) {
                rangeError += std::format(" >= {}", numMin);
            }
            if (!maxUnlimited) {
                rangeError += std::format(" and <= {}", numMax);
            }
            rangeError += ": ";
            log(rangeError, false, width);
            return false;
        }

        return true;
    }
}

/**
 * @brief Prompts for a number and optionally checks its minimum and maximum.
 *
 * The limit types can be numeric types or bool. Pass false for either limit to
 * leave it unlimited. Bounds are inclusive, so values equal to a bound pass.
 *
 * @tparam T The arithmetic type to read, such as int, float, or double.
 * @tparam Min The type of the minimum, or bool when the minimum is unlimited.
 * @tparam Max The type of the maximum, or bool when the maximum is unlimited.
 * @param question The message shown before input is read.
 * @param width The display width passed to the logging function.
 * @param numMin The lowest accepted value, or false for no minimum.
 * @param numMax The highest accepted value, or false for no maximum.
 * @param newLine Whether to put a newline after the question.
 * @return The number after it has been read and checked.
 *
 * @throws std::invalid_argument If a boolean limit is true, or the minimum is
 *         greater than the maximum.
 *
 * @code
 * int score = askNum<int>("Score: ", 80, 0, 100);
 * double temperature = askNum<double>("Temperature: ", 80, false, 50.0);
 * @endcode
 **/
template <typename T, typename Min = bool, typename Max = bool>
    requires (
        std::is_arithmetic_v<T> &&
        !std::is_same_v<T, bool> &&
        std::is_arithmetic_v<Min> &&
        std::is_arithmetic_v<Max>
    )
T askNum(
    std::string question,
    size_t width,
    Min numMin = false,
    Max numMax = false,
    bool newLine = false
) {
    const bool minUnlimited = ask_detail::isUnlimited(numMin);
    const bool maxUnlimited = ask_detail::isUnlimited(numMax);
    if (!minUnlimited && !maxUnlimited &&
        isGreaterThan(numMin, numMax)) {
        throw std::invalid_argument(
            std::format(
                "Numeric minimum cannot exceed maximum. Question: {}. Min: {}, Max: {}",
                question,
                numMin,
                numMax
            )
        );
    }

    auto reader = [&](T& response) {
        return ask_detail::readNumber(response, width, numMin, numMax);
    };
    return ask_detail::runAsk<T>(
        question,
        width,
        std::vector<std::variant<T>>{},
        newLine,
        reader
    );
}