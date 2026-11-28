#include <iostream>
#include "../lib/my_funcs.hpp"
using namespace std;

void increaseStock(int *ptr, int amount) {
  *ptr = *ptr + amount;
}

int main() {
  const int SIZE = 5;
  int inventory[SIZE] = {12, 8, 20, 5, 15};
  int *ptr = inventory;

  // Task 1: Print all values using *(ptr + i).
  vector<int> ptrList = {};
  for(size_t i = 0; i < SIZE; i++) {
    ptrList.push_back(*(ptr + i));
  }
  log("Pointer list: " + separateBy(ptrList, ", "), true);

  // Task 2: Change third value to 30 using a pointer.
  *(ptr + 2) = 30;

  // Task 3: Prompt for an index (0 to 4) and new value.
  int newIdx = ask<int>("Please enter an index from 0 to 4: ", 80, false);
  double newNum = ask<double>("Please enter a new number for index " + to_string(newIdx) + ": ", 80);
  string strIdx = to_string(newIdx);
  log("idx: " + strIdx + " mod 1: " + to_string(newIdx % 1));
  *(ptr + newIdx) = newNum;

  // Check that the index is valid before accessing it.
  // ^done in ask.tpp
  // Task 4: Print updated inventory using pointer notation.
  ptrList.clear();
  for(size_t i = 0; i < SIZE; i++) {
    ptrList.push_back(*(ptr + i));
  }
  log("Pointer list: " + separateBy(ptrList, ", "), true);

  return 0;
}