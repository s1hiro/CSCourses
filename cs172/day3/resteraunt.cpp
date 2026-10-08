#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <sstream>
#include <string>
#include <format>
using namespace std;

int guiWidth = 50;

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
}

string centerString(string text, string emptySpaceChar = " ") {
	string spacing = repeatOneChar(emptySpaceChar, (guiWidth - text.length()) / 2);
	return spacing + text + spacing;
}

void printBigBorder() {
        log(repeatOneChar("=", guiWidth), true);
};

void printThinBorder() {
        log(centerString(repeatOneChar(" - ", guiWidth / 3)), true);
}

void introText() {
	string introText = "Welcome to S1Delights!";
	printBigBorder();
        log(centerString(introText), true);
        printBigBorder();
}

int charCounter(string text) {
	int count = 0;
	for(int i = 0; i < text.length(); i++) { count++;};
	return count;
}

void menu() {
	for(auto& product : products) {
                string name = product.first;
		double price = product.second;

		stringstream stream;
		stream << fixed << setprecision(2) << price;
		string strPrice = "$" + stream.str();

                log(name);
		cout << setw(guiWidth - charCounter(name));
		log(strPrice, true);
        }
}

int main() {
	string currentItem;
	int currentAmount;
	string tempInp;

	introText();

	log(centerString("Here is our menu."), true);
	printThinBorder();
	menu();
	printThinBorder();

	int keepOrdering = 1; //0 = stop, 1 = keepOrdering
	int count = 0;
	while(keepOrdering != 0) {
		if(count < 1) {
			log("What would you like to order? ");
		} else {
			log("Would you like anything else? ");
			if(count % 5 == 0) {
				log("Here is our menu again.", true);
				printThinBorder();
				menu();
				printThinBorder();
			}
		}

		cin >> tempInp;

		if(tempInp == "No" || tempInp == "no" || tempInp == "n" || tempInp == "N") {
			keepOrdering = 0;
			break;
		} else {
			currentItem = tempInp;
		}

		//if currentItem === someItemWeHave
		log("Great choice. How many? ");
		cin >> tempInp;
		currentAmount = stoi(tempInp);

		order[currentItem] += currentAmount;
		count++;
	}

	printBigBorder();
	log(centerString("Ok, Thank you for ordering!"), true);
	printBigBorder();
	log(centerString("Here is your receipt:"), true);

	double totalExpense = 0;

	for(auto& item : order) {
	        string name = item.first;
	        string amount = to_string(item.second);

	        // 1. Build and log the item text
	        string leftText = name + repeatOneChar(" ", 11 - name.length()) + "x " + amount;
	        log(leftText);

	        // 2. Calculate and format the total price
	        double totalCost = stoi(amount) * products[name];

		totalExpense += totalCost;

	        stringstream stream;
	        stream << fixed << setprecision(2) << totalCost;
	        string totalPriceOfItem = "$" + stream.str();

	        // 3. Align and log the formatted price string
	        cout << setw(guiWidth - charCounter(leftText));
	        log(totalPriceOfItem, true);
    	}

	double taxAmount = totalExpense * .08;

	stringstream stream;

	stream << fixed << setprecision(2) << taxAmount;
	string strTaxAmount = "$" + stream.str();

	double tipAmount = 0;
	string tempInput;

	log("+8% Tax" + repeatOneChar(" ", guiWidth - 7 - strTaxAmount.length()) + strTaxAmount, true);
	printThinBorder();
	log("Would you be so kind as to leave a hearty tip for\nthe S1Delights waiter? He has worked incredibly\nhard for this job. (%): ");
	cin >> tempInput;
	printThinBorder();
	if(tempInput == "No" || tempInput == "no" || tempInput == "n" || tempInput == "N") {
		log("Thank you for considering it.", true);
	} else {
		tipAmount = totalExpense * (stod(tempInput) / 100);

		stringstream stream;
		stream << fixed << setprecision(2) << tipAmount;
		string strTipAmount = "$" + stream.str();

		log("+ Tip :)" + repeatOneChar(" ", guiWidth - 8 - strTipAmount.length()) + strTipAmount, true);
		printThinBorder();
	}

	stream.str("");
        stream << fixed << setprecision(2) << totalExpense + taxAmount + (tipAmount ? tipAmount : 0);
        string strTotalExpense = "$" + stream.str();

	log("Total:" + repeatOneChar(" ", guiWidth - 6 - strTotalExpense.length()) + strTotalExpense, true);
	printBigBorder();
	log(centerString("Thanks for dining at S1Delights! Hope you return."), true);
	printBigBorder();
};
