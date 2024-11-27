#include <iostream>

using namespace std;

void merge(int credits[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = credits[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = credits[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            credits[k] = L[i];
            i++;
        } else {
            credits[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        credits[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        credits[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int credits[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(credits, left, mid);
        mergeSort(credits, mid + 1, right);
        merge(credits, left, mid, right);
    }
}

int main() {
    int n;

    cout << "Enter the number of students: ";
    cin >> n;

    int* credits = new int[n];

    cout << "Enter the credits obtained by each student in club activities:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Credits for student " << i + 1 << ": ";
        cin >> credits[i];
    }

    cout << "\nCredits before sorting:" << endl;
    for (int i = 0; i < n; i++) {
        cout << credits[i] << " ";
    }
    cout << endl;

    mergeSort(credits, 0, n - 1);

    cout << "\nCredits after sorting:" << endl;
    for (int i = 0; i < n; i++) {
        cout << credits[i] << " ";
    }
    cout << endl;

    delete[] credits;

    return 0;
}
