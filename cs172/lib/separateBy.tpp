#include <format>
#include <string>
#include <vector>

/**
 * @brief Joins the values in a vector into a single string using a separator.
 *
 * Converts each element in the input list into text and appends it to a result string,
 * inserting the provided separator between items.
 *
 * @tparam T          The data type stored inside the input vector.
 * @param inpList     The values to join together.
 * @param separator   The string placed between each item in the final output.
 *
 * @return std::string The combined text with separators between entries.
 *
 * @note
 * - Works with numbers, strings, and other types that std::format can print.
 * - Example: {1, 2, 3} with ", " becomes "1, 2, 3".
 **/
template <typename T>
std::string separateBy(const std::vector<T>& inpList, const std::string& separator) {
    std::string separatedText;

    for (size_t i = 0; i < inpList.size(); ++i) {
        separatedText += std::format("{}", inpList[i]);
        if (i + 1 < inpList.size()) separatedText += separator;
    }

    return separatedText;
}