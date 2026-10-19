#include "../lib/my_funcs.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <variant>
using namespace std;

size_t width = 80;

void intro() {
    printBorder(width, "=");
    log(centerString("Welcome to S1Sales!", width), width, true);
    printBorder(width, "=");
}

int main() {
    vector<variant<string,  int>> actions = {"1", "2", "3", "Record Sales", "View sales report", "Exit"};
    string action;
    intro();

    do {
        action = ask<string>("Please type one of the following!\n(1)Record Sales\n(2)View sales report\n(3)Exit\n", width, actions);
    } while ( action != "Exit" && action != "3");

    log("Thanks for using S1Sales.", width, true);
    return 0;
}
