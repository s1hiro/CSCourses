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
        if(n >= 70) {
            // Count scores that meet the 70-point threshold.
            scores70OrAbove++;
        }
        if(i != 0) {
            // Skip the first score when checking later values against the bounds.
            if(n > high) {
                // Replace the highest value when this score is larger.
                high = n;
            }
            if(n < low) {
                // Replace the lowest value when this score is smaller.
                low = n;
            }
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
            // Add only scores equal to the user's search value.
            if(matches.size() == 0) {
                // Show the position of the first matching score.
                log("First match at position " + i, true);
            } 
            matches.emplace_back(i);
        }
    }

    if (matches.size() > 0) {
        // Print the match list only when at least one score was found.
        log("All matches: " + separateBy(matches, ", "), true);
    }
}
