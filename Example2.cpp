#include "include/Triangulation.h"

using namespace std;

double * S2Fx(const double & x, double & y) {
    if (x >= 0.0 && x <= 0.4) {
        y = 0.4;
    }else {
        return NULL;
    }
    return &y;
}

double * S2Fy(double & x, const double & y) {
    if (y >= 0 && y <= 0.4) {
        x = 0.4;
    }else {
        return NULL;
    }
    return &x;
}

int main() {
    
    int n = 10; //number of values of x
    int m = 10;
    
    vector < double > x_i = {
        0.0,
        0.4
    };

    vector < double > y_i = {
        0.0,
        0.4
    };
    
    vector<Point> nodesS1;
    vector<Point> nodesS2;
    vector<Triangle> trianglesS1;
    vector<Triangle> trianglesS2;
    vector<Triangle> trianglesnotS1S2;
    
    Triangulation t;
    t.buildTrianglesAndNodes(trianglesS1, trianglesS2, trianglesnotS1S2, nodesS1, nodesS2, S2Fx, S2Fy, x_i, y_i, n, m);
    
    string fname = "dat/S1Triangles.dat";
    t.saveTriangles(trianglesS1, fname);
    fname = "dat/S2Triangles.dat";
    t.saveTriangles(trianglesS2, fname);
    fname = "dat/NotS1S2Triangles.dat";
    t.saveTriangles(trianglesnotS1S2, fname);
    
    return 0;
}
