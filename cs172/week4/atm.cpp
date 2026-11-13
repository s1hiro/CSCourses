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
    bool hasEmergencyFund = savings == 3 * expenses;
    bool highDebtRisk = expenses > .8 * income;

    string financialStatus;
    if (remainingMoney >= 2000.0) {
        // Choose the highest cash-flow tier first.
        financialStatus = "Excellent cash flow";
    } 
    else if (remainingMoney >= 1000.0) { // Implies < 2000
        // This tier applies after the higher cash-flow check failed.
        financialStatus = "Good cash flow";
    } 
    else if (remainingMoney >= 500.0) {  // Implies < 1000
        // This tier applies after both higher cash-flow checks failed.
        financialStatus = "Limited cash flow";
    } 
    else {                         // Implies < 500
        financialStatus = "Financially strained";
    }

    log(financialStatus, width, true);

    string creditStatus;
    if (creditScore >= 750) {
        // Choose the highest credit-score tier first.
        creditStatus = "Excellent";
    } 
    else if (creditScore >= 670) {
        // This tier applies after the higher credit-score check failed.
        creditStatus = "Good";
    } 
    else if (creditScore >= 580) {
        // This tier applies after both higher credit-score checks failed.
        creditStatus = "Fair";
    }
    else {
        creditStatus = "Poor";
    }

    log(creditStatus, width, true);

    if(carPrice > 12 * income || remainingMoney < 0) {
        // Warn if the car costs over 12 times income or expenses exceed income.
        log("WARNING: High financial risk!", width, true);
    }

    if (remainingMoney >= 1000 && savings >= downPayment && creditScore >= 670) {
        // All three checks must pass before recommending the purchase.
        log("Financially prepared for your car!", width, true);
        if(hasEmergencyFund) {
            // Mention the extra safety cushion when it is present.
            log("You have a 3 month emergency fund too.", width, true);
        }
        if(highDebtRisk) {
            // Warn about debt risk even if the other readiness checks pass.
            log("You are at risk of high debt! Proceed with caution.", width, true);
        }
    }
    
    return 0;
}