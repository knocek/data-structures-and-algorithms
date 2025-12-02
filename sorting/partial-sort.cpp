#include <iostream>
#include <string>
#include <time.h>
#include <algorithm> // for swap
#include <chrono>
using namespace std::chrono;
using namespace std;

template<typename type>
void shiftDown(type* h, int heapSize, int i){
    while (true) {
        int left = 2 * i + 1; // left child
        int right = 2 * i + 2; // right child
        int largest = i;

        if (left < heapSize && h[left] > h[largest]) largest = left;
        if (right < heapSize && h[right] > h[largest]) largest = right;

        if (largest == i) break; // heap is OK

        swap(h[i], h[largest]);
        i = largest;
    }
}

template<typename type>
void buildHeapDown(type* h, int heapSize){
    for (int i = heapSize/2 -1; i >= 0; --i){
        shiftDown(h, heapSize, i);
    }
}

// partialSort
template<typename type>
int partialSort(const type* arr, int n, int k, type* heapOut){

    auto start = high_resolution_clock::now();

    if (n <= 0 || k <= 0) return 0;

    int heapSize = (k < n) ? k : n;

    // build heap with k elements
    for (int i = 0; i < heapSize; ++i) {
        heapOut[i] = arr[i];
    }
    buildHeapDown(heapOut, heapSize);

    for (int i = heapSize; i < n; ++i) {
        if (arr[i] < heapOut[0]) {
            heapOut[0] = arr[i];
            shiftDown(heapOut, heapSize, 0);
        }
    }

    for (int i = heapSize - 1; i>0; --i) {
        swap(heapOut[0], heapOut[i]);
        shiftDown(heapOut, i, 0);
    }

    auto stop = high_resolution_clock::now();
    auto ns = duration_cast<nanoseconds>(stop - start).count();
    cout << "\nPartial sorting time: " << ns << " ns\n";

    return heapSize;
}

// random fill
template<typename type>
void fillRandom(type* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand()%size;
    }
}

// nearly sorted fill
template<typename type>
void fillNearlySorted(type* arr, int size){
    for (int i = 0; i < size; i++) {
        arr[i] = i+1;
    } 
    int swaps = size/100;
    if (swaps<1) swaps = 1;

    for (int k = 0; k < swaps; k++) {
        int i = rand() % (size - 1);   // index from 0 to size-2
        // swaps elements
        int tmp = arr[i]; 
        arr[i] = arr[i + 1];
        arr[i + 1] = tmp;
    }
}

template<typename T>
void printArray(const T* arr, int size) {
    for (int i = 0; i < size; ++i) cout << arr[i] << " ";
    cout << "\n";
}

int main(){

    srand(time(NULL));

    int size = 10000;
    int k = 50; // how much values sorted

    int* arr1 = new int[size];
    int* arr2 = new int[size];

    fillRandom(arr1, size);
    fillNearlySorted(arr2, size);

    cout << "Size of array: " << size << endl;
    cout << "\nRandom filled array";
    //cout << "\nbefore sorting\n";
    //printArray(arr1, size);
    
    int* topRandom = new int[k];
    int foundRandom = partialSort(arr1, size, k, topRandom);
    cout << "Top " << foundRandom << " min values (ascending) from random:\n";
    printArray(topRandom, foundRandom);

    cout << "\nNearly sorted filled array";
    //cout << "\nbefore sorting\n";
    //printArray(arr2, size);
    int* topNearlySorted = new int[k];
    int foundNearlySorted = partialSort(arr2, size, k, topNearlySorted);
    cout << "Top " << foundNearlySorted << " min values (ascending) from nearly sorted:\n";
    printArray(topNearlySorted, foundNearlySorted);

    delete[] arr1;
    delete[] arr2;
    delete[] topRandom;
    delete[] topNearlySorted;

    return 0;
}