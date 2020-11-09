#ifndef POINT_H
#define POINT_H

#include <string>
#include <vector>

using namespace std;

class Point {
public:
    Point(double&, double&);
    Point();
    void setX(double&);
    double getX() const;

    void setY(double&);
    double getY() const;

    void setXY(double&, double&);
    vector<double> getXY() const;
    string toStr() const;
    bool operator==(const Point & obj) const
    {
        return (this->getX() == obj.getX() && this->getY() == obj.getY());
    }

private:
    double x;
    double y;
};
#endif