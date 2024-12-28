#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Graph {
public:
    int V; // Number of vertices
    vector<vector<int>> adjMatrix; // Adjacency matrix

    Graph(int V) {
        this->V = V;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight; // For undirected graph
    }

    void primMST() {
        vector<int> parent(V, -1); // Array to store MST
        vector<int> key(V, INT_MAX); // Key values used to pick minimum weight edge
        vector<bool> mstSet(V, false); // To represent the set of vertices included in MST
        key[0] = 0;

        for (int count = 0; count < V - 1; count++) {
            // Find the vertex with the minimum key value
            int u = -1;
            for (int v = 0; v < V; v++) {
                if (!mstSet[v] && (u == -1 || key[v] < key[u])) {
                    u = v;
                }
            }

            mstSet[u] = true; // Include vertex in MST

            // Update the key values of the adjacent vertices
            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] && !mstSet[v] && adjMatrix[u][v] < key[v]) {
                    key[v] = adjMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        // Print the constructed MST
        cout << "Edge \tWeight" << endl;
        for (int i = 1; i < V; i++) {
            cout << parent[i] << " - " << i << "\t" << adjMatrix[i][parent[i]] << endl;
        }
    }
};

int main() {
    Graph g(5); // Create a graph with 5 vertices

    // Add edges (u, v, weight)
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    cout << "Minimum Spanning Tree (MST) using Prim's Algorithm:" << endl;
    g.primMST();

    return 0;
}
