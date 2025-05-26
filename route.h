#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include <vector>
#include <set>

using namespace std;

// Segment structure declaration
struct Segment {
    string from;
    string to;
    string terrain;
    double distance;
};

// Abstract base class Route
class Route {
protected:
    double totalDistance;
    vector<string> path;

public:
    // Constructor declaration
    Route();
    // Virtual destructor declaration
    virtual ~Route();
    // Pure virtual method declarations
    virtual void findRoute(const string& from, const string& to, const vector<Segment>& segments) = 0;
    virtual void displayRoute() const = 0;
    // Getter method declarations for testing
    double getDistance() const;
    vector<string> getPath() const;
};

// Derived class declarations
class WalkRoute : public Route {
public:
    WalkRoute();
    ~WalkRoute();
    
    void findRoute(const string& from, const string& to, const vector<Segment>& segments) override;
    void displayRoute() const override;
};

class BikeRoute : public Route {
public:
    BikeRoute();
    ~BikeRoute();
    
    void findRoute(const string& from, const string& to, const vector<Segment>& segments) override;
    void displayRoute() const override;
};

class CarRoute : public Route {
public:
    CarRoute();
    ~CarRoute();
    
    void findRoute(const string& from, const string& to, const vector<Segment>& segments) override;
    void displayRoute() const override;
};

// NavigationApp class declaration
class NavigationApp {
private:
    Route* strategy;
    
public:
    NavigationApp(Route* strategy);
    ~NavigationApp();
    
    void planRoute(const string& from, const string& to);
    vector<Segment> getAllSegments();
};

// TestRoute class declaration (for testing purposes)
class TestRoute : public Route {
protected:
    set<string> allowedTerrains;
    
public:
    TestRoute(const set<string>& terrains);
    ~TestRoute();
    
    void findRoute(const string& from, const string& to, const vector<Segment>& segments) override;
    void displayRoute() const override;
};

#endif // ROUTE_H
