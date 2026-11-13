#include <format>
#include <iterator>
#include <string>

/**
 * @brief Joins the values in an indexable sequence into a string using a separator.
 *
 * Converts each element in the input list into text and appends it to a result string,
 * inserting the provided separator between items.
 *
 * @tparam Sequence   A sized sequence that supports indexing.
 * @param inpList     The values to join together.
 * @param separator   The string placed between each item in the final output.
 *
 * @return std::string The combined text with separators between entries.
 *
 * @note
 * - Works with C arrays and containers such as std::array and std::vector.
 * - Elements must be printable with std::format.
 * - Example: {1, 2, 3} with ", " becomes "1, 2, 3".
 **/
template <typename Sequence>
std::string separateBy(const Sequence& inpList, const std::string& separator) {
    std::string separatedText;
    const auto size = std::size(inpList);

    for (size_t i = 0; i < size; ++i) {
        separatedText += std::format("{}", inpList[i]);
        if (i + 1 < size) separatedText += separator;
    }

    return separatedText;
}