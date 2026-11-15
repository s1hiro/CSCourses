#include "../lib/my_funcs.hpp"
#include <format>
#include <iostream>
using namespace std;

void bubbleSort(int arr[], int size) {
    size_t ifchecks = 0;
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            ifchecks++;
            if (arr[j] > arr[j + 1]) {
                swapped = true;
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
        if(!swapped) break;
    }
    log("Bubble Sort Checks: " + to_string(ifchecks), true);
}

void selectionSort(int arr[], int size) {
    size_t ifchecks = 0;
    for (int i = 0; i < size - 1; i++) {
        int lowIdx = i;
        for(int j = i + 1; j < size; j++) {
            ifchecks++;
            if(arr[j] < arr[lowIdx]) lowIdx = j;
        }

        int temp = arr[i];
        arr[i] = lowIdx;
        arr[lowIdx] = temp;
    }
    log("Insertion Sort Checks: " + to_string(ifchecks), true);
}

int main() {
    int bubbleNumbers[8] = {42, 17, 8, 99, 23, 5, 61, 14};
    int selectionNumbers[8] = {42, 17, 8, 99, 23, 5, 61, 14};

    cout << format("Original: {}", separateBy(bubbleNumbers, ", ")) << endl;

    bubbleSort(bubbleNumbers, 8);
    cout << format("Bubble Sorted: {}", separateBy(bubbleNumbers, ", ")) << endl;

    selectionSort(selectionNumbers, 8);
    cout << format("Selection Sorted: {}", separateBy(selectionNumbers, ", ")) << endl;

    return 0;
}
