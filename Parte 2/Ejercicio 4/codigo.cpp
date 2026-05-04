#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

struct Punto { double x, y; };

int antenaMasCercana(const vector<Punto>& antenas, Punto p) {
    double minDist = numeric_limits<double>::max();
    int asignada = -1;

    for (int i = 0; i < antenas.size(); i++) {
        double dist = sqrt(pow(antenas[i].x - p.x, 2) +
                          pow(antenas[i].y - p.y, 2));
        if (dist < minDist) {
            minDist = dist;
            asignada = i;
        }
    }
    return asignada;
}
