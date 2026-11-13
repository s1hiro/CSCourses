#include “../../lib/my_funcs.h”
using namespace std;

int main() {
    size_t SIZE = 8;
    int scores[SIZE] = {};
    for(size_t i = 0; i < SIZE; i++) {
        scores.push_back(ask<int>(
            “Please input a score from 0-100: “, 
            newline=false, width=80, recreate ask as 
            num));
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
    log(centerString(“Score Analysis”, “=“, 80),
    true);
    log(“Scores: “ + separateBy(scores, “, “), true);
    log(“Total: “ + total, true);
    cout << fixed << setprecision(1) << average << 
    endl;
    log(“Scores >= 70: “ + scores70OrAbove, true);
    log(Highest: “ + high, true);
    log(Lowest: “ + low, true);
    int search = ask<int>(
        “Search for score: “,
        nl=false,
        w=80,
        min=0
    );
    vector<int> matches = {};
    for(size_t i = 0; i < SIZE; i++) {
        int currScore = scores[i];
        if(currScore == search)
            if(matches.size == 0) {
                log(“First match at position “ + i, true);
            } 
            matches.emplace_back(i);
        }
    }
    log(“All matches: “ + separateBy(matches, “, “), 
            true
    );
}
