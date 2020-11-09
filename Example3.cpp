#include "include/Triangulation.h"
#include "FEM.cpp"
using namespace std;

double * S2Fx(const double & x, double & y) {
    if (x >= 0.0 && x <= 0.5) {
        y = 1-x;
    }
    else {
        return NULL;
    }
    return &y;
}

double * S2Fy(double & x, const double & y) {
    if (y >= 0.5 && y <= 1.0) {
        x = 1-y;
    }else {
        return NULL;
    }
    return &x;
}

double g(const double &x, const double &y)
{
    return 4.0;    
}

int main() {
    
    int n = 10; //number of values of x
    int m = 10;
    vector < double > x_i = {
        0.0,
        0.5
    };

    vector < double > y_i = {
        0.5,
        1.0
    };
    
    solve(S2Fx, S2Fy, g, x_i, y_i, n, m);
    return 0;
}
