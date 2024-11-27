#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <string>
using namespace std;

class Graph {
    unordered_map<string, list<pair<string, int>>> adjList;

public:
    void addFlight(string cityA, string cityB, int cost) {
        adjList[cityA].push_back(make_pair(cityB, cost));
        adjList[cityB].push_back(make_pair(cityA, cost));
    }

    void DFS(string city, unordered_map<string, bool>& visited) {
        visited[city] = true;
        
        for (auto& neighbor : adjList[city]) {
            string nextCity = neighbor.first;
            if (!visited[nextCity]) {
                DFS(nextCity, visited);
            }
        }
    }

    bool isConnected() {
        unordered_map<string, bool> visited;
        
        for (auto& pair : adjList) {
            visited[pair.first] = false;
        }

        string startCity = adjList.begin()->first;
        DFS(startCity, visited);

        for (auto& pair : visited) {
            if (!pair.second) {
                return false;
            }
        }
        return true;
    }

    void displayAdjList() {
        for (auto& pair : adjList) {
            string city = pair.first;
            cout << city << " -> ";
            for (auto& neighbor : pair.second) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g;
    int numFlights;

    cout << "Enter the number of flights: ";
    cin >> numFlights;

    for (int i = 0; i < numFlights; i++) {
        string cityA, cityB;
        int cost;
        cout << "Enter the source city: ";
        cin >> cityA;
        cout << "Enter the destination city: ";
        cin >> cityB;
        cout << "Enter the flight cost (time/fuel): ";
        cin >> cost;
        g.addFlight(cityA, cityB, cost);
    }

    g.displayAdjList();

    if (g.isConnected()) {
        cout << "The graph is connected. All cities are reachable from any other city." << endl;
    } else {
        cout << "The graph is not connected. There are cities that cannot be reached." << endl;
    }

    return 0;
}
