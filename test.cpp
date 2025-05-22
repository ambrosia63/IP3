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

class TestRoute : public Route {
protected:
    set<string> allowedTerrains;

public:
    TestRoute(const set<string>& terrains) : allowedTerrains(terrains) {}

    void findRoute(const string& from, const string& to, const vector<Segment>& segments) override {
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
};

class NavigationApp {
    Route* strategy;
public:
    NavigationApp(Route* strategy) : strategy(strategy) {}

    void planRoute(const string& from, const string& to) {
        vector<Segment> segments = getAllSegments();
        strategy->findRoute(from, to, segments);
        strategy->displayRoute();
    }

    vector<Segment> getAllSegments() {
        return {
            {"home", "park", "sidewalk", 1.2},
            {"park", "betche", "dirt road", 2.8},
            {"betche", "mall", "sidewalk", 2.0},
            {"home", "plaza", "road", 4.0},
            {"plaza", "station", "highway", 5.5},
            {"station", "mall", "road", 3.5},
            {"university", "lane", "bike lane", 3.2},
            {"lane", "mall", "sidewalk", 2.7},
            {"downtown", "creek", "dirt road", 2.3},
            {"creek", "university", "sidewalk", 3.7},
            {"mall", "bypass", "road", 3.8},
            {"bypass", "downtown", "road", 4.2},
            {"home", "university", "sidewalk", 7.0},
            {"home", "downtown", "road", 8.0},
            {"university", "plaza", "bike lane", 3.0},
            {"downtown", "betche", "dirt road", 5.2},
            {"mall", "home", "road", 6.5},
            {"park", "lane", "sidewalk", 3.6},
            {"creek", "bypass", "road", 2.8},
            {"station", "lane", "highway", 4.8},
            {"downtown", "station", "road", 4.3},
            {"downtown", "plaza", "highway", 5.0},
            {"downtown", "home", "road", 7.0},
            {"mall", "junction", "sidewalk", 2.5},
            {"junction", "grove", "bike lane", 2.0},
            {"grove", "downtown", "dirt road", 2.7},
            {"mall", "orchard", "dirt road", 2.3},
            {"orchard", "downtown", "sidewalk", 3.0},
            {"university", "garden", "road", 3.5},
            {"garden", "downtown", "road", 3.2},
            {"university", "avenue", "sidewalk", 2.9},
            {"avenue", "downtown", "sidewalk", 3.1},
            {"downtown", "boulevard", "road", 3.4},
            {"boulevard", "mall", "road", 3.3},
            {"downtown", "promenade", "sidewalk", 2.6},
            {"promenade", "mall", "sidewalk", 2.4}
        };
    }
};

int main() {
    vector<Segment> allSegments = NavigationApp(nullptr).getAllSegments();

    // 🚶 Walk route (sidewalk, dirt road)
    TestRoute walk({ "sidewalk", "dirt road" });
    walk.findRoute("home", "mall", allSegments);
    assert(!walk.getPath().empty());
    assert(walk.getPath().front() == "home");
    assert(walk.getPath().back() == "mall");
    assert(walk.getDistance() > 0);

    // 🚴 Bike route (bike lane, sidewalk, dirt road)
    TestRoute bike({ "bike lane", "sidewalk", "dirt road" });
    bike.findRoute("university", "mall", allSegments);
    assert(!bike.getPath().empty());
    assert(bike.getPath().front() == "university");
    assert(bike.getPath().back() == "mall");
    assert(bike.getDistance() > 0);

    // 🚗 Car route (road, highway)
    TestRoute car({ "road", "highway" });
    car.findRoute("home", "mall", allSegments);
    assert(!car.getPath().empty());
    assert(car.getPath().front() == "home");
    assert(car.getPath().back() == "mall");
    assert(car.getDistance() > 0);

    cout << "All assertions passed.\n";
    return 0;
}
