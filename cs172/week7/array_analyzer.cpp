#include "../lib/my_funcs.hpp"
using namespace std;

int main() {
    constexpr size_t SIZE = 8;
    int scores[SIZE] = {};

    for(size_t i = 0; i < SIZE; i++) {
        scores[i] = ask<int>("Please input a score from 0-100: ", 80, false, 0);
    }
    int total = 0;
    double average = 0;
    int scores70OrAbove = 0;
    int high, low = scores[0];

    for(size_t i = 0; i < SIZE; i++) {
        int n = scores[i];
        total += n;
        if(n >= 70) scores70OrAbove++;
        if(i != 0) {
            if(n > high) high = n;
            if(n < low) low = n;
        }
    }

    average = total / SIZE;

    log(centerString("Score Analysis", 80, "="), true);
    log("Scores: " + separateBy(scores, ", "), true);
    log("Total: " + to_string(total), true);
    cout << "Average: " << fixed << setprecision(1) << average << endl;
    log("Scores >= 70: " + to_string(scores70OrAbove), true);
    log("Highest: " + to_string(high), true);
    log("Lowest: " + to_string(low), true);

    int search = ask<int>("Search for score: ", 80, false);

    vector<int> matches = {};
    for(size_t i = 0; i < SIZE; i++) {
        int currScore = scores[i];
        if(currScore == search) {
            if(matches.size() == 0) {
                log("First match at position " + i, true);
            } 
            matches.emplace_back(i);
        }
    }

    if (matches.size() > 0) log("All matches: " + separateBy(matches, ", "), true);
}
