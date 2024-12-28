#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Define a pair for the priority queue (distance, vertex)
typedef pair<int, int> iPair;

// Function to perform Dijkstra's Algorithm
void dijkstra(const vector<vector<iPair>>& graph, int source) {
    int V = graph.size();  // Number of vertices
    vector<int> dist(V, INT_MAX);  // Distance array, initialized to infinity
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;  // Min-heap priority queue

    dist[source] = 0;  // Distance to the source is 0
    pq.push({0, source});  // Push source to the priority queue

    while (!pq.empty()) {
        int u = pq.top().second;  // Vertex with the smallest distance
        pq.pop();

        // Traverse adjacent vertices of u
        for (const auto& edge : graph[u]) {
            int v = edge.first;  // Neighboring vertex
            int weight = edge.second;  // Edge weight

            // If a shorter path to v is found
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Print the shortest distances from the source
    cout << "Vertex\tDistance from Source" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << "\t" << dist[i] << endl;
    }
}

int main() {
    int V = 4;  // Number of vertices
    vector<vector<iPair>> graph(V);

    // Add edges to the graph (example graph)
    graph[0].push_back({1, 4});
    graph[0].push_back({2, 2});
    graph[1].push_back({3, 6});
    graph[2].push_back({3, 3});

    // Call Dijkstra's algorithm with source vertex 0
    dijkstra(graph, 0);

    return 0;
}
