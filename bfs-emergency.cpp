#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Function to perform BFS traversal of a graph
void bfs(int start, const vector<vector<int>>& adj) {
    int V = adj.size();  // Number of vertices
    vector<bool> visited(V, false);  // Array to keep track of visited vertices
    queue<int> q;  // Queue for BFS

    // Start BFS from the given starting node
    visited[start] = true;
    q.push(start);

    cout << "BFS Traversal starting from vertex " << start << ": ";

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";  // Visit the node (print it)

        // Explore all unvisited neighbors of the current node
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    cout << endl;
}

int main() {
    // Number of vertices
    int V = 6;
    vector<vector<int>> adj(V);

    // Example graph (adjacency list representation)
    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[1].push_back(0);
    adj[1].push_back(3);
    adj[2].push_back(0);
    adj[2].push_back(4);
    adj[3].push_back(1);
    adj[3].push_back(5);
    adj[4].push_back(2);
    adj[5].push_back(3);

    // Perform BFS starting from vertex 0
    bfs(0, adj);

    return 0;
}
