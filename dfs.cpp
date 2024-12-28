#include <iostream>
#include <vector>
using namespace std;

class Graph {
public:
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // For undirected graph
    }

    void DFS(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        // Recur for all the vertices adjacent to this vertex
        for (int i : adj[v]) {
            if (!visited[i]) {
                DFS(i, visited);
            }
        }
    }

    void DFSTraversal(int start) {
        vector<bool> visited(V, false);
        DFS(start, visited);
    }
};

int main() {
    Graph g(5); // Create a graph with 5 vertices

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);

    cout << "DFS starting from vertex 0: ";
    g.DFSTraversal(0); // Perform DFS traversal starting from vertex 0
    cout << endl;

    return 0;
}
