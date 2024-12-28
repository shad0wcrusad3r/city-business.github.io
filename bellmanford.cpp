#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Graph {
public:
    int V, E; // Number of vertices and edges
    vector<vector<int>> edges; // Edges as {u, v, weight}

    Graph(int V, int E) {
        this->V = V;
        this->E = E;
    }

    void addEdge(int u, int v, int weight) {
        edges.push_back({u, v, weight});
    }

    void bellmanFord(int src) {
        vector<int> dist(V, INT_MAX); // Distance array to store the shortest path from src
        dist[src] = 0;

        // Relax all edges V-1 times
        for (int i = 1; i <= V - 1; i++) {
            for (auto& edge : edges) {
                int u = edge[0], v = edge[1], weight = edge[2];
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }

        // Check for negative-weight cycles
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], weight = edge[2];
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                cout << "Graph contains negative weight cycle\n";
                return;
            }
        }

        // Print the shortest distances
        cout << "Vertex Distance from Source " << src << endl;
        for (int i = 0; i < V; i++) {
            cout << i << "\t" << dist[i] << endl;
        }
    }
};

int main() {
    Graph g(5, 8); // Create a graph with 5 vertices and 8 edges

    // Add edges (u, v, weight)
    g.addEdge(0, 1, -1);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(1, 4, 2);
    g.addEdge(3, 2, 5);
    g.addEdge(3, 1, 1);
    g.addEdge(4, 3, -3);

    g.bellmanFord(0); // Run Bellman-Ford from vertex 0

    return 0;
}
