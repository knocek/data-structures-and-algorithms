#include <iostream>
#include <time.h>
#include <chrono>
using namespace std::chrono;
using namespace std;

size_t extraBytesCurrent = 0;
size_t extraBytesPeak = 0; 
void memAdd(size_t bytes){
    extraBytesCurrent += bytes;
    if (extraBytesCurrent > extraBytesPeak)
        extraBytesPeak = extraBytesCurrent;
}
void memFree(size_t bytes){
    if (bytes > extraBytesCurrent){
        extraBytesCurrent = 0;
    } else {
        extraBytesCurrent -= bytes;
    }
}
void resetMemUsage(){
    extraBytesCurrent = 0;
    extraBytesPeak = 0;
}

void quickSort(int* arr, int size) {
    if (size <= 1) return;

    int i = 0, j = size - 1;
    int pivot = arr[size / 2];

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++; j--;
        }
    }
    if (0 < j) quickSort(arr, j + 1);
    if (i < size - 1) quickSort(arr + i, size - i);
}

void bucketSort(int* arr, int size) {

    if (size <= 0) return;
    int minVal = arr[0]; // our range starts from 0
    int maxVal = arr[0];

    for (int i=0; i<size; i++){
        if (arr[i] <= minVal) minVal = arr[i];
        if (arr[i] >= maxVal) maxVal = arr[i];
    }

    int BucketRange = maxVal - minVal + 1;
    int* Bucket = new int[BucketRange];

    memAdd(BucketRange * sizeof(int));

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
    memFree(BucketRange * sizeof(int));
}

void mergeSort(int* arr, int size) {
    if (size <= 1) return;

    int mid = size / 2;
    mergeSort(arr, mid);
    mergeSort(arr + mid, size - mid);

    int* temp = new int[size];
    memAdd(size * sizeof(int));

    int i = 0, j = mid, k = 0;
    while (i < mid && j < size) {
        if (arr[i] < arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i < mid) {
        temp[k++] = arr[i++];
    }
    while (j < size) {
        temp[k++] = arr[j++];
    }

    for (i = 0; i < size; i++) {
        arr[i] = temp[i];
    }

    delete[] temp;
    memFree(size * sizeof(int));
}

void printArray(int* arr, int size) {
    for (int i=0; i<size; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(){
    srand(time(NULL));
    int size = 1000;
    int* arrQuickSort = new int[size];
    int* arrBucketSort = new int[size];
    int* arrMergeSort = new int[size];

    for (int i=0; i<size; i++){
        arrQuickSort[i] = rand()%size;
        arrMergeSort[i] = arrQuickSort[i];
        arrBucketSort[i] = arrQuickSort[i];
    }

    cout << "Size of array: " << size << endl;
    resetMemUsage();
    auto start = high_resolution_clock::now();
    quickSort(arrQuickSort, size);
    auto stop = high_resolution_clock::now();
    auto ns = duration_cast<nanoseconds>(stop - start).count();
    cout << "Sorting time [quickSort]: " << ns << " ns\n";
    cout << "In-place quicksort extra memory used (peak): " << extraBytesPeak << " bytes\n";
    //printArray(arrQuickSort, size);

    resetMemUsage();
    auto start2 = high_resolution_clock::now();
    bucketSort(arrBucketSort, size);
    auto stop2 = high_resolution_clock::now();
    auto ns2 = duration_cast<nanoseconds>(stop2 - start2).count();
    cout << "Sorting time [bucketSort]: " << ns2 << " ns\n";
    cout << "Not in-place bucket sort extra memory used (peak): " << extraBytesPeak << " bytes\n";
    //printArray(arrBucketSort, size);

    resetMemUsage();
    auto start3 = high_resolution_clock::now();
    mergeSort(arrMergeSort, size);
    auto stop3 = high_resolution_clock::now();
    auto ns3 = duration_cast<nanoseconds>(stop3 - start3).count();
    cout << "Sorting time [mergeSort]: " << ns3 << " ns\n";
    cout << "Not in-place merge sort extra memory used (peak): " << extraBytesPeak << " bytes\n";
    //printArray(arrMergeSort, size);

    delete[] arrQuickSort;
    delete[] arrBucketSort;
    delete[] arrMergeSort;
    return 0;
}