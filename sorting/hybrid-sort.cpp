#include <iostream>
#include <time.h>

using namespace std;

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
}

void insertionSort(int* arr, int size){
    for (int i=1; i<size; i++){
        int key = arr[i];
        int compare = i-1;

        while (compare >=0 && arr[compare] > key) {
            arr[compare+1] = arr[compare];
            compare--;
        }
        arr [compare+1] = key;
    }
}

void mergeSort(int* arr, int size) {
    if (size <= 1) return;

    int mid = size / 2;
    mergeSort(arr, mid);
    mergeSort(arr + mid, size - mid);

    int* temp = new int[size];

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
}

void shellSort(int* arr, int size){ 
    for (int gap = size/2; gap>0; gap /= 2){
        for (int i = gap; i < size; i++){
            int temp = arr[i];
            int j = i;

            while (j>=gap && arr[j-gap] > temp) {
                arr[j] = arr[j-gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

bool isNearlySorted(int* arr, int n) {
    int inv = 0;
    for (int i = 0; i < n - 1; i++)
        if (arr[i] > arr[i + 1])
            inv++;

    return inv < n * 0.02; // mniej niż 2% nieuporządkowanych par
}

void hybridSort(int* arr, int n) {
    int minVal = arr[0];
    int maxVal = arr[0];
    for (int i=0; i<n; i++){
        if (arr[i] <= minVal) minVal = arr[i];
        if (arr[i] >= maxVal) maxVal = arr[i];
    }

    int range = maxVal - minVal;

    // 1. xs arrays
    if (n <= 20) {
        cout << "insertion sort used\n";
        insertionSort(arr, n);
        return;
    }

    // 2. small arrays
    if (n <= 50) {
        cout << "shell sort used\n";
        shellSort(arr, n);
        return;
    }

    // 3. nearly sorted arrays
    if (isNearlySorted(arr, n)) {
        cout << "insertion sort used (nearly sorted data)\n";
        insertionSort(arr, n);
        return;
    }

    // 4. if range small, bucket sort - good for integers and reversed data
    if (range < 2000) {
        cout << "bucket sort used (small range in array: " << range << ")\n";
        bucketSort(arr, n);
        return;
    }

    // 5. large arrays - merge sort - stable and O(n log n)
    cout << "merge sort used (large array)\n";
    mergeSort(arr, n);
}

void printArray(int* arr, int size) {
    for (int i=0; i<size; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
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

int main() {
    int size = 0;
    srand(time(NULL));
    while (size <=0) {
        cout << "Enter array size (>0): ";
        cin >> size;
    }
    
    int* randomFilled = new int[size];

    fillRandom(randomFilled, size);

    cout << "\nBefore sorting [random filled array]:\n";
    printArray(randomFilled, size);

    hybridSort(randomFilled, size);

    //cout << "\nAfter sorting (hybrid algorithm):\n";
    //printArray(randomFilled, size);
    cout << "\n";

    int* reversedFilled = new int[size];

    fillReversed(reversedFilled, size);

    cout << "\nBefore sorting [reversed filled array]:\n";
    printArray(reversedFilled, size);

    hybridSort(reversedFilled, size);

    //cout << "\nAfter sorting (hybrid algorithm):\n";
    //printArray(reversedFilled, size);
    cout << "\n";

    int* nearlySortedFilled = new int[size];

    fillNearlySorted(nearlySortedFilled, size);

    cout << "\nBefore sorting [nearly sorted filled array]:\n";
    printArray(nearlySortedFilled, size);

    hybridSort(nearlySortedFilled, size);

    //cout << "\nAfter sorting (hybrid algorithm):\n";
    //printArray(nearlySortedFilled, size);
    cout << "\n";

    delete[] randomFilled;
    delete[] reversedFilled;
    delete[] nearlySortedFilled;

    return 0;
}