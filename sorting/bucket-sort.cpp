#include <iostream>
#include <chrono>
#include <time.h>
using namespace std::chrono;
using namespace std;

void printArray(int* arr, int size){
    for (int i=0; i<size; i++){
        cout << arr[i] << " ";
    }
}

void bucketSort(int* arr, int size){
    if (size <= 0) return;
    //cout << "\nArray unsorted\n";
    //printArray(arr, size);

    auto start = high_resolution_clock::now();

    int minVal = arr[0]; // our range starts from 0
    int maxVal = arr[0];

    for (int i=0; i<size; i++){
        if (arr[i] <= minVal) minVal = arr[i];
        if (arr[i] >= maxVal) maxVal = arr[i];
    }

    int BucketRange = maxVal - minVal + 1;
    int* Bucket = new int[BucketRange];
    for (int i=0; i<BucketRange; i++){
        Bucket[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        int index = arr[i] - minVal;   
        Bucket[index]++;
    }

    int j = 0;
    for (int i = 0; i < BucketRange; i++) {
        while (Bucket[i] > 0) {
            arr[j++] = i + minVal;
            Bucket[i]--;
        }
    }
    delete[] Bucket;

    auto stop = high_resolution_clock::now();
    auto ns = duration_cast<nanoseconds>(stop - start).count();
    auto ms = duration_cast<milliseconds>(stop - start).count();
    cout << "\nSorting time: " << ns << " ns\n";

    //cout << "\nPrinting array sorted\n";
    //printArray(arr, size);
    //cout << "\n\n";
}

// random fill
void fillRandom(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand()%size;
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

int main(){
    srand(time(NULL));

    int size = 50000;

    int* arr1 = new int[size];
    int* arr2 = new int[size];
    int* arr3 = new int[size];

    fillRandom(arr1, size);
    fillNearlySorted(arr2, size);
    fillReversed(arr3, size);

    cout << "Size of array: " << size << endl;
    cout << "Random filled array";
    bucketSort(arr1, size);
    cout << "\nNearly sorted filled array";
    bucketSort(arr2, size);
    cout << "\nReversed order filled array";
    bucketSort(arr3, size);

    return 0;
}