#include "../lib/my_funcs.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <variant>
#include <filesystem>
using namespace std;

size_t width = 80;

void intro() {
    printBorder(width, "=");
    log(centerString("Welcome to S1Sales!", width), width, true);
    printBorder(width, "=");
}

int main() {
    std::filesystem::path path = std::filesystem::current_path();
    vector<variant<string,  int>> actions = {"1", "2", "3", "Record Sales", "View sales report", "Exit"};
    string action;
    intro();

    do {
        action = ask<string>("Please type one of the following!\n(1)Record Sales\n(2)View sales report\n(3)Exit\n", width, actions);

        if(action == "1" || action == "Record sales") {
            int numOfTransactions = ask<int>("How many transactions will you be recording? ", width, false, -1);
            string content;

            log("Enter transaction amounts:", true);

            for(; numOfTransactions > 0; numOfTransactions--) {
                content += to_string(ask<int>("\n$", width));
            }

            writeFile(path, content);
        }

        if(action == "2" || action == "View sales report") {

        }

    } while ( action != "Exit" && action != "3");

    log("Thanks for using S1Sales.", width, true);
    writeFile(path, "");
    return 0;
}
