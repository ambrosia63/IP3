#include "route.h"

using namespace std;

Route::Route() : totalDistance(0) {}

Route::~Route() {}

double Route::getDistance() const {
    return totalDistance;
}

vector<string> Route::getPath() const {
    return path;
}
