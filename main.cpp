// Kit Pollinger
// 210 - Lab - 29 | Pseudocode and Mockup

#include <iostream>
#include <map>
#include <array>
#include <list>
#include <string>
#include <fstream>
#include <random>

using namespace std;

void TrafficData(std::map<std::string, std::array<std::list<std::string>, 3>>& trafficMap, const std::string& filename) {
    // Open the file
    // If file cannot be opened, output an error and exit function
    // For each line in the file:
        // Parse lane name, vehicle type, and other details
        // Insert vehicle into the appropriate list in the array for that lane
    // Close the file
}

void trafficSim(std::map<std::string, std::array<std::list<std::string>, 3>>& trafficMap, int intervals)
{

    // Loop through each time interval
    for (int i = 0; i < intervals; i++)
    {
// Display  current state of  traffic map (number of vehicles in each lane)
        
        // For each lane in the map:
            // Check traffic light is green for this lane (simulate based on interval)
            // If green:
                // Move one vehicle from each list (car, truck, motorcycle) forward
                // Update wait times for remaining vehicles in the list
            // If red, do nothing for this lane

            // Randomly decide if a vehicle breakdown or traffic spike occurs
                // If breakdown, temporarily block lane and add a delay
                // If spike, add additional vehicles to the lane
            
        // Print changes for this interval, "Added 2 cars to Northbound lane"
        // pause to simulate real-time passage of time between intervals
    }
}

/*
//Add vehicle to lane 
void addVehicle(std::list<std::string>& vehicleList, const std::string& vehicleType) {
    //Add vehicle type to speicfic list
}

//Remove Vehicle from lane
void removeVehicle(std::list<std::string>& vehicleList) {
    // Remove  first vehicle from the specified list if not empty
    }
}
*/

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

//Main Function
int main()
{
    //Define Map (store Lane and Vehcile data)
    /*std::map<std::string, std::array<std::list<std::string>, 3>> trafficMap;

    //Read traffic map data from File
    TrafficData (trafficMap, ""); //Add traffic Data txt file


    //run Traffic simulation for 25 intervals
    trafficSim(trafficMap, 25);*/

    //Output Final Traffic (total vehicles, average wait time)

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

    return 0;
}