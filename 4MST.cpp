#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge {
public:
    int u, v, weight;
    Edge(int uc, int vc, int weightc) {
        u = uc;
        v = vc;
        weight = weightc;
    }
};

class DSU {
public:
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void union_sets(int u, int v) {
        u = find(u);
        v = find(v);
        if (u != v) {
            if (rank[u] < rank[v]) {
                parent[u] = v;
            } else if (rank[u] > rank[v]) {
                parent[v] = u;
            } else {
                parent[v] = u;
                rank[u]++;
            }
        }
    }
};

bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

int main() {
    int n;
    int m;
    int u;
    int v;
    int weight;
    cout << "Enter number of nodes: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> m; 

    vector<Edge> edges;
    cout << "Enter the edges (u v weight) one by one:\n";
    for (int i = 0; i < m; i++) {
        u=0;
        v=0;
        weight=0;
        cout<<"Enter u for "<< i <<": ";
        cin >> u;
        cout<<"Enter v for "<< i <<": ";
        cin >> v;
        cout<<"Enter weight for "<< i <<": ";
        cin>> weight;
        edges.push_back(Edge(u, v, weight));
    }

    sort(edges.begin(), edges.end(), compareEdges);

    DSU dsu(n);
    vector<Edge> mst;
    int mstWeight = 0;

    for (Edge e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            dsu.union_sets(e.u, e.v);
            mst.push_back(e);
            mstWeight += e.weight;
        }
    }

    cout << "Total weight of the Minimum Spanning Tree: " << mstWeight << endl;

    cout << "Edges in the MST:\n";
    for (Edge e : mst) {
        cout << e.u << " - " << e.v << " : " << e.weight << endl;
    }

    return 0;
}
