#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>

using namespace std;

// Define a struct for storing charging station data
struct ChargingStation {
    int id;
    int freeTime;  // Time when the station is set free (in minutes)
    bool hasCoffee;  // Coffee availability (true or false)

    // Constructor to initialize the station data
    ChargingStation(int id, int freeTime, bool hasCoffee)
        : id(id), freeTime(freeTime), hasCoffee(hasCoffee) {}
};

// Merge Sort helper functions for Divide and Conquer (works with lists)
void merge(list<ChargingStation>& stations, list<ChargingStation>& left, list<ChargingStation>& right) {
    list<ChargingStation> result;

    // Merge two sorted lists
    auto itLeft = left.begin(), itRight = right.begin();
    while (itLeft != left.end() && itRight != right.end()) {
        if (itLeft->freeTime <= itRight->freeTime) {
            result.push_back(*itLeft++);
        } else {
            result.push_back(*itRight++);
        }
    }

    // Add remaining elements
    while (itLeft != left.end()) result.push_back(*itLeft++);
    while (itRight != right.end()) result.push_back(*itRight++);

    // Transfer the merged result back to the original stations list
    stations = move(result);
}

void mergeSort(list<ChargingStation>& stations) {
    if (stations.size() <= 1)
        return;

    // Divide the list into two halves
    list<ChargingStation> left, right;
    auto it = stations.begin();
    advance(it, stations.size() / 2);
    left.splice(left.begin(), stations, stations.begin(), it);
    right.splice(right.begin(), stations, it, stations.end());

    // Recursively sort each half
    mergeSort(left);
    mergeSort(right);

    // Merge the sorted halves
    merge(stations, left, right);
}

// Pruning function to discard stations based on coffee availability
void pruneUnavailableStations(list<ChargingStation>& stations) {
    for (auto it = stations.begin(); it != stations.end(); ) {
        if (!it->hasCoffee) {  // Check if coffee is unavailable
            it = stations.erase(it);  // Remove the station and move the iterator forward
        } else {
            ++it;  // Move to the next station if coffee is available
        }
    }
}

// Function to read charging station data from a text file
list<ChargingStation> readChargingStations(const string& filename) {
    list<ChargingStation> stations;
    ifstream file(filename);
    int id, freeTime;
    bool hasCoffee;

    while (file >> id >> freeTime >> hasCoffee) {
        ChargingStation station(id, freeTime, hasCoffee);
        stations.push_back(station);
    }

    file.close();
    return stations;
}

int main() {
    // Read the charging stations from the file
    list<ChargingStation> stations = readChargingStations("charging_stations.txt");

    // Prune stations that do not have coffee available
    pruneUnavailableStations(stations);

    // Sort the stations by their free time using Merge Sort (Divide and Conquer)
    mergeSort(stations);

    // Display sorted stations by free time
    cout << "Charging stations sorted by free time:\n";
    for (const auto& station : stations) {
        cout << "ID: " << station.id << ", Free Time: " << station.freeTime << " minutes, Coffee: "
             << (station.hasCoffee ? "Available" : "Unavailable") << "\n";
    }

    return 0;
}
