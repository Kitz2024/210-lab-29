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
//Add vehicle to lane 
void addVehicle(std::list<std::string>& vehicleList, const std::string& vehicleType) {
    //Add vehicle type to speicfic list
}
//Remove Vehicle from lane
void removeVehicle(std::list<std::string>& vehicleList) {
    // Remove  first vehicle from the specified list if not empty
}

//Main Function
int main()
{
    //Define Map (store Lane and Vehcile data)
    std::map<std::string, std::array<std::list<std::string>, 3>> trafficMap;

    //Read traffic map data from File
    TrafficData (trafficMap, "");


    //run Traffic simulation for 50 intervals
    trafficSim(trafficMap, 50);

    //Output FInal Traffic (total vehicles, average wait time)
    return 0;
}