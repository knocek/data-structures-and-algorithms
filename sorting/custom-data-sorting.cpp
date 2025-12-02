#include <iostream>
#include <string>
using namespace std;

struct Patient {
    string name;
    int age;
    string disease;
    int severity; // severity case 1 (low) to 10 (high)
    bool emergency; // true = prioritied case 
    int arrivalOrder; // order of arrival
};

void printPatients(Patient* arr, int n) {
    cout << "Patients queue:\n";
    for (int i = 0; i < n; i++) {
        cout << i+1 << ". "
             << arr[i].name
             << ", AGE: " << arr[i].age
             << ", DISEASE: " << arr[i].disease
             << ", SEVERITY: " << arr[i].severity
             << ", EMERGENCY CASE (ambulance, etc): " << (arr[i].emergency ? "yes" : "no")
             << ", ARRIVAL: " << arr[i].arrivalOrder
             << "\n";
    }
}

void triageSort(Patient* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            bool swapNeeded = false;

            // emergency cases first
            if (arr[j].emergency != arr[j + 1].emergency) {
                swapNeeded = arr[j + 1].emergency;
            }
            // then severity (higher first)
            else if (arr[j].severity != arr[j + 1].severity) {
                swapNeeded = arr[j].severity < arr[j + 1].severity;
            }
            // finally arrival order (earlier first)
            else {
                swapNeeded = arr[j].arrivalOrder > arr[j + 1].arrivalOrder;
            }

            if (swapNeeded) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    Patient patients[] = {
        {"Jan",   70, "infarct (zawal)", 9, true,  1},
        {"Anna",  25, "fever", 3, false, 2},
        {"Piotr", 60, "suspected stroke (podejrzenie udaru)", 8, true,  3},
        {"Ola",   40, "abdominal pain", 4, false, 4},
        {"Kuba",  80, "shortness of breath", 7, true,  5},
        {"Maja",  10, "rash", 2, false, 6},
        {"Stas", 15, "traffic accident, multiple injuries", 9, true, 7},
        {"Ewa",   50, "broken arm", 5, false, 8},
        {"Tomek", 30, "severe allergic reaction", 8, true, 9},
        {"Zofia", 65, "flu symptoms", 4, false, 10}
    };

    int n = sizeof(patients) / sizeof(patients[0]);

    cout << "before sorting:\n";
    printPatients(patients, n);

    // sorting by triage rules
    triageSort(patients, n);

    cout << "\nafter sorting (by triage):\n";
    printPatients(patients, n);

    return 0;
}