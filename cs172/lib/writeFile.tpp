#include "my_funcs.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

template <typename T>
void writeFile(const std::filesystem::path target_dir, const T content) {
    if (!std::filesystem::exists(target_dir)) {
        std::cerr << "Error: The folder " << target_dir << " does not exist.\n";
        return;
    }

    std::filesystem::path file_path = target_dir / "output.txt";

    // Open the file in append mode (std::ios::app) so new data doesn't wipe old data
    std::ofstream outfile(file_path, std::ios::app); 
    
    if (outfile.is_open()) {
        // Write the generic content, then append a newline character
        outfile << content << "\n"; 
        outfile.close();
        log("Successfully wrote data to: " + file_path.string(), true);
    } else {
        std::cerr << "Error: Could not open file for writing.\n";
    }

    return;
}