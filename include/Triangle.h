#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Point.h"

using namespace std;

class Triangle {
public:
    Triangle(Point &, Point &, Point &);
    Triangle();
    
    void setV1(Point &);
    Point getV1() const;
    
    void setV2(Point & );
    Point getV2() const;
    
    void setV3(Point & );
    Point getV3() const;

    string toStr() const;
    
    vector<Point> getVertices();
    
    double getArea() const;
    void setArea(double);//se usa en la integracion
    
private://los 3 vertices del triangulo, V = vertex
    Point V1;
    Point V2;
    Point V3;
    double Area;
    
};
#endif
