#include "../lib/my_funcs.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <variant>
#include <filesystem>
#include <format>
using namespace std;

size_t width = 80;

void intro() {
    printBorder(width, "=");
    log(centerString("Welcome to S1Sales!", width), true, width);
    printBorder(width, "=");
}

int main() {
    std::filesystem::path path = std::filesystem::current_path();
    vector<variant<string, int>> actions = {"1", "2", "3", "Record Sales", "View sales report", "Exit"};
    string action;
    intro();

    do {
        action = ask<string>("Please type one of the following!\n(1)Record Sales\n(2)View sales report\n(3)Exit\n", width, actions);

        if(action == "1" || action == "Record Sales") {
            int numOfTransactions = ask<int>("How many transactions will you be recording? ", width, false, -1);
            string content;

            log("Enter transaction amounts:", true);

            for(; numOfTransactions > 0; numOfTransactions--) {
                content += to_string(ask<double>("$", width)) + "\n";
            }

            writeFile(path, content);
            log("Sales successfully recorded!", true);
            continue;
        }

        if(action == "2" || action == "View sales report") {
            vector<double> sales = {};
            ifstream salesFile(path / "output.txt");
            string line;
            size_t count = 0;

            while(getline(salesFile, line)) {
                count++;
                sales.push_back(stod(line));
            }

            double total = 0;

            for(size_t i = 0; i < count; i++) {
                total += sales[i];
            }

            string totalStr = format("{:.2f}", total);
            string averageStr = format("{:.2f}", total / count);

            log("Total Sales: $" + totalStr, true);
            log("Average Sale: $" + averageStr, true);
        }

    } while ( action != "Exit" && action != "3");

    log("Thanks for using S1Sales.", true, width);
    writeFile(path, "");
    return 0;
}
