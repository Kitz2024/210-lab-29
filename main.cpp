// Kit Pollinger
// 210 - Lab - 29 | Pseudocode and Mockup

#include <iostream>
#include <map>
#include <array>
#include <list>
#include <string>
#include <fstream>
#include <ctime> //srand and time

using namespace std;

void TrafficData(std::map<std::string, std::array<std::list<std::string>, 3>>& trafficMap, const std::string & filename)
{
    // Open the file
    ifstream infile("trafficData.txt");

    // File checking
    if (!infile.is_open())
    {
        cout << "Error, Can't open file: ";
        return;
    }
    string lane, vehicleType;
    // Read the file line by line and parse lane name and vehicle type
    while (infile >> lane >> vehicleType)
    {
        // Set vehicle in appropriate list base on type
        if (vehicleType == "Car")
        {
            trafficMap[lane][0].push_back(vehicleType); // Add car to first list
        }
        else if (vehicleType == "Truck")
        {
            trafficMap[lane][1].push_back(vehicleType); // Add truck to  second list
        }
        else if (vehicleType == "Motorcycle")
        {
            trafficMap[lane][2].push_back(vehicleType); // Add Motorcycle to thirdlist
        }
    }

    infile.close(); // Close the file
}

void trafficSim(std::map<std::string, std::array<std::list<std::string>, 3>> &trafficMap, int intervals)
{
    // Random Number generator
    srand(static_cast<unsigned int>(time(0)));

    // simulation traffic
    for (int i = 0; i < intervals; i++)
    {
        // Display  current state of traffic map (number of vehicles in each lane)
        cout << "Interval " << i + 1 << ":" << endl;
        // For each lane in the map:
        for (auto &lane : trafficMap)
        {
            string laneName = lane.first;     // Lane name
            auto &vehicleLists = lane.second; // Array of lists (vehicle Types for first lane)
                                              // Check traffic light is green for this lane (simulate based on interval)
            bool lightGreen = (i % 2 == 0);
            cout << "Lane " << laneName << " traffic light is " << (lightGreen ? "GREEN" : "RED") << endl;

            // If green:
            if (lightGreen)
            {
                for (int j = 0; j < 3; ++j)
                {
                    if (!vehicleLists[j].empty())
                    {
                        // Move one vehicle from each list (car, truck, motorcycle) forward
                        cout << "Moving " << vehicleLists[j].front() << " forward in " << laneName << endl;
                        vehicleLists[j].pop_front(); // Remove first vehicle from list
                    }

                    // Update wait times for remaining vehicles in the list

                    // If breakdown, temporarily block lane and add a delay
                    // If spike, add additional vehicles to the lane

                    // Print changes for this interval, "Added 2 cars to Northbound lane"
                    // pause to simulate real-time passage of time between intervals
                }
            }
            // If red, do nothing for this lane
            else
            {
                cout << "Lane " << laneName << " is on RED; vehicles remain in place." << endl;
            }
            // Random Traffic Simulate spike / break down
            int event = rand() % 10; // Generate a random event between 0 and 9
            if (event < 2)
            { // 20% chance of
                cout << "Breakdown in " << laneName << "! Traffic delayed." << endl;
            }
            else if (event < 4)
            { // 20% chance of traffic spike
                // Randomly add a vehicle type during a traffic spike
                int vehicleType = rand() % 3; // Randomly pick Car (0), Truck (1), or Motorcycle (2)
                string vehicleName = (vehicleType == 0) ? "Car" : (vehicleType == 1) ? "Truck"
                                                                                     : "Motorcycle";
                vehicleLists[vehicleType].push_back(vehicleName); // Add the randomly chosen vehicle type to the lane
                cout << "Traffic spike! Added an extra " << vehicleName << " to " << laneName << endl;
            }
        }
    }
}

// Add vehicle to lane
void addVehicle(std::list<std::string>& vehicleList, const std::string & vehicleType)
{
    // Add vehicle type to speicfic list
}

// Remove Vehicle from lane
void removeVehicle(std::list<std::string> & vehicleList)
{
    // Remove  first vehicle from the specified list if not empty
}

/*
//Testing Simulation
void addVehicle(std::list<std::string>& vehicleList, const std::string& vehicleType) {
    //Add vehicle type to speicfic list
    vehicleList.push_back(vehicleType);
}

//Remove Vehicle from lane
void removeVehicle(std::list<std::string>& vehicleList) {
    // Remove  first vehicle from the specified list if not empty
    if (!vehicleList.empty()) {
        vehicleList.pop_front();
    }
}

//Lane Test Pass/Failed
void checkTestResult(const string& testName, bool condition) {
    if (condition) {
        cout << testName << " passed." << endl;
    } else {
        cout << testName << " failed." << endl;
    }
}
*/

// Main Function
int main()
{

    // Define Map (store Lane and Vehcile data)
    std::map<std::string, std::array<std::list<std::string>, 3>> trafficMap;

    // Read traffic map data from File
    TrafficData(trafficMap, "trafficData.txt"); // Add traffic Data txt file

    // run Traffic simulation for 25 intervals
    trafficSim(trafficMap, 25);

    // Output Final Traffic (total vehicles, average wait time)

    /*

        //Unit Testing

        std::list<std::string> testLane;
        // Test 1: Add a vehicle and verify
        addVehicle(testLane, "Car");
        checkTestResult("Test 1 - Add Vehicle (Car)", testLane.size() == 1 && testLane.front() == "Car");

        // Test 2: Add multiple vehicles and verify order
        addVehicle(testLane, "Truck");
        addVehicle(testLane, "Motorcycle");
        checkTestResult("Test 2 - Add Vehicles (Truck, Motorcycle)",
                        testLane.size() == 3 && testLane.back() == "Motorcycle");

        // Test 3: Remove vehicle and verify
        removeVehicle(testLane);
        checkTestResult("Test 3 - Remove Vehicle (should remove Car)",
                        testLane.size() == 2 && testLane.front() == "Truck");

        // Test 4: Remove remaining vehicles
        removeVehicle(testLane);
        removeVehicle(testLane);
        checkTestResult("Test 4 - Remove All Vehicles (should be empty)", testLane.empty());
    */
    return 0;
}