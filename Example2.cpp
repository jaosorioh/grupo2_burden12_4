
#include "include/FEM.h"
#include "cmath"
#include "functional"
using namespace std;

double * S2Fx(const double & x, double & y) {
    if (x >= 0.0 && x <= 1.0) {
        y = 1.0;
    }else {
        return NULL;
    }
    return &y;
}

double * S2Fy(double & x, const double & y) {
    if (y >= 0 && y <= 1.0) {
        x = 1.0;
    }else {
        return NULL;
    }
    return &x;
}


int main() {
    
    int n = 5; //number of values of x
    int m = 5;
    
    vector < double > x_i = {
        0.0,
        1.0
    };

    vector < double > y_i = {
        0.0,
        1.0
    };
    
    function<double(const double & , const double &)> g = [](const double &x, const double &y){return 0.0;}; 
    function<double(const double & , const double &)> p = [](const double &x, const double &y){return 1.0;}; 
    function<double(const double & , const double &)> r = [](const double &x, const double &y){return 0.0;}; 
    function<double(const double & , const double &)> f = [](const double &x, const double &y){
        return sin(M_PI*x)*sin(M_PI*y);
    };
    
    function<double(const double & , const double &)> g2 = [](const double &x, const double &y){
        if(x==0.0)
        {
            return -sin(y*M_PI)/(2*M_PI);            
        }
        return 0.0;
    };
    
    function<Point(const double &)> S2 = [](const double &t)
    {
        Point p;
        if(0.0<=t && t<=1.0)
        {
            p.setX(1.0*t);
            p.setY(1.0);
        }
        if(1.0<=t && t<=2.0)
        {
            p.setX(1);
            p.setY(1*(2.0-t));
        }
        return p;
    };
    
    function<Point(const double &)> DS2 = [](const double &t)
    {
        Point p;
        if(0.0<=t && t<=1.0)
        {
            p.setX(1.0);
            p.setY(0.0);
        }
        if(1.0<=t && t<=2.0)
        {
            p.setX(0.0);
            p.setY(-1.0);
        }
        return p;
    };

    double ta = 0.0;
    double tb = 2.0;
    
    FEM fem(S2Fx, S2Fy, p, p, r, f, g, g, g2, x_i, y_i, n, m, S2, DS2, ta, tb);
    fem.solve();
    return 0;
}
