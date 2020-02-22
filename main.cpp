/*
 * Title: heap.cpp Homework 6
 * Abstract: heap.cpp receives an input size and a series of numbers and stores
 * then in an array. The program then determines if this array is a heap.
 * Options are then presented to the user for further operations.
 * Author: Christopher Piwarski
 * ID: 0026
 * Date: February 20, 2020
 */

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/*
This function prints out a selection menu for the user.
 */
void printMenu() {
    cout << "Select an operation" << endl;
    cout << "\t1: Insert a number" << endl;
    cout << "\t2: Delete the max" << endl;
    cout << "\t3: Heapsort and Quit" << endl;
}

/*
 * This function receives an integer array and integer size and determines
 * if the array is a max heap.
 */
bool isHeap(int *heap, int size) {
    bool isHeap = true;

    for(int i = 1; i <= (size / 2); i++) {
        int parent = heap[i];
        int child1 = heap[2 * i];
        int child2 = heap[(2 * i) + 1];
        if ( parent < child1 || parent < child2) {
            isHeap = false;
            break;
        }
    }

    return isHeap;
}

/*
 * This function implements the textbook defined algorithm for heapifying
 * an array.
 */
int* heapify(int* heap, int size) {

    int itemCount = size - 1;
    for( int i = (itemCount/ 2) + 1; i >= 1; i--) {
        int k = i;
        int v = heap[k];
        bool heapCheck = false;
        while (!heapCheck && 2 * k <= itemCount) {
            int j = 2 * k;
            if (j < itemCount) {
                if (heap[j] < heap[j + 1]) {
                    j++;
                }
            }
            if (v > heap[j]) {
                heapCheck = true;
            } else {
                heap[k] = heap[j];
                k = j;
            }
        }
        heap[k] = v;
    }
    return heap;
}

/*
 * This function inserts a user defined value into the heap array.
 */
int* insertNumber(int *heap, int size) {
    int newNum;
    int newSize = size + 2;
    int* newHeap = new int[newSize];
    newHeap[0] = 0;

    cout << "Enter a number: ";
    cin >> newNum;
    for(int i = 1; i <= newSize; i++){
        newHeap[i] = heap[i];
    }
    newHeap[newSize - 1] = newNum;

    heapify(newHeap, newSize);
    return newHeap;
}


/*
 * This function deletes the max value for a heap and returns the new heap
 * in array form.
 */
int* deleteMax(int *oldHeap, int size) {
    int* newHeap = new int[size];
    int lastChild = oldHeap[size];
    oldHeap[1] = lastChild;
    newHeap[0] = 0;

    // Put heap values into smaller array
    for(int i = 1; i <= size; i++) {
        newHeap[i] = oldHeap[i];
    }
    cout << endl;

    heapify(newHeap, size);
    return newHeap;
}

/*
 * This function receives an array and prints out the contents
 * in order.
 */
void printHeap(int *heap, int size) {
    for (int i = 1; i <= size; i++) {
        cout << heap[i] << " ";
    }
    cout << endl;
}

/*
 * The main function governs the operation of heap.cpp
 */
int main()
{
    // Declare variables
    int size;
    int value;
    int selection = 0;
    int heapCounter = 1;
    int* heap;
    bool initCheck;
    string userValues;
    string userInput;

    // Gather user information and initialize
    cout << "Input Size:  ";
    cin >> size;
    cin.ignore();
    heap = new int[size + 1];
    for (int i = 0; i < size; i++) {
        heap[i] = 0;
    }

    // Receive heap values
    cout << "Enter numbers: ";
    getline(cin, userValues);
    stringstream sstream (userValues);
    while (sstream >> value) {
        heap[heapCounter] = value;
     heapCounter++;
    }

    // Handle heapify initial values if necessary
    initCheck = isHeap(heap, size);
    if (initCheck) {
        cout << "This is a heap" << endl;
    } else {
        cout << "This is NOT a heap" << endl;
        heap = heapify(heap, size + 1);
        cout << "Heap constructed: ";
        printHeap(heap, size);
    }

    // Enter user menu loop
    while (selection != 3) {
        printMenu();
        cin >> selection;

        switch (selection) {
            case 1:
                heap = insertNumber(heap, size);
                size++;
                cout << "Updated heap: ";
                printHeap(heap, size);
                break;
            case 2:
                heap = deleteMax(heap, size);
                size--;
                cout << "Updated heap: ";
                printHeap(heap, size);
                break;
        }
    }

    // Report final heap values and exit
    heap = heapify(heap, size);
    cout << "Heapsort: ";
    printHeap(heap, size);
    cout << "Bye!" << endl;
}

