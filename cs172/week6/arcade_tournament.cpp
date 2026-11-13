#include "../lib/my_funcs.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*
    request three player names and nonnegative scores; 
    greet each player; print all three scores; 
    determine the highest score; 
    announce the winning name. If the top score is tied, 
    clearly report a tie instead of arbitrarily selecting 
    a champion.
*/

size_t width = 80;

void showBanner();

void greetPlayer(string name) {
    log("Welcome, " + name + "!", true);
};

void announceScore(string player, int points) {
    log(player + " Scored " + to_string(points) + " points!", true);
};

void showChampion(string name) {
    log(name + " is the champion!", true);
};

void showGoodbye() {
    log("Thanks for playing at S1Arcade!", true);
}

int main() {
    char cont = 'n';
    do {
        log("Please input 3 names!", true);
        vector<pair<string, int>> players = {};
        for(size_t i = 0; i < 3; i++) {
            string tempName = ask<string>("Name " + to_string(i + 1) + ": ", width, true);
            double tempScore = ask<double>(tempName + "'s Score: ", width, true);
            players.emplace_back(tempName, tempScore);
            greetPlayer(tempName);
        }

        for(size_t i = 0; i < 3; i++) {
            announceScore(players[i].first, players[i].second);
        }

        //sort(arg1, arg2) tells sort what range of what 
        //vector/list to sort
        sort(players.begin(), players.end(), 
        [](const auto& player1, const auto& player2) {
            return player1.second > player2.second;
        });

        //[](args)
        //is a lambda function -- like () => {} in js.
        //this is how sort should sort; you provide logic

        //BUT, args must be defined explicitly and how 
        //you plan to use it - whether by reference,
        //or by copy

        if(
            players[0].second == players[1].second ||
            players[1].second == players[2].second ||
            players[0].second == players[2].second
        ) {
            // Any matching pair means the players are tied for the top score.
            log("There was a tie! No champions.", true);
        } else { 
            showChampion(players[0].first);
        }

        cont = ask<char>(
            "Would you like to continue? (y/n) ", 
            80, 
            vector<variant<char>>{'y', 'Y', 'n', 'N'}, 
            false
        );
    } while ( cont == 'y' || cont == 'Y' );
    showGoodbye();

    return 0;
}

void showBanner() {
    printBorder(80, "=");
    log("Welcome to S1Arcade!", true);
    printBorder(80, "=");
};