#include "include/Triangulation.h"
#include "FEM.cpp"
#include "cmath"
#include "functional"
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
    
    int n = 4; //number of values of x
    int m = 4;
    
    vector < double > x_i = {
        0.0,
        0.4
    };

    vector < double > y_i = {
        0.0,
        0.4
    };
    
    function<double(const double & , const double &)> g = [](const double &x, const double &y){return 0.0;}; 
    function<double(const double & , const double &)> p = [](const double &x, const double &y){return 1.0;}; 
    function<double(const double & , const double &)> r = [](const double &x, const double &y){return -12.5*pow(M_PI, 2.0);}; 
    function<double(const double & , const double &)> f = [](const double &x, const double &y){
        return -25.0*pow(M_PI, 2.0)*sin(5.0*M_PI*x/2.0)*sin(5.0*M_PI*y/2.0);
    };
    function<Point(const double &)> S2 = [](const double &t)
    {
        Point p;
        if(0.0<=t && t<=1.0)
        {
            p.setX(0.4*t);
            p.setY(0.4);
        }
        if(1.0<=t && t<=2.0)
        {
            p.setX(0.4);
            p.setY(0.4*(2.0-t));
        }
        return p;
    };

    double ta = 0.0;
    double tb = 2.0;
    
    FEM fem(S2Fx, S2Fy, p, p, r, f, g, g, g, x_i, y_i, n, m, S2, ta, tb);
    fem.solve();
    return 0;
}
