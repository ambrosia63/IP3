#include "route.h"
#include <iostream>
#include <vector>

using namespace std;

NavigationApp::NavigationApp(Route* strategy) : strategy(strategy) {}

NavigationApp::~NavigationApp() {}

void NavigationApp::planRoute(const string& from, const string& to) {
    vector<Segment> segments = getAllSegments();
    strategy->findRoute(from, to, segments);
    strategy->displayRoute();
}

vector<Segment> NavigationApp::getAllSegments() {
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
