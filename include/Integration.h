#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <functional>
#include "Triangle.h"

using namespace std;

class Integration {
public:

    Integration( void ); //constructor

    double Gaussian_quad2D( double (*)( const double, const double),
                double, double, double (*)(const double), double (*)(const double) );

    double Integration2D(Triangle &, double* (*)(const double &, double &));
    

    /*aun no estoy muy claro con este punto*/
    double lineIntegration(vector<Point> &, double *(*)(const double &, const double &));

    //funciones para obtener limites de integración
    double get_aLim( void ) const;
    double get_bLim( void ) const;
    
private:
    //parametros para los límites 2D de integración
    double _slope;
    double _xm;
    double _intr;
    double _aLim;
    double _bLim;
    double _cCon;

    double _cLim( const double );
    double _dLim( const double );

    //modifica variables 
    void set2D_params( const double E1x, const double E1y, const double E2x, const double E2y, 
            const double E3x, const double E3y );

    //revisar como declarar esto sin que se queje el compilador 
    const double r_ij[5][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0},
        // Roots n=2 
        {0.5773502692, -0.5773502692, 0.0, 0.0, 0.0},
        // Roots n=3 
        {0.7745966692, 0.0000000000, -0.7745966692, 0.0, 0.0},
        // Roots n=4
        {0.8611363116, 0.3399810436, -0.3399810436, -0.8611363116, 0.0},
        // Roots n=5 
        {0.9061798459, 0.5384693101, 0.0000000000, -0.5384693101, -0.9061798459} 
    };

    const double C_ij[5][5] = {
        {0.0, 0.0, 0.0, 0.0, 0.0},
        // Roots n=2 
        {1.0000000000, 1.0000000000, 0.0, 0.0, 0.0},
        // Roots n=3 
        {0.5555555556, 0.8888888889, 0.5555555556, 0.0, 0.0},
        // Roots n=4 
        {0.3478548451, 0.6521451549, 0.6521451549, 0.3478548451, 0.0},
        // Roots n=5 
        {0.2369268850, 0.4786286705, 0.5688888889, 0.4786286705, 0.2369268850} 
    };
};
#endif
