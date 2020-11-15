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

int main() {
    
    int n = 16; //number of values of x
    int m = 16;
    vector < double > x_i = {
        0.0,
        0.5
    };

    vector < double > y_i = {
        0.5,
        1.0
    };
    
    function<double(const double & , const double &)> p = [](const double &x, const double &y){return pow(y, 2);}; 
    function<double(const double & , const double &)> g = [](const double &x, const double &y){
        if(y == 0.5 && x>=0 && x<=0.5)
        {
           return 2*x; 
        }
    else if(x == 0.5 && y>=0 && y<=0.5)
    {
        return 0.0;
    }
    return 0.0;}; 
    function<double(const double & , const double &)> r = [](const double &x, const double &y){return -y;}; 
    function<double(const double & , const double &)> f = [](const double &x, const double &y){return -x;};
    
    function<double(const double & , const double &)> g1 = [](const double &x, const double &y){return 0;}; 
    function<double(const double & , const double &)> g2 = [](const double &x, const double &y){return (sqrt(2.0)/2.0)*(y - x);}; 
    function<Point(const double &)> S2 = [](const double &t)
    {
        Point p;
        if(0.0<=t && t<=1.0)
        {
            p.setX(0.5*t);
            p.setY(1 - 0.5*t);
        }
        return p;
    };

    double ta = 0.0;
    double tb = 1.0;
    
    FEM fem(S2Fx, S2Fy, p, p, r, f, g, g1, g2, x_i, y_i, n, m, S2, ta, tb);
    fem.solve();
    return 0;
}
