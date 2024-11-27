#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> pii;

vector<int> dijkstra(int source, int V, const vector<vector<pii> >& adj) {
    priority_queue<pii, vector<pii>, greater<pii> > pq;
    vector<int> dist(V, INT_MAX);

    dist[source] = 0;
    pq.push(make_pair(0, source));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].first;
            int weight = adj[u][i].second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    return dist;
}

int main() {
    int V, E;

    cout << "Enter the number of places (vertices): ";
    cin >> V;
    
    vector<vector<pii> > adj(V);

    cout << "Enter the number of roads (edges): ";
    cin >> E;

    cout << "Enter the roads (u, v, weight) where u and v are 0-based indices:" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v, weight;
        cout<<"Enter u: ";
        cin >> u;
        cout<<"Enter v: ";
        cin >> v;
        cout<<"Enter weight: ";
        cin >> weight;
        adj[u].push_back(pii(v, weight));
        adj[v].push_back(pii(u, weight));
    }

    int source, destination;
    cout << "Enter the source place (A): ";
    cin >> source;

    cout << "Enter the destination place (B): ";
    cin >> destination;

    vector<int> distances = dijkstra(source, V, adj);

    if (distances[destination] == INT_MAX) {
        cout << "There is no path from A to B." << endl;
    } else {
        cout << "Shortest path from A to B: " << distances[destination] << endl;
    }

    return 0;
}
