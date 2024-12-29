#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <set>

using namespace std; //DYNAMIC PROGRAMMING + PRUNING

void floyd(vector<vector<int>>& graph, int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (graph[i][k] != INT_MAX && graph[k][j] != INT_MAX &&
                    graph[i][j] > graph[i][k] + graph[k][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}

void all_pair_shortest_paths(const vector<vector<int>>& graph, int n) {
    cout << "All-pairs shortest paths:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == INT_MAX) {
                cout << "INF ";
            } else {
                if(graph[i][j]<10){
                    cout << graph[i][j] << "  ";
                }
                else{
                    cout << graph[i][j] << " ";
                }
            }
        }
        cout << endl;
    }
}

void home_to_stations(const vector<vector<int>>& graph, const set<int>& homes, const set<int>& stations) {
    for (int home : homes) {
        int minDistance = INT_MAX;
        int nearestStation = -1;

        for (int station : stations) {
            if (graph[home][station] < minDistance) {
                minDistance = graph[home][station];
                nearestStation = station;
            }
        }

        if (nearestStation == -1) {
            cout << "No accessible station for home " << home << ".\n";
        } else {
            cout << "Shortest path from home " << home << " to nearest station " << nearestStation
                 << " is: " << minDistance << "\n";
        }
    }
}

int main() {
    ifstream inputFile("graph_input.txt");

    if (!inputFile) {
        std::cerr << "File opening error\n";
        return 1;
    }

    int n, e, numHomes, numStations;
    inputFile >> n >> e;

    vector<vector<int>> graph(n, vector<int>(n, INT_MAX));

    for (int i = 0; i < n; ++i) {
        graph[i][i] = 0;
    }

    int u, v, w;
    for (int i = 0; i < e; ++i) {
        inputFile >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w;
    }

    set<int> homes, stations;
    inputFile >> numHomes;
    for (int i = 0; i < numHomes; ++i) {
        int home;
        inputFile >> home;
        if (stations.count(home)) {
            std::cerr << "Error: Node " << home << " cannot be both a home and a station.\n";
            return 1;
        }
        homes.insert(home);
    }

    inputFile >> numStations;
    for (int i = 0; i < numStations; ++i) {
        int station;
        inputFile >> station;
        if (homes.count(station)) {
            std::cerr << "Error: Node " << station << " cannot be both a home and a station.\n";
            return 1;
        }
        stations.insert(station);
    }

    inputFile.close();

    floyd(graph, n);

    all_pair_shortest_paths(graph, n);

    home_to_stations(graph, homes, stations);

    return 0;
}
