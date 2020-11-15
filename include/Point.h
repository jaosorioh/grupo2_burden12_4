#ifndef POINT_H
#define POINT_H

#include <string>
#include <vector>

using namespace std;

class Point {
public:
    Point(double=0.0, double=0.0);//constructor
    void setX(double);
    double getX() const;
    
    void setY(double);
    double getY() const;

    void setXY(double, double);
    string toStr() const;
    
    double length() const;

private:
    double x;
    double y;
};
#endif
