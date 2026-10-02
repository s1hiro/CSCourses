#include <iostream>
#include <iomanip>
#include <unordered_map>
using namespace std;

void log(string output, bool nl = false) {
        cout << output << (nl ? "\n" : "");
}

unordered_map<string, double> products = {
        {"Burger", 8.50},
        {"Pasta", 10},
        {"Salad", 6.25},
        {"Lemonade", 2.50},
        {"Water", 1}
};

unordered_map<string, int> order;

string repeatOneChar(string output, int num) {
        string final = "";
        for(; num > 0 ; num--) {
                final += output;
        };
        return final;
};

void printBigBorder() {
        log(repeatOneChar("=", 70), true);
};

int main() {
        for(auto& product : products) {
                string name = product.first;
                order.insert({name, 0});
        };
        printBigBorder();
        log(repeatOneChar(" ", 24) + "Welcome to S1Delights!", true);
        printBigBorder();

        cout << endl;
};