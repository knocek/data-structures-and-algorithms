#include <iostream>
#include <time.h>
#include <chrono>
using namespace std::chrono;
using namespace std;

long long cmpCount = 0; // comparison keys counter
long long movCount = 0; // key movement counter

// bubble sort
void bubbleSort(int* arr, int size){
    for (int step=0; step < (size-1); step++){
        bool swapped = false;

        for (int i=0; i<(size-step-1); i++){
            cmpCount++;
            if (arr[i] > arr[i+1]) {
                movCount++;
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr [i+1] = temp;

                swapped = true;
            }
        }

        if (swapped == 0) break;
    }
}

// inserion sort
void insertionSort(int* arr, int size){
    for (int i=1; i<size; i++){
        int key = arr[i];
        int compare = i-1;

        while (compare >=0 && arr[compare] > key) {
            cmpCount++;
            movCount++;
            arr[compare+1] = arr[compare];
            compare--;
        }
        movCount++;
        arr [compare+1] = key;
    }
}

// selection sort
void selectionSort(int* arr, int size){
    for (int i=0; i<size-1; i++){
        int min_index = i;

        for (int j=i+1; j<size; ++j) {
            cmpCount++;
            if (arr[j] < arr[min_index]) min_index = j;
        }
        if (min_index != i){
            movCount++;
            swap(arr[i], arr[min_index]);
        }
    }

}

// comb sort - bubble sort with gap=arraySize*10/13, when gap=1, sorting ends
void combSort(int* arr, int size){
    int gap = size;
    bool replace = true;

    while (gap > 1 || replace){
        gap = gap*10/13;
        if (gap == 0) gap = 1;

        replace = false;
        for (int i=0; i+gap<size; i++){
            cmpCount++;
            if (arr[i+gap] < arr[i]){
                movCount++;
                swap(arr[i], arr[i+gap]);
                replace = true;
            }
        }
    }
}

/// shell sort - optimalizaton of insertion sort, elements can be moved over larger distances
void shellSort(int* arr, int size){ 
    for (int gap = size/2; gap>0; gap /= 2){
        for (int i = gap; i < size; i++){
            int temp = arr[i];
            int j = i;

            while (j>=gap && arr[j-gap] > temp) {
                cmpCount++;
                movCount++;
                arr[j] = arr[j-gap];
                j -= gap;
            }
            movCount++;
            arr[j] = temp;
        }
    }
}

// random fill
void fillRandom(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }
}

// reverse tab fill
void fillReversed(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = size-1-i;
    } 
}

// nearly sorted fill
void fillNearlySorted(int* arr, int size){
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

// copy array
void copyArray(int* dest, const int* src, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

// measure time
void measureTime(const string& name, void (*sortFunc)(int*, int), int* source, int size) {
    int* tmp = new int[size];
    copyArray(tmp, source, size);

    cmpCount = 0;
    movCount = 0;

    auto start = high_resolution_clock::now();
    sortFunc(tmp, size);
    auto stop = high_resolution_clock::now();

    // time measured in different units
    auto ns = duration_cast<nanoseconds>(stop - start).count();
    auto us = duration_cast<microseconds>(stop - start).count();
    auto ms = duration_cast<milliseconds>(stop - start).count();
    double sec = (stop - start).count() * 1e-9;

    cout << name << ":\n";
    cout << "Seconds: " << sec << " s  //  ";
    cout << "Milliseconds: " << ms  << " ms  //  ";
    cout << "Nanoseconds: " << ns  << " ns\n";
    cout << "Comparisons: " << cmpCount << "  |  Moves: " << movCount << "\n\n";

    delete[] tmp;
}

// print arrays
void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

int main () {
    srand(time(NULL));

    int size1 = 1000, size2 = 5000, size3 = 10000;
    // random fill arrays
    int* arr1 = new int[size1];
    int* arr2 = new int[size2];
    int* arr3 = new int[size3];
    // reverse arrays
    int* arr4 = new int[size1];
    int* arr5 = new int[size2];
    int* arr6 = new int[size3];
    // nearly sorted arrays
    int* arr7 = new int[size1];
    int* arr8 = new int[size2];
    int* arr9 = new int[size3];

    fillRandom(arr1, size1);
    fillRandom(arr2, size2);
    fillRandom(arr3, size3);

    fillReversed(arr4, size1);
    fillReversed(arr5, size2);
    fillReversed(arr6, size3);

    fillNearlySorted(arr7, size1);
    fillNearlySorted(arr8, size2);
    fillNearlySorted(arr9, size3);

    /* for (int i=0; i<size1; i++){
        cout << arr1[i] << " ";
    } */

    cout << "RANDOM FILLED ARRAYS\n";
    cout << "Size of array: " << size1 << endl;
    measureTime("Bubble sort  ", bubbleSort, arr1, size1);
    measureTime("Insertion sort", insertionSort, arr1, size1);
    measureTime("Selection sort", selectionSort, arr1, size1);
    measureTime("Comb sort    ", combSort, arr1, size1);
    measureTime("Shell sort   ", shellSort, arr1, size1);
    cout << endl;

    cout << "Size of array: " << size2 << endl;
    measureTime("Bubble sort  ", bubbleSort, arr2, size2);
    measureTime("Insertion sort", insertionSort, arr2, size2);
    measureTime("Selection sort", selectionSort, arr2, size2);
    measureTime("Comb sort    ", combSort, arr2, size2);
    measureTime("Shell sort   ", shellSort, arr2, size2);
    cout << endl;

    cout << "Size of array: " << size3 << endl;
    measureTime("Bubble sort  ", bubbleSort, arr3, size3);
    measureTime("Insertion sort", insertionSort, arr3, size3);
    measureTime("Selection sort", selectionSort, arr3, size3);
    measureTime("Comb sort    ", combSort, arr3, size3);
    measureTime("Shell sort   ", shellSort, arr3, size3);
    cout << endl;

    cout << "\nREVERSED ARRAYS\n";
    cout << "Size of array: " << size1 << endl;
    measureTime("Bubble sort  ", bubbleSort, arr4, size1);
    measureTime("Insertion sort", insertionSort, arr4, size1);
    measureTime("Selection sort", selectionSort, arr4, size1);
    measureTime("Comb sort    ", combSort, arr4, size1);
    measureTime("Shell sort   ", shellSort, arr4, size1);
    cout << endl;

    cout << "Size of array: " << size2 << endl;
    measureTime("Bubble sort  ", bubbleSort, arr5, size2);
    measureTime("Insertion sort", insertionSort, arr5, size2);
    measureTime("Selection sort", selectionSort, arr5, size2);
    measureTime("Comb sort    ", combSort, arr5, size2);
    measureTime("Shell sort   ", shellSort, arr5, size2);
    cout << endl;

    cout << "Size of array: " << size3 << endl;
    measureTime("Bubble sort  ", bubbleSort, arr6, size3);
    measureTime("Insertion sort", insertionSort, arr6, size3);
    measureTime("Selection sort", selectionSort, arr6, size3);
    measureTime("Comb sort    ", combSort, arr6, size3);
    measureTime("Shell sort   ", shellSort, arr6, size3);
    cout << endl;

    cout << "\nNEARLY SORTED ARRAYS\n";
    cout << "Size of array: " << size1 << endl;
    measureTime("Bubble sort  ", bubbleSort, arr7, size1);
    measureTime("Insertion sort", insertionSort, arr7, size1);
    measureTime("Selection sort", selectionSort, arr7, size1);
    measureTime("Comb sort    ", combSort, arr7, size1);
    measureTime("Shell sort   ", shellSort, arr7, size1);
    cout << endl;

    cout << "Size of array: " << size2 << endl;
    measureTime("Bubble sort  ", bubbleSort, arr8, size2);
    measureTime("Insertion sort", insertionSort, arr8, size2);
    measureTime("Selection sort", selectionSort, arr8, size2);
    measureTime("Comb sort    ", combSort, arr8, size2);
    measureTime("Shell sort   ", shellSort, arr8, size2);
    cout << endl;

    cout << "Size of array: " << size3 << endl;
    measureTime("Bubble sort  ", bubbleSort, arr9, size3);
    measureTime("Insertion sort", insertionSort, arr9, size3);
    measureTime("Selection sort", selectionSort, arr9, size3);
    measureTime("Comb sort    ", combSort, arr9, size3);
    measureTime("Shell sort   ", shellSort, arr9, size3);
    cout << endl;

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete[] arr7;
    delete[] arr8;
    delete[] arr9;

    /////////////////
    ////////////////////// TESTING ZONE
    //////////////////////
    cout << "\n\nTESTING\n";
    int sizeTest = 10;
    int* arrTest = new int [sizeTest];

    cout << "array before sorting (RANDOM)\n";
    for (int i = 0; i < sizeTest; i++) {
        int randomTest = rand()%20;
        arrTest[i] = randomTest;
        cout << arrTest[i] << " ";
    }
    
    cout << "\narraytest sorted\n";
    //bubbleSort(arrTest, sizeTest);
    //insertionSort(arrTest, sizeTest);
    //selectionSort(arrTest, sizeTest);
    //combSort(arrTest, sizeTest);
    shellSort(arrTest, sizeTest);
    printArray(arrTest, sizeTest);

    int* arrTest2 = new int [sizeTest];

    fillReversed(arrTest2, sizeTest);
    cout << "\narray2 before sorting (FILL REVERSED)\n";
    printArray(arrTest2, sizeTest);
    
    cout << "arraytest2 sorted\n";
    //bubbleSort(arrTest2, sizeTest);
    //insertionSort(arrTest2, sizeTest);
    //selectionSort(arrTest2, sizeTest);
    //combSort(arrTest2, sizeTest);
    shellSort(arrTest2, sizeTest);
    printArray(arrTest2, sizeTest);

    int* arrTest3 = new int [sizeTest];

    fillNearlySorted(arrTest3, sizeTest);
    cout << "\narray3 before sorting (NEARLY SORTED)\n";
    printArray(arrTest3, sizeTest);
    
    cout << "arraytest3 sorted\n";
    //bubbleSort(arrTest3, sizeTest);
    //insertionSort(arrTest3, sizeTest);
    //selectionSort(arrTest3, sizeTest);
    //combSort(arrTest3, sizeTest);
    shellSort(arrTest3, sizeTest);
    printArray(arrTest3, sizeTest);

    ///////////////// testing zone ended ////////////////////
    ////////////////////////
    /////////////////////////////////////////////

    return 0;
}