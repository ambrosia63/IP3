#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Segment {
    string from;
    string to;
    string terrain;
    double distance;
};

class Route {
protected:
    vector<string> path;
    double totalDistance = 0.0;

public:
    virtual void findRoute(const string& from, const string& to, const vector<Segment>& segments) = 0;

    virtual void displayRoute() const {
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i != path.size() - 1)
                cout << " -> ";
        }
        cout << "\nTotal Distance: " << totalDistance << " km\n";
    }

    vector<string> getPath() const { return path; }
    double getDistance() const { return totalDistance; }

    virtual ~Route() = default; // optional but recommended
};

#endif
