#include "my_funcs.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <type_traits>

template <typename T>
void writeFile(const std::filesystem::path target_dir, const T content) {
    if (!std::filesystem::exists(target_dir)) {
        // Do not try to write into a directory that does not exist.
        std::cerr << "Error: The file " << target_dir << " does not exist.\n";
        return;
    }

    std::filesystem::path file_path = target_dir / "output.txt";

    if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, const char*>) {
        // Only string content can use an empty value to clear the file.
        if (content == "") {
            // Opening with trunc instantly empties the file and closes automatically on the same line
            std::ofstream(file_path, std::ios::trunc);
            log("Successfully cleared " + file_path.string(), true);
            return;
        }
    }

    // Open the file in append mode (std::ios::app) so new data doesn't wipe old data
    std::ofstream outfile(file_path, std::ios::app);

    if (outfile.is_open()) {
        // Write the generic content, then append a newline character
        outfile << content;
        outfile.close();
        log("Successfully wrote data to: " + file_path.string(), true);
    } else {
        std::cerr << "Error: Could not open file for writing.\n";
    }

    return;
}