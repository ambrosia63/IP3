// TravelPlanner – strategy šablonas. Bazinė klasė Route apibrėžia maršruto pasirinkimo strategiją, 
// o konkretūs CarRoute, BikeRoute realizuoja specifinius keliavimo būdus. 
// Pastovi klasė NavigationApp deleguoja maršruto skaičiavimą pasirinktai strategijai.

// Sukurti 3 klasę: walk_route.cpp
// - galimi terrainiai: sidewalk, dirt road
// - greitis: 5 km/h
// parašyti findRoute ir displayRoute (galima remiantis kitomis 2 klasėmis) 

#include "route.h"
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

TestRoute::TestRoute(const set<string>& terrains) : allowedTerrains(terrains) {}

TestRoute::~TestRoute() {}

void TestRoute::findRoute(const string& from, const string& to, const vector<Segment>& segments) {
    map<string, double> distance;
    map<string, string> previous;
    queue<string> q;

    for (const auto& seg : segments) {
        if (allowedTerrains.count(seg.terrain)) {
            distance[seg.from] = 1e9;
            distance[seg.to] = 1e9;
        }
    }

    distance[from] = 0;
    q.push(from);

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        for (const auto& seg : segments) {
            if (seg.from == current && allowedTerrains.count(seg.terrain)) {
                if (distance[seg.to] > distance[current] + seg.distance) {
                    distance[seg.to] = distance[current] + seg.distance;
                    previous[seg.to] = current;
                    q.push(seg.to);
                }
            }
        }
    }

    if (!distance.count(to) || distance[to] == 1e9) return;

    vector<string> revPath;
    for (string at = to; at != from; at = previous[at]) {
        revPath.push_back(at);
    }
    revPath.push_back(from);
    reverse(revPath.begin(), revPath.end());

    path = revPath;
    totalDistance = distance[to];
}

void TestRoute::displayRoute() const {
    if (!path.empty()) {
        for (const auto& loc : path) cout << loc << " -> ";
        cout << "END\n";
        cout << "Total distance: " << totalDistance << " km\n\n";
    } else {
        cout << "No route found.\n\n";
    }
}

int main() {
    NavigationApp* app = new NavigationApp(nullptr);
    vector<Segment> allSegments = app->getAllSegments();
    delete app;

    TestRoute walk({ "sidewalk", "dirt road" });
    walk.findRoute("home", "mall", allSegments);
    assert(!walk.getPath().empty());
    assert(walk.getPath().front() == "home");
    assert(walk.getPath().back() == "mall");
    assert(walk.getDistance() > 0);

    TestRoute bike({ "bike lane", "sidewalk", "dirt road" });
    bike.findRoute("university", "mall", allSegments);
    assert(!bike.getPath().empty());
    assert(bike.getPath().front() == "university");
    assert(bike.getPath().back() == "mall");
    assert(bike.getDistance() > 0);

    TestRoute car({ "road", "highway" });
    car.findRoute("home", "mall", allSegments);
    assert(!car.getPath().empty());
    assert(car.getPath().front() == "home");
    assert(car.getPath().back() == "mall");
    assert(car.getDistance() > 0);

    cout << "All assertions passed.\n";
    return 0;
}
