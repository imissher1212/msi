#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Job {
    char id;
    int deadline;
    int profit;
};

bool compare(Job a, Job b) {
    return a.profit > b.profit;
}

void jobScheduling(Job jobs[], int n) {
    sort(jobs, jobs + n, compare);
    bool slot[n];
    char result[n];

    for (int i = 0; i < n; i++) {
        for (int j = min(n, jobs[i].deadline) - 1; j >= 0; j--) {
            if (!slot[j]) {
                slot[j] = true;
                result[j] = jobs[i].id;
                break;
            }
        }
    }

    cout << "Selected jobs: ";
    for (int i = 0; i < n; i++) {
        if (slot[i]) {
            cout << result[i] << " ";
        }
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the number of jobs: ";
    cin >> n;

    Job jobs[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter job ID (single character) " << (i + 1) << ": ";
        cin >> jobs[i].id;
        cout << "Enter deadline for job " << (i + 1) << ": ";
        cin >> jobs[i].deadline;
        cout << "Enter profit for job " << (i + 1) << ": ";
        cin >> jobs[i].profit;
    }

    jobScheduling(jobs, n);

    return 0;
}
