#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Point.h"

using namespace std;

class Triangle {
public:
    Triangle(Point &, Point &, Point &);
    Triangle();
    
    void setE1(Point &);
    Point getE1() const;
    
    void setE2(Point & );
    Point getE2() const;
    
    void setE3(Point & );
    Point getE3() const;

    string toStr() const;
    
private://los 3 vertices del triangulo, el E es por "edge"
    Point E1;
    Point E2;
    Point E3;
    
};
#endif
