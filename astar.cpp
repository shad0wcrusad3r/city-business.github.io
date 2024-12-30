#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;

struct Node {
    int x, y;
    double gCost, hCost;
    Node* parent;

    double fCost() const { return gCost + hCost; }
};

// Comparison for priority queue (lowest fCost comes first)
struct CompareNode {
    bool operator()(const Node* a, const Node* b) {
        return a->fCost() > b->fCost();
    }
};

// Check if a given position is within the grid and not blocked
bool isValid(int x, int y, const vector<vector<int>>& grid) {
    return x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size() && grid[x][y] == 0;
}

// Calculate Manhattan distance as the heuristic
double heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

vector<pair<int, int>> AStar(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> target) {
    int rows = grid.size();
    int cols = grid[0].size();

    priority_queue<Node*, vector<Node*>, CompareNode> openList;
    map<pair<int, int>, Node*> allNodes;

    // Create the start node
    Node* startNode = new Node{start.first, start.second, 0, heuristic(start.first, start.second, target.first, target.second), nullptr};
    openList.push(startNode);
    allNodes[{start.first, start.second}] = startNode;

    vector<vector<bool>> closedList(rows, vector<bool>(cols, false));

    // Directions for moving up, down, left, and right
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        // Mark current node as visited
        closedList[current->x][current->y] = true;

        // Check if the target is reached
        if (current->x == target.first && current->y == target.second) {
            vector<pair<int, int>> path;
            while (current) {
                path.push_back({current->x, current->y});
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // Explore neighbors
        for (const auto& dir : directions) {
            int newX = current->x + dir.first;
            int newY = current->y + dir.second;

            if (isValid(newX, newY, grid) && !closedList[newX][newY]) {
                double newGCost = current->gCost + 1; // Cost to move to a neighbor is 1
                double newHCost = heuristic(newX, newY, target.first, target.second);

                if (allNodes.find({newX, newY}) == allNodes.end() || newGCost < allNodes[{newX, newY}]->gCost) {
                    Node* neighbor = new Node{newX, newY, newGCost, newHCost, current};
                    openList.push(neighbor);
                    allNodes[{newX, newY}] = neighbor;
                }
            }
        }
    }

    // If no path is found
    return {};
}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    pair<int, int> start = {0, 0};
    pair<int, int> target = {4, 4};

    vector<pair<int, int>> path = AStar(grid, start, target);

    if (!path.empty()) {
        cout << "Path found:\n";
        for (const auto& p : path) {
            cout << "(" << p.first << ", " << p.second << ")\n";
        }
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}
