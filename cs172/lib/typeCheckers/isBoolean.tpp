#include <type_traits>
#include <variant>

/**
 * @brief Checks whether a variant currently holds a bool.
 *
 * @param value The variant whose active value should be checked.
 * @return true if the active value is bool; otherwise false.
 **/
template <typename... Types>
bool isBoolean(const std::variant<Types...>& value) {
    return std::visit([](const auto& activeValue) {
        using ActiveType = std::decay_t<decltype(activeValue)>;
        return std::is_same_v<ActiveType, bool>;
    }, value);
}
