#include <type_traits>

/**
 * @brief Checks whether one arithmetic value is greater than another.
 *
 * It reverses the arguments and uses isLessThan, so both functions follow the
 * same comparison rules.
 *
 * @tparam Left The type of the first number.
 * @tparam Right The type of the second number.
 * @param left The value to compare.
 * @param right The value to compare against.
 * @return true when left is greater than right; otherwise false.
 **/
template <typename Left, typename Right>
    requires (
        std::is_arithmetic_v<Left> &&
        std::is_arithmetic_v<Right> &&
        !std::is_same_v<Left, bool> &&
        !std::is_same_v<Right, bool>
    )
bool isGreaterThan(Left left, Right right) {
    return isLessThan(right, left);
}
