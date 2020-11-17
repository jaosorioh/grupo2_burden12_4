/*
Implementacion clase Point.h
*/

#include <string>

#include "cmath"
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

/* ---------------------
Metodo que toma la coordenada (x, y) y lo convierte en un formato de string leible.
INPUTS: 
OUTPUT: string donde se separa las coordenadas por " ".
-----------------------*/
string Point::toStr() const
{
    return std::to_string(getX()) + " " + std::to_string(getY());
}

/* ---------------------
Obtiene la longitud de un punto con respecto al origen (0, 0).
INPUTS:
OUTPUT double con la longitud del pubto*/
double Point::length() const
{
    return pow(pow(getX(), 2) + pow(getY(), 2), 0.5);
}
