// ===========================
// bike_route.cpp
// Strategy: Biking using bike lanes, sidewalks, and dirt roads
// ===========================

#include "route.h"
#include <iostream>
#include <set>

using namespace std;

class BikeRoute : public Route {
    double totalDistance = 0;
    vector<string> path;

public:
    void findRoute(const string& from, const string& to, const vector<Segment>& segments) override {
        set<string> allowedTerrains = {"bike lane", "sidewalk", "dirt road"};
        totalDistance = 0;
        path.clear();

        for (const auto& seg : segments) {
            if (allowedTerrains.count(seg.terrain)) {
                if (path.empty() && seg.from == from) {
                    path.push_back(seg.from);
                    path.push_back(seg.to);
                    totalDistance += seg.distance;
                } else if (!path.empty() && path.back() == seg.from) {
                    path.push_back(seg.to);
                    totalDistance += seg.distance;
                    if (seg.to == to) break;
                }
            }
        }
    }

    void displayRoute() const override {
        if (!path.empty()) {
            for (const auto& loc : path) cout << loc << " -> ";
            cout << "END\n";
            cout << "Total distance: " << totalDistance << " km\n";
            cout << "Estimated time: " << (totalDistance / 20) * 60 << " min\n\n";
        } else {
            cout << "No route found.\n\n";
        }
    }
};
