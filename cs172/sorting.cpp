#include <iostream>
using namespace std;

void printArray(const int a[], int size) {
  for (int i = 0; i < size; i++) cout << a[i] << " ";
  cout << endl;
}

void bubbleSort(int& arr[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

int main() {
  int numbers[8] = {42, 17, 8, 99, 23, 5, 61, 14};
  cout << format(“{}”, “Original: {}”, 
                 seperateBy(numbers, “, “, false)
                 }
  bubbleSort(numbers, 8);
  cout << format(“{}”, “Sorted: “, 
                 seperateBy(numbers, “, “, false));
  return 0;
}
