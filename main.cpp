// Kit Pollinger
// 210 - Lab - 29 | Pseudocode and Mockup

#include <iostream>
#include <map>
#include <array>
#include <list>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

//structure to store vehicle info with wait time
struct VehicleInfo {
    string type;
    int waitTime; // Number of intervals the vehicle has been in the lane
};

// Function prototypes
void TrafficData(std::map<std::string, std::array<std::list<VehicleInfo>, 3>>& trafficMap, const std::string& filename);
void trafficSim(std::map<std::string, std::array<std::list<VehicleInfo>, 3>>& trafficMap, int intervals);
void addVehicle(std::list<VehicleInfo>& vehicleList, const std::string& vehicleType);
void removeVehicle(std::list<VehicleInfo>& vehicleList);
void printFinalTraffic(const std::map<std::string, std::array<std::list<VehicleInfo>, 3>>& trafficMap);

int main()
{
    // Define Map (store Lane and Vehicle data)
    std::map<std::string, std::array<std::list<VehicleInfo>, 3>> trafficMap;

    // Read traffic map data from file
    TrafficData(trafficMap, "C:/210-Coding/projects/210-lab-29/trafficData.txt");

    // Run Traffic simulation for 25 intervals
    trafficSim(trafficMap, 25);

    // Output final traffic (total vehicles, average wait time) 
    printFinalTraffic(trafficMap);
    return 0;
}

void TrafficData(std::map<std::string, std::array<std::list<VehicleInfo>, 3>>& trafficMap, const std::string& filename) {
    // Open the file
    ifstream infile("C:/210-Coding/projects/210-lab-29/trafficData.txt");
    if (!infile.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    string lane;
    string vehicleType;
    while (infile >> lane >> vehicleType) {
        // Based on the vehicle type, find the correct index in the array
        int vehicleIndex = (vehicleType == "Car") ? 0 :
                           (vehicleType == "Truck") ? 1 : 2;

        // Add vehicle to appropriate list in the map with initial wait time as 0
        trafficMap[lane][vehicleIndex].push_back({vehicleType, 0});
    }
    
    //Closing file
    infile.close();
}

void trafficSim(std::map<std::string, std::array<std::list<VehicleInfo>, 3>>& trafficMap, int intervals)
{
    srand(static_cast<unsigned int>(time(0)));

    // Loop each time interval
    for (int i = 0; i < intervals; i++)
    {
        cout << "Interval " << i + 1 << ":" << endl;

        // For each lane, process the vehicles
        for (auto& lane : trafficMap)
        {
            string laneName = lane.first;
            auto& vehicleLists = lane.second;

            // Simulate green/red light (alternates every 2 intervals)
            bool lightGreen = (i % 2 == 0); // Green light for even intervals, red for odd

            // Print current state of the traffic map
            cout << laneName << " - Cars: " << vehicleLists[0].size()
                 << ", Trucks: " << vehicleLists[1].size()
                 << ", Motorcycles: " << vehicleLists[2].size() << endl;

            if (lightGreen)
            {
                // Green light: Move vehicles forward
                if (!vehicleLists[0].empty()) {
                    removeVehicle(vehicleLists[0]);
                    cout << "  Moved 1 Car forward." << endl;
                }
                if (!vehicleLists[1].empty()) {
                    removeVehicle(vehicleLists[1]);
                    cout << "  Moved 1 Truck forward." << endl;
                }
                if (!vehicleLists[2].empty()) {
                    removeVehicle(vehicleLists[2]);
                    cout << "  Moved 1 Motorcycle forward." << endl;
                }
            }
            else {
                cout << "  Red light - no vehicles moved." << endl;
            }

            // Simulate breakdown every 5 intervals (manual event simulation)
            if (i % 5 == 0) {
                cout << "  Breakdown! Blocking lane for this interval." << endl;
            }

            // Simulate traffic spike every 3 intervals (manual event simulation)
            if (i % 3 == 0) {
                int randomChoice = rand() % 3; // Random number between 0 and 2
                if (randomChoice == 0) {
                    addVehicle(vehicleLists[0], "Car");
                    cout << "  Traffic spike: Added 1 Car." << endl;
                } else if (randomChoice == 1) {
                    addVehicle(vehicleLists[1], "Truck");
                    cout << "  Traffic spike: Added 1 Truck." << endl;
                } else {
                    addVehicle(vehicleLists[2], "Motorcycle");
                    cout << "  Traffic spike: Added 1 Motorcycle." << endl;
                }
            }

            // Update wait time for vehicles in the lane
            for (auto& vehicle : vehicleLists[0]) {
                vehicle.waitTime++;
            }
            for (auto& vehicle : vehicleLists[1]) {
                vehicle.waitTime++;
            }
            for (auto& vehicle : vehicleLists[2]) {
                vehicle.waitTime++;
            }
        }

        // Print a blank line after each interval
        cout << endl;
    }
}

void addVehicle(std::list<VehicleInfo>& vehicleList, const std::string& vehicleType) {
    vehicleList.push_back({vehicleType, 0}); // New vehicle with wait time 0
}

void removeVehicle(std::list<VehicleInfo>& vehicleList) {
    if (!vehicleList.empty()) {
        vehicleList.pop_front(); // Remove the first vehicle from  list
    }
}

void printFinalTraffic(const std::map<std::string, std::array<std::list<VehicleInfo>, 3>>& trafficMap)
{
    int totalVehicles = 0;
    int totalWaitTime = 0;
    int numVehicles = 0;  // calculate the average wait time

    // Calculate the total number of vehicles and total wait time
    for (const auto& lane : trafficMap)
    {
        for (int i = 0; i < 3; i++) {
            for (const auto& vehicle : lane.second[i]) {
                totalVehicles++;  // total vehicle count
                totalWaitTime += vehicle.waitTime;  // Add  wait time of each vehicle
                numVehicles++;  //counter for the number of vehicles
            }
        }
    }

    // average wait time
    double averageWaitTime = (numVehicles > 0) ? static_cast<double>(totalWaitTime) / numVehicles : 0.0;

    // Output final traffic data
    cout << "Final Traffic Report:" << endl;
    cout << "Total vehicles: " << totalVehicles << endl;
    cout << "Average wait time: " << averageWaitTime << " intervals" << endl;
}
