#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "../lib/my_funcs.hpp"
using namespace std;

int main() {
    int width = 80;
    string name = ask<string>("What is your name? ", width);
    double income = ask<double>("What is your income? $", width);
    double expenses = ask<double>("What is your monthly expense? $", width);
    double savings = ask<double>("What is your current savings balance? $", width);
    int creditScore = ask<int>("What is your credit score? $", width);
    double carPrice = ask<double>("What is your prospective car price? $", width, 1);
    double remainingMoney = income - expenses;
    double downPayment = carPrice * 0.20;


    return 0;
}