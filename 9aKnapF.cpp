#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int weight;
    int value;
};

bool compare(const Item& a, const Item& b) {
    double ratioA = (double)a.value / a.weight;
    double ratioB = (double)b.value / b.weight;
    return ratioA > ratioB;
}

double fractionalKnapsack(Item items[], int n, int capacity) {
    sort(items, items + n, compare);
    double totalValue = 0.0;

    for (int i = 0; i < n; i++) {
        if (items[i].weight <= capacity) {
            totalValue += items[i].value;
            capacity -= items[i].weight;
        } else {
            totalValue += items[i].value * ((double)capacity / items[i].weight);
            break;
        }
    }

    return totalValue;
}

int main() {
    int n;
    cout << "Enter the number of items: ";
    cin >> n;

    Item items[n];

    for (int i = 0; i < n; i++) {
        cout << "Enter weight and value for item " << i + 1 << ": ";
        cin >> items[i].weight >> items[i].value;
    }

    int capacity;
    cout << "Enter the capacity of the knapsack: ";
    cin >> capacity;

    double maxValue = fractionalKnapsack(items, n, capacity);
    cout << "Maximum total value in the knapsack: " << maxValue << endl;

    return 0;
}
