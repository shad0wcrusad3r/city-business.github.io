#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <fstream>
#include <algorithm>
#include <sstream>  // For stringstream

#include <string>
#include <utility> 

using namespace std;

class Graph {
private:
    vector<vector<pair<int, int>>> adjList;

public:
    Graph(int nodes) {
        adjList.resize(nodes);
    }

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back(make_pair(v, weight));
        adjList[v].push_back(make_pair(u, weight)); // Assuming an undirected graph
    }

    vector<vector<pair<int, int>>>& getGraph() {
        return adjList;
    }
};

void dijkstra(int source, int destination, const vector<vector<pair<int, int>>>& graph) {
    cout<<"Analyzing the graph using Dijkstra's algorithm...\n";
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[source] = 0;
    pq.push(make_pair(0, source));

    while (!pq.empty()) {
        int current_dist = pq.top().first;
        int current_node = pq.top().second;
        pq.pop();

        if (current_dist > dist[current_node]) continue;

        for (int i = 0; i < graph[current_node].size(); i++) {
            int neighbor = graph[current_node][i].first;
            int weight = graph[current_node][i].second;

            int new_dist = current_dist + weight;
            if (new_dist < dist[neighbor]) {
                dist[neighbor] = new_dist;
                parent[neighbor] = current_node;
                pq.push(make_pair(new_dist, neighbor));
            }
        }
    }

    if (dist[destination] == INT_MAX) {
        cout << "No path exists between the source and destination.\n";
        return;
    }

    cout << "Optimal Route: ";
    vector<int> path;
    for (int node = destination; node != -1; node = parent[node]) {
        path.push_back(node);
    }
    reverse(path.begin(), path.end());

    for (size_t i = 0; i < path.size(); i++) {
        if (i > 0) cout << " -> ";
        cout << path[i];
    }
    cout << "\nTotal Cost: " << dist[destination] << endl;
}

// Heap Sort Class
class HeapSort {
public:
    static void heapify(vector<pair<string, int>>& arr, int n, int i) {
        int largest = i; // Change to 'largest' for max heap
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left].second > arr[largest].second)
            largest = left;

        if (right < n && arr[right].second > arr[largest].second)
            largest = right;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    static void sort(vector<pair<string, int>>& arr) {
        int n = arr.size();

        // Build the max heap
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }

        // Extract elements from heap
        for (int i = n - 1; i >= 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
};

// New function to sort services in descending order
void sortServicesDescending(vector<pair<string, int>>& services) {
    HeapSort::sort(services); // Sorts services using max heap
    reverse(services.begin(), services.end()); // Reverses to maintain descending order
}

void readServiceData(const string& file_name, vector<pair<string, int>>& services) {
    ifstream file(file_name);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file.\n";
        exit(1);
    }

    string line;
    vector<string> serviceNames;
    vector<int> serviceCosts;

    // Read all service names and their corresponding costs
    while (getline(file, line)) {
        if (line.empty()) break;  // Stop reading if there's an empty line

        // Split the line into service name and cost
        stringstream ss(line);
        string service;
        int cost;

        // Assuming each line has service and cost in this format: ServiceName Cost
        ss >> service >> cost;

        if (ss.fail()) {
            cerr << "Error reading line: " << line << endl;
            continue;  // Skip invalid lines
        }

        services.push_back(make_pair(service, cost));
    }

    file.close();

    if (services.empty()) {
        cout << "No services were read from the file.\n";
    }
}

void displaySortedServices(const vector<pair<string, int>>& services) {
    cout << "Services sorted by cost :\n";
    for (const auto& service : services) {
        cout << service.first << " - " << service.second << endl;
    }
}

void parseInput(const string& file_name, Graph& graph, int& source, int& destination) {
    ifstream file(file_name);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file.\n";
        exit(1);
    }

    int nodes, edges;
    file >> nodes >> edges;
    file >> source >> destination;

    graph = Graph(nodes);

    for (int i = 0; i < edges; ++i) {
        int u, v, w;
        file >> u >> v >> w;
        graph.addEdge(u, v, w);
    }

    file.close();
}

int main() {
    string service_file = "service.txt";
    vector<pair<string, int>> services;

    cout << "Reading service data...\n";
    readServiceData(service_file, services);

    if (services.empty()) {
        cout << "No services found in the file.\n";
    } else {
        sortServicesDescending(services);  // Sort and reverse services
        displaySortedServices(services);  // Display sorted services
    }

    string file_name = "path.txt";  
    Graph graph(0);  // Create an empty graph (size will be updated after parsing input)
    int source, destination;

    parseInput(file_name, graph, source, destination);

    vector<vector<pair<int, int>>>& adjList = graph.getGraph();
    dijkstra(source, destination, adjList);

    return 0;
}
