#include <string>

std::string repeatOneChar(std::string output, int num) {
        std::string final = "";
        for(; num > 0 ; num--) {
                final += output;
        };
        return final;
}