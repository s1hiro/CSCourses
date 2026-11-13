#include <type_traits>
#include <utility>

/**
 * @brief Checks whether one arithmetic value is less than another.
 *
 * Integral values are compared safely even when their signedness differs.
 * If either value is floating point, both values are compared as long double.
 *
 * @tparam Left The type of the first number.
 * @tparam Right The type of the second number.
 * @param left The value to compare.
 * @param right The value to compare against.
 * @return true when left is less than right; otherwise false.
 **/
template <typename Left, typename Right>
    requires (
        std::is_arithmetic_v<Left> &&
        std::is_arithmetic_v<Right> &&
        !std::is_same_v<Left, bool> &&
        !std::is_same_v<Right, bool>
    )
bool isLessThan(Left left, Right right) {
    if constexpr (
        std::is_integral_v<Left> &&
        std::is_integral_v<Right> &&
        !type_checker_detail::isCharacterType<Left> &&
        !type_checker_detail::isCharacterType<Right>
    ) {
        // cmp_less safely compares signed and unsigned integers.
        return std::cmp_less(left, right);
    } else {
        // Character and floating-point values use a common numeric type instead.
        return static_cast<long double>(left) <
               static_cast<long double>(right);
    }
}
