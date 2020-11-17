#ifndef INTEGRALS_H
#define INTEGRALS_H

#include <functional>
#include <vector>
#include "../include/Triangle.h"

using namespace std;

class Integrals {
public:
    Integrals(void); //constructor

    double Integration2D(Triangle&, function<double(const double&, const double&)>&);

    double lineIntegration(function<double(const double&, const double&)>&, function<Point(const double&)>&, function<Point(const double&)>&, const double, const double);

    double Simpsons_comp1D(function<double(const double&)>&, double, double);

private:
    Point derivativeS(function<Point(const double&)>, const double&);
    double Gaussian_quad2D(function<double(const double&, const double&)>&, double, double, double, function<double(const double&)>&);
    
    //revisar como declarar esto sin que se queje el compilador
    const double r_ij[5][5] = {
        { 0.0, 0.0, 0.0, 0.0, 0.0 },
        // Roots n=2
        { 0.5773502692, -0.5773502692, 0.0, 0.0, 0.0 },
        // Roots n=3
        { 0.7745966692, 0.0000000000, -0.7745966692, 0.0, 0.0 },
        // Roots n=4
        { 0.8611363116, 0.3399810436, -0.3399810436, -0.8611363116, 0.0 },
        // Roots n=5
        { 0.9061798459, 0.5384693101, 0.0000000000, -0.5384693101, -0.9061798459 }
    };

    const double C_ij[5][5] = {
        { 0.0, 0.0, 0.0, 0.0, 0.0 },
        // Roots n=2
        { 1.0000000000, 1.0000000000, 0.0, 0.0, 0.0 },
        // Roots n=3
        { 0.5555555556, 0.8888888889, 0.5555555556, 0.0, 0.0 },
        // Roots n=4
        { 0.3478548451, 0.6521451549, 0.6521451549, 0.3478548451, 0.0 },
        // Roots n=5
        { 0.2369268850, 0.4786286705, 0.5688888889, 0.4786286705, 0.2369268850 }
    };
};
#endif
