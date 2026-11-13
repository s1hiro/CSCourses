#include <string>
#include <type_traits>
#include <variant>

/**
 * @brief Checks whether a variant currently holds a std::string.
 *
 * @param value The variant whose active value should be checked.
 * @return true if the active value is a string; otherwise false.
 **/
template <typename... Types>
bool isString(const std::variant<Types...>& value) {
    return std::visit([](const auto& activeValue) {
        using ActiveType = std::decay_t<decltype(activeValue)>;
        return std::is_same_v<ActiveType, std::string>;
    }, value);
}
