#include <iostream>
#include <string>

/**
 * @brief Helper function that formats a string to fit a maximum line width.
 * 
 * Inserts newlines at appropriate spaces to prevent text from overflowing the width.
 * 
 * @param text  The original unwrapped string.
 * @param width The maximum character width allowed per line.
 * @return The newly formatted word-wrapped string.
 * 
 * @note
 * - Does NOT handle width = 0 case.
 */
std::string wrapText(std::string text, size_t width) {
    // If the entire text fits on one line, return it as-is
    if (text.length() <= width) {
        return text;
    }

    size_t start = 0;
    while (start + width < text.length()) {
        size_t targetIndex = start + width;

        // If it's already a space, swap it to a newline
        if (text[targetIndex] == ' ') {
            text[targetIndex] = '\n';
            start = targetIndex + 1;
        }
        else {
            // Look backward for the nearest space
            size_t spaceIndex = targetIndex;
            while (spaceIndex > start && text[spaceIndex] != ' ') {
                spaceIndex--;
            }

            // If a space was found, break there
            if (spaceIndex > start) {
                text[spaceIndex] = '\n';
                start = spaceIndex + 1;
            }
            // If NO space was found, the word is longer than the width.
            // Force a break at the maximum width to avoid an infinite loop.
            else {
                text.insert(targetIndex, "\n");
                start = targetIndex + 1;
            }
        }
    }
    return text;
}