#include "../include/Triangle.h"

using namespace std;

Triangle::Triangle(Point& V1_, Point& V2_, Point& V3_)
{
    setV1(V1_);
    setV2(V2_);
    setV3(V3_);
}

Triangle::Triangle()
{
    Point V1_;
    Point V2_;
    Point V3_;

    setV1(V1_);
    setV2(V2_);
    setV3(V3_);
}

void Triangle::setV1(Point& V1_)
{
    V1 = V1_;
}

Point Triangle::getV1() const
{
    return V1;
}

void Triangle::setV2(Point& V2_)
{
    V2 = V2_;
}

Point Triangle::getV2() const
{
    return V2;
}

void Triangle::setV3(Point& V3_)
{
    V3 = V3_;
}

Point Triangle::getV3() const
{
    return V3;
}

string Triangle::toStr() const
{
    return getV1().toStr() + " " + getV2().toStr() + " " + getV3().toStr();
}

vector<Point> Triangle::getVertices()
{
    vector<Point> vertices = { getV1(), getV2(), getV3() };
    return vertices;
}

void Triangle::setArea(double Area_)
{
    Area = Area_;
}

double Triangle::getArea() const
{
    return Area;
}