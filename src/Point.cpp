#include <string>

#include "../include/Point.h"

using namespace std;

Point::Point(double x_, double y_)
{
    setX(x_);
    setY(y_);
}

void Point::setX(double x_)
{
    x = x_;
}

double Point::getX() const
{
    return x;
}

void Point::setY(double y_)
{
    y = y_;
}

double Point::getY() const
{
    return y;
}

void Point::setXY(double x_, double y_)
{
    setX(x_);
    setY(y_);
}

vector<double> Point::getXY() const
{
    const vector<double> r = { getX(), getY() };
    return r;
}

string Point::toStr() const
{
    return std::to_string(getX()) + " " + std::to_string(getY());
}
