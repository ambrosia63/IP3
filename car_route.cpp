// car_route.cpp

#include "route.h"
#include <iostream>
#include <set>
#include <iomanip>

using namespace std;

class CarRoute : public Route {
    double totalDistance = 0;
    vector<string> path;

public:
    void findRoute(const string& from, const string& to, const vector<Segment>& segments) override {
        set<string> allowedTerrains = {"road", "highway"};
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
        if (!path.empty() && path.front() != path.back()) {
            for (const auto& loc : path) cout << loc << " -> ";
            cout << "END\n";
            cout << fixed << setprecision(0); // This ensures no decimal points
            cout << "Total distance: " << totalDistance << " km\n";
            cout << "Estimated time: " << (totalDistance / 70) * 60 << " min\n\n";
        } else {
            cout << "No route found.\n\n";
        }
    }
};

