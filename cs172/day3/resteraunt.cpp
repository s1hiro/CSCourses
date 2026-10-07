#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <sstream>
#include <string>
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
        for(auto& product : products) {
                string name = product.first;
                order.insert({name, 0});
        };

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

        cout << endl;
};
