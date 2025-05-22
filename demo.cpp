#include <iostream>
#include "route.h"
#include "navigation_app.cpp"
#include "car_route.cpp"
#include "walk_route.cpp"
#include "bike_route.cpp"

using namespace std;

int main() {
    cout << "      TRAVEL PLANNER    \n";

    cout << "Available locations:\n";
    cout << "  - home\n";
    cout << "  - university\n";
    cout << "  - mall\n";
    cout << "  - downtown\n";

    string from, to;
    cout << "\nEnter starting point: ";
    cin >> from;
    cout << "Enter destination: ";
    cin >> to;

    cout << "\n=== Finding routes from " << from << " to " << to << " ===\n\n";

    Route* car = new CarRoute();
    NavigationApp appCar(car);
    cout << "[CAR ROUTE]\n";
    appCar.planRoute(from, to); // polymorphism
    cout << "\n";

    Route* bike = new BikeRoute();
    NavigationApp appBike(bike);
    cout << "[BIKE ROUTE]\n";
    appBike.planRoute(from, to); // polymorphism
    cout << "\n";

    Route* walk = new WalkRoute();
    NavigationApp appWalk(walk);
    cout << "[WALK ROUTE]\n";
    appWalk.planRoute(from, to); // polymorphism
    cout << "\n";

    delete car;
    delete bike;
    delete walk;

    return 0;
}
