#include <iostream>
#include <string>
// defaults MUST be at the end of func declarations

/**
 * @brief Safely logs and word-wraps text to the console.
 * 
 * Replaces clunky 'std::cout' streams with a clean, automatic wrapper.
 * 
 * @param text  The string content you want to output.
 * @param width The maximum character width of the screen.
 * @param newLine Appends a trailing newline if true. [Default: false]
 * 
 * @note 
 * - WILL word-wrap text at the nearest space (not by letter).
 * @note
 * - WILL NOT accept a width of 0.
 **/
void log(std::string text, size_t width, bool newLine = false) { 

	if(width <= 0) {
		std::cout << "Please return a width greater than 0! You input: " << width << std::endl;
		return;
	}

	if (text.length() <= width) {
		std::cout << text << (newLine ? "\n" : "");
		return;
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

	std::cout << text << (newLine ? "\n" : "");
	return;
}
