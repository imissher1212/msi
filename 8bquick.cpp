#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int credits;
};

int partition(Student arr[], int low, int high) {
    int pivot = arr[high].credits;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].credits >= pivot) {
            i++;
            Student temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    Student temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return (i + 1);
}

void quickSort(Student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void displayTopStudents(Student arr[], int size) {
    cout << "Top 3: " << endl;

    if (size > 3) {
        for (int i = 0; i < 3; i++) {
            cout << arr[i].name << " " << arr[i].credits << endl;
        }
    } else {
        for (int i = 0; i < size; i++) {
            cout << arr[i].name << " " << arr[i].credits << endl;
        }
    }
}

int main() {
    int noOfStud;
    cout << "Enter the number of students: ";
    cin >> noOfStud;

    Student students[noOfStud];
    string stdName;
    int stdCredits;

    for (int i = 0; i < noOfStud; i++) {
        cin.ignore();
        cout << "Enter the name of student no. " << i + 1 << ": ";
        getline(cin, stdName);
        cout << "Enter the credits for " << stdName << ": ";
        cin >> stdCredits;

        students[i].name = stdName;
        students[i].credits = stdCredits;
    }

    quickSort(students, 0, noOfStud - 1);

    displayTopStudents(students, noOfStud);

    return 0;
}
