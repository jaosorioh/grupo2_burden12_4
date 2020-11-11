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
    
private:
    //raices y coeficientes para integrar
    double r_ij[5][5];
    double C_ij[5][5];
/*construye una línea recta con la forma “y = mx + b” a partir de la diagonal de un triangulo, devuelve una funcion.”. 
*/
    std::function<double (double)> getAsLine(Triangle t);
 /*
 Construye una curva parámetrica , usando aproximacion de bezier a partir de una coleccion de Point, estos son los nodos en la superficie de S2. Cada Point contiene 2 atributos: x y y: getX(), getY(), y en general, esta ordenados del que está más a la izquierda de la curva, al que esta más a la derecha*/
    std::function<Point (double)> bezier(vector<Point> nodesS);
    /*derivada de una curva bezier, al parecer se requiere para la integracion por contorno. Referencia: https://pages.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/Bezier/bezier-der.html*/
    std::function<Point (double)> bezierDt(vector<Point> nodesS);
    

};
#endif
