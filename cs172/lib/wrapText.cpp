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
    if (text.length() <= width) {
        // The text already fits, so no wrapping is needed.
        return text;
    }

    size_t start = 0;
    while (start + width < text.length()) {
        size_t targetIndex = start + width;

        if (text[targetIndex] == ' ') {
            // Use the space at the width limit as the line break.
            text[targetIndex] = '\n';
            start = targetIndex + 1;
        }
        else {
            // Look backward for the nearest space
            size_t spaceIndex = targetIndex;
            while (spaceIndex > start && text[spaceIndex] != ' ') {
                spaceIndex--;
            }

            if (spaceIndex > start) {
                // Break at the nearest earlier space to avoid splitting a word.
                text[spaceIndex] = '\n';
                start = spaceIndex + 1;
            }
            else {
                // No space fits, so split the long word to keep making progress.
                text.insert(targetIndex, "\n");
                start = targetIndex + 1;
            }
        }
    }
    return text;
}