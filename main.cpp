// Kit Pollinger
// 210 - Lab - 29 | Pseudocode and Mockup
#include <iostream>
#include <map>
#include <array>
#include <list>
#include <string>
#include <fstream>

using namespace std;
   
//structure to store vehicle info with wait time
struct VehicleInfo {
    string type;
    int waitTime; // Number of intervals the vehicle has been in the lane
};

void TrafficData(std::map<std::string, std::array<std::list<std::string>, 3>>& trafficMap, const std::string& filename) {
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
        int vehicleIndex = (vehicleType == "Car") ? 0 : (vehicleType == "Truck") ? 1 : 2;

        // Add vehicle to appropriate list
        trafficMap[lane][vehicleIndex].push_back(vehicleType);
    }

    infile.close();
}

void addVehicle(std::list<std::string>& vehicleList, const std::string& vehicleType) {
    vehicleList.push_back(vehicleType);
}

void removeVehicle(std::list<std::string>& vehicleList) {
    if (!vehicleList.empty()) {
        vehicleList.pop_front(); // Remove the first vehicle from the list
    }
}


void trafficSim(std::map<std::string, std::array<std::list<std::string>, 3>>& trafficMap, int intervals)
{
    // Counter for manual random event simulation
    int eventCounter = 0;

    // Loop through each time interval
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
                int vehicleType = eventCounter % 3; // Alternate between vehicle types
                if (vehicleType == 0) {
                    addVehicle(vehicleLists[0], "Car");
                    cout << "  Traffic spike: Added 1 Car." << endl;
                } else if (vehicleType == 1) {
                    addVehicle(vehicleLists[1], "Truck");
                    cout << "  Traffic spike: Added 1 Truck." << endl;
                } else {
                    addVehicle(vehicleLists[2], "Motorcycle");
                    cout << "  Traffic spike: Added 1 Motorcycle." << endl;
                }
                eventCounter++; // Increment event counter for next simulation
            }
        }

        // Print a blank line after each interval
        cout << endl;
    }
}
int main()
{
    // Define Map (store Lane and Vehicle data)
    std::map<std::string, std::array<std::list<std::string>, 3>> trafficMap;

    // Read traffic map data from File
    TrafficData(trafficMap, "C:/210-Coding/projects/210-lab-29/trafficData.txt"); // Ensure you have this file

    // Run Traffic simulation for 25 intervals
    trafficSim(trafficMap, 25);
    
    return 0;
}
