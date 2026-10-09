#pragma once // Prevents the header from being included multiple times
#include <string>

void log(bool newLine = false, std::string text, size_t width);
std::string repeatOneChar(std::string output, int num);