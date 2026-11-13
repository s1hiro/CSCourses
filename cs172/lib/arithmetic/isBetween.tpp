#include <cmath>
#include <type_traits>

/**
 * @brief Checks whether a value is between an inclusive minimum and maximum.
 *
 * This uses isLessThan and isGreaterThan. Values equal to either bound count
 * as between. If the bounds are reversed, or a floating-point value is NaN,
 * the function returns false.
 *
 * @tparam Value The type of the value being checked.
 * @tparam Min The type of the minimum.
 * @tparam Max The type of the maximum.
 * @param value The value to check.
 * @param min The inclusive lower bound.
 * @param max The inclusive upper bound.
 * @return true when min <= value <= max; otherwise false.
 **/
template <typename Value, typename Min, typename Max>
    requires (
        std::is_arithmetic_v<Value> &&
        std::is_arithmetic_v<Min> &&
        std::is_arithmetic_v<Max> &&
        !std::is_same_v<Value, bool> &&
        !std::is_same_v<Min, bool> &&
        !std::is_same_v<Max, bool>
    )
bool isBetween(Value value, Min min, Max max) {
    if constexpr (
        std::is_floating_point_v<Value> ||
        std::is_floating_point_v<Min> ||
        std::is_floating_point_v<Max>
    ) {
        if (std::isnan(static_cast<long double>(value)) ||
            std::isnan(static_cast<long double>(min)) ||
            std::isnan(static_cast<long double>(max))) {
            return false;
        }
    }

    return !isGreaterThan(min, max) &&
           !isLessThan(value, min) &&
           !isGreaterThan(value, max);
}
