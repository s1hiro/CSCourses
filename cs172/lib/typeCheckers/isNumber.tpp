#include <type_traits>
#include <variant>

/**
 * @brief Checks whether a variant currently holds an arithmetic value.
 *
 * Boolean and character values are not counted as numbers because they have
 * their own checkers.
 *
 * @param value The variant whose active value should be checked.
 * @return true if the active value is arithmetic and is not bool; otherwise false.
 **/
template <typename... Types>
bool isNumber(const std::variant<Types...>& value) {
    return std::visit([](const auto& activeValue) {
        using ActiveType = std::decay_t<decltype(activeValue)>;
        return std::is_arithmetic_v<ActiveType> &&
               !std::is_same_v<ActiveType, bool> &&
               !type_checker_detail::isCharacterType<ActiveType>;
    }, value);
}
