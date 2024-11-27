#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <utility>

using namespace std;

class HashTableChaining {
private:
    vector<list<pair<string, string> > > table;
    int hashFunction(const string& key) {
        return key.length() % table.size();
    }
public:
    HashTableChaining(int size) : table(size) {}

    void insert(const string& name, const string& phone) {
        int index = hashFunction(name);
        table[index].push_back(make_pair(name, phone));
    }

    bool search(const string& name, int& comparisons) {
        int index = hashFunction(name);
        comparisons = 0;
        for (list<pair<string, string> >::iterator it = table[index].begin(); it != table[index].end(); ++it) { // Explicit iterator used
            comparisons++;
            if (it->first == name) {
                return true;
            }
        }
        return false;
    }
};

class HashTableOpenAddressing {
private:
    vector<pair<string, string> > table;
    int size;
    int hashFunction(const string& key) {
        return key.length() % size;
    }
public:
    HashTableOpenAddressing(int size) : size(size) {
        table.resize(size, make_pair("", ""));
    }

    void insert(const string& name, const string& phone) {
        int index = hashFunction(name);
        while (table[index].first != "") {
            index = (index + 1) % size;
        }
        table[index] = make_pair(name, phone);
    }

    bool search(const string& name, int& comparisons) {
        int index = hashFunction(name);
        comparisons = 0;
        while (table[index].first != "") {
            comparisons++;
            if (table[index].first == name) {
                return true;
            }
            index = (index + 1) % size;
        }
        return false;
    }
};

int main() {
    int size;
    cout << "Enter the size of the hash table: ";
    cin >> size;

    HashTableChaining phoneBookChaining(size);
    HashTableOpenAddressing phoneBookOpenAddressing(size);

    int n;
    cout << "Enter the number of clients: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        string name, phone;
        cout << "Enter name of client " << i + 1 << ": ";
        cin >> name;
        cout << "Enter phone number of " << name << ": ";
        cin >> phone;

        phoneBookChaining.insert(name, phone);
        phoneBookOpenAddressing.insert(name, phone);
    }

    int searchCount;
    cout << "Enter the number of names you want to search for: ";
    cin >> searchCount;
    vector<string> searchNames(searchCount);
    for (int i = 0; i < searchCount; i++) {
        cout << "Enter name to search for: ";
        cin >> searchNames[i];
    }

    cout << "\nSearch results (Chaining):" << endl;
    for (int i = 0; i < searchNames.size(); i++) {
        int comparisons = 0;
        if (phoneBookChaining.search(searchNames[i], comparisons)) {
            cout << searchNames[i] << " found with " << comparisons << " comparisons." << endl;
        } else {
            cout << searchNames[i] << " not found after " << comparisons << " comparisons." << endl;
        }
    }

    cout << "\nSearch results (Open Addressing):" << endl;
    for (int i = 0; i < searchNames.size(); i++) {
        int comparisons = 0;
        if (phoneBookOpenAddressing.search(searchNames[i], comparisons)) {
            cout << searchNames[i] << " found with " << comparisons << " comparisons." << endl;
        } else {
            cout << searchNames[i] << " not found after " << comparisons << " comparisons." << endl;
        }
    }

    return 0;
}
