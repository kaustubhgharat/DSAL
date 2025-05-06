#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// Structure to store an edge
struct Edge {
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

// Union-Find (Disjoint Set) data structure for Kruskal's algorithm
class UnionFind {
public:
    vector<int> parent, rank;

    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

// Prim's Algorithm for MST using adjacency matrix
void primsAlgorithm(int n, vector<vector<int>>& graph) {
    const int INF = 1000000;
    vector<int> key(n, INF);
    vector<bool> inMST(n, false);
    vector<int> parent(n, -1);

    key[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0});

    int mstCost = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;

        inMST[u] = true;
        mstCost += key[u];

        for (int v = 0; v < n; v++) {
            if (graph[u][v] != 0 && !inMST[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    cout << "Prim's Algorithm MST Cost: " << mstCost << endl;
    cout << "Edges in MST (Prim's):\n";
    for (int i = 1; i < n; i++) {
        cout << parent[i] << " - " << i << " : " << graph[i][parent[i]] << endl;
    }
}

// Kruskal's Algorithm for MST using edge list
void kruskalAlgorithm(int n, vector<Edge>& edges) {
    UnionFind uf(n);
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    int mstCost = 0;
    cout << "Kruskal's Algorithm MST Cost:\n";
    for (auto& edge : edges) {
        int u = edge.u, v = edge.v;
        if (uf.find(u) != uf.find(v)) {
            uf.unionSets(u, v);
            mstCost += edge.weight;
            cout << "(" << u << ", " << v << ") : " << edge.weight << endl;
        }
    }
    cout << "Total Cost: " << mstCost << endl;
}

// Main function
int main() {
    int n, m;
    cout << "Enter the number of cities (nodes): ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n, 0));
    vector<Edge> edges;

    cout << "Enter the number of connections (edges): ";
    cin >> m;

    cout << "Enter the connections in the form of (u, v, cost):\n";
    for (int i = 0; i < m; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        graph[u][v] = cost;
        graph[v][u] = cost;
        edges.push_back(Edge(u, v, cost));
    }

    primsAlgorithm(n, graph);
    kruskalAlgorithm(n, edges);

    return 0;
}
