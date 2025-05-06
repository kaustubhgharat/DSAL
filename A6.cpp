#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Graph {
public:
    int numberOfNodes;
    int connectedComp;
    vector<vector<int>> adj;
    vector<int> deg;

    Graph(int n) {
        numberOfNodes = n;
        connectedComp = 0;
        adj.resize(n);
        deg.resize(n, 0);
    }
    

    void addEdge(int i, int j) {
        if (i >= numberOfNodes || j >= numberOfNodes || i < 0 || j < 0) {
            cout << "Invalid edge!" << endl;
            return;
        }
        adj[i].push_back(j);
        adj[j].push_back(i); // Undirected graph
        deg[i]++;
        deg[j]++;
    }

    void BFS(int start) {
        if (start < 0 || start >= numberOfNodes) {
            cout << "Invalid starting node!" << endl;
            return;
        }

        vector<bool> visited(numberOfNodes, false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        cout << "BFS Traversal: ";
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            cout << cur << " ";

            for (int x : adj[cur]) {
                if (!visited[x]) {
                    q.push(x);
                    visited[x] = true;
                }
            }
        }
        cout << endl;
    }

    void DFS(int start, vector<bool>& visited) {
        visited[start] = true;
        cout << start << " ";

        for (int a : adj[start]) {
            if (!visited[a]) {
                DFS(a, visited);
            }
        }
        
    }

    void dfs(int start) {
        if (start < 0 || start >= numberOfNodes) {
            cout << "Invalid starting node!" << endl;
            return;
        }

        vector<bool> visited(numberOfNodes, false);
        cout << "DFS Traversal: ";
        DFS(start, visited);
        cout << endl;
    }
        // stack<int> s;
        // s.push(start);

        // while (!s.empty()) {
        //     int node = s.top();
        //     s.pop();

        //     if (!visited[node]) {
        //         visited[node] = true;
        //         cout << node << " ";
        //     }

        //     for (int neighbor : adj[node]) {
        //         if (!visited[neighbor]) {
        //             s.push(neighbor);
        //         }
        //     }
        // }
    void countComponents() {
        vector<bool> visited(numberOfNodes, false);
        int count = 0;

        for (int i = 0; i < numberOfNodes; i++) {
            if (!visited[i]) {
                DFS(i, visited);
                count++;
            }
        }
        connectedComp = count;
        cout << "\nNumber of connected components: " << connectedComp << endl;
    }

    void displayDegree() {
        cout << "Node Degrees:" << endl;
        for (int i = 0; i < numberOfNodes; i++) {
            cout << "Node " << i << " has degree " << deg[i] << endl;
        }
    }
};

int main() {
    int n, choice, u, v, start;

    cout << "Enter the number of nodes in the graph: ";
    cin >> n;
    Graph g(n);

    while (true) {
        cout << "\nGraph Menu:\n";
        cout << "1. Add Edge\n";
        cout << "2. BFS Traversal\n";
        cout << "3. DFS Traversal\n";
        cout << "4. Count Connected Components\n";
        cout << "5. Display Node Degrees\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter nodes to connect (u v): ";
                cin >> u >> v;
                g.addEdge(u, v);
                break;
            case 2:
                cout << "Enter starting node for BFS: ";
                cin >> start;
                g.BFS(start);
                break;
            case 3:
                cout << "Enter starting node for DFS: ";
                cin >> start;
                g.dfs(start);
                break;
            case 4:
                g.countComponents();
                break;
            case 5:
                g.displayDegree();
                break;
            case 6:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
}
