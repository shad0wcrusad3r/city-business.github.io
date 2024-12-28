#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// A structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// A structure to represent a subset for Union-Find
struct Subset {
    int parent;
    int rank;
};

// Function to find the parent of a node in the disjoint-set
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Function to perform Union of two subsets
void Union(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    // Union by rank
    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Comparison function to sort edges by their weight
bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Function to implement Kruskal's algorithm
void kruskal(int V, vector<Edge>& edges) {
    // Sort edges in non-decreasing order of their weight
    sort(edges.begin(), edges.end(), compare);

    Subset* subsets = new Subset[V];

    // Initially, each node is in its own subset
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    vector<Edge> result;  // To store the resulting MST

    int e = 0;  // Count of edges in MST
    int i = 0;  // Initial index of sorted edges
    while (e < V - 1) {
        Edge next_edge = edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge does not cause a cycle
        if (x != y) {
            result.push_back(next_edge);
            Union(subsets, x, y);
            e++;
        }
    }

    // Print the edges of the MST
    cout << "Edges in the MST:" << endl;
    for (auto& edge : result) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
    }

    delete[] subsets;
}

int main() {
    int V = 4;  // Number of vertices
    vector<Edge> edges;

    // Example edges (src, dest, weight)
    edges.push_back({0, 1, 10});
    edges.push_back({0, 2, 6});
    edges.push_back({0, 3, 5});
    edges.push_back({1, 3, 15});
    edges.push_back({2, 3, 4});

    kruskal(V, edges);

    return 0;
}
