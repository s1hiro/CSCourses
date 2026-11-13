#include <type_traits>
#include <variant>

namespace type_checker_detail {
template <typename T>
inline constexpr bool isCharacterType =
    std::is_same_v<T, char> ||
    std::is_same_v<T, signed char> ||
    std::is_same_v<T, unsigned char> ||
    std::is_same_v<T, wchar_t> ||
    std::is_same_v<T, char8_t> ||
    std::is_same_v<T, char16_t> ||
    std::is_same_v<T, char32_t>;
}

/**
 * @brief Checks whether a variant currently holds a character type.
 *
 * This includes char and the wide-character types. A character is distinct
 * from a std::string, which can hold multiple characters.
 *
 * @param value The variant whose active value should be checked.
 * @return true if the active value is a character type; otherwise false.
 **/
template <typename... Types>
bool isCharacter(const std::variant<Types...>& value) {
    return std::visit([](const auto& activeValue) {
        using ActiveType = std::decay_t<decltype(activeValue)>;
        return type_checker_detail::isCharacterType<ActiveType>;
    }, value);
}
