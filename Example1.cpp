/*
main correspondiente al ejemplo de la temperatura desarrollado en el Burden
*/

#include "include/Triangulation.h"
#include "include/FEM.h"
using namespace std;

double * S2Fx(const double & x, double & y) {
    if (x >= 0.0 && x < 0.2) {
        y = 0.4 - x;
    } else if (x >= 0.2 && x < 0.4) {
        y = 0.2;
    } else if (x >= 0.4 && x < 0.5) {
        y = 0.6 - x;
    } else if (x >= 0.5 && x <= 0.6) {
        y = 0.1;
    } else {
        return NULL;
    }
    return &y;
}

double * S2Fy(double & x, const double & y) {
    if (y >= 0.0 && y < 0.1)
        x = 0.6;
    else
        return NULL;
    return &x;
}

int main() {
    
    int n = 2; //number of values of x
    int m = 2;
    vector < double > x_i = {
        0.0,
        0.2,
        0.4,
        0.5,
        0.6
    };

    vector < double > y_i = {
        0.0,
        0.1,
        0.2,
        0.4
    };
    
    function<double(const double & , const double &)> g = [](const double &x, const double &y){return 4.0;}; 
    function<double(const double & , const double &)> p = [](const double &x, const double &y){return 1.0;}; 
    function<double(const double & , const double &)> r = [](const double &x, const double &y){return 0.0;}; 
    function<double(const double & , const double &)> f = [](const double &x, const double &y){
        return 0.0;
    };
    
    function<double(const double & , const double &)> g2 = [](const double &x, const double &y){
        if((y<=0.4 && y >= 0.2 && x<=0.2 && x>=0) || (y<=0.2 && y>=0.1 && x <= 0.5 && x>=0.4))
        {
            return (x+y)/sqrt(2);        
        }
        else if(x==0.6 && y<=0.1 && y>=0)
        {
            return y;
        }
        else if((y == 0.2 && x>=0.2 && x<=0.4) || (y == 0.2 && x>=0.5 && x<=0.6))
        {
            return x;
        }
        return 0.0;
    };
    
    function<Point(const double &)> S2 = [](const double &t)
    {
        Point p;
        if(0.0<=t && t<=1.0)
        {
            p.setX(0.2*t);
            p.setY(0.4 - 0.2*t);
        }
        else if(1.0 <=t && t<=2.0)
        {
            p.setX(0.2 + 0.2*(t-1.0));
            p.setY(0.2);
        }
        else if(2.0<=t && t<=3.0)
        {
            p.setX(0.4 + 0.1*(t-2));
            p.setY(0.2 - 0.1*(t-2));
        }
        else if(3.0 <=t && t<=4.0)
        {
            p.setX(0.5 + 0.1*(t-3));
            p.setY(0.1);
        }
        else if(4<=t && t <=5.0)
        {
            p.setX(0.6);
            p.setY(0.1 - 0.1*(t-4));
        }
        return p;
    };
    
    function<Point(const double &)> DS2 = [](const double &t)
    {
        Point p;
        if(0.0<=t && t<=1.0)
        {
            p.setX(0.2);
            p.setY(-0.2);
        }
        else if(1<=t && t<=2.0)
        {
            p.setX(0.2);
            p.setY(0.0);
        }
        else if(2<=t && t<=3.0)
        {
            p.setX(0.1);
            p.setY(-0.1);
        }
        else if(3<=t && t<=4.0)
        {
            p.setX(0.1);
            p.setY(0.0);
        }
        else if(4<=t && t <=5.0)
        {
            p.setX(0.0);
            p.setY(-0.1);
        }
        return p;
    };

    double ta = 0.0;
    double tb = 5.0;
    
    FEM fem(S2Fx, S2Fy, p, p, r, f, g, r, g2, x_i, y_i, n, m, S2, DS2, ta, tb);
    fem.solve();
    return 0;
}
