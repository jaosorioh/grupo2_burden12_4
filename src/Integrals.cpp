/*
Implementación de la clase Integration
*/

#include <iostream>
#include <cmath>
#include "../include/Integrals.h"

using namespace std;

//constructor
Integrals::Integrals(void)
{
    //lo que se necesite inicializar
}

/*--------------------
Función que realiza integrales 2D
INPUTS: Triangulo de la clase Triangle, F(x, y) a integrar
OUTPUT: Valor de la integral de F(x, y) en el Triangulo
----------------------*/
double Integrals::Integration2D(Triangle& Tr, function<double(const double& _x, const double& _y)>& toInt)
{
    double x1, y1, x2, y2, x3, y3;
    x1 = Tr.getV1().getX();
    y1 = Tr.getV1().getY();

    x2 = Tr.getV2().getX();

    y2 = Tr.getV2().getY();

    x3 = Tr.getV3().getX();
    y3 = Tr.getV3().getY();

    
    function<double(const double&, const double&)> x = [&x1, &x2, &x3](const double& s, const double&t) { return x1 + (x2-x1)*s+(x3-x1)*t;};
    
    function<double(const double&, const double&)> y = [&y1, &y2, &y3](const double& s, const double&t) { return y1 + (y2-y1)*s+(y3-y1)*t;};
    
    function<double(const double&, const double&)> fst = [&toInt, &x, &y](const double & s, const double &t){
        return toInt(x(s, t), y(s, t));
    };
    
    function<double(const double&)> t_s = [](const double & s){
        return 1-s;
    };
    
    double result = Tr.getArea()*Gaussian_quad2D(fst, 0, 1, 0, t_s);
    
    return result;
}

/*----------------------
Función que realiza integral 2D de linea sobre contorno parametrizado
INPUTS: F(x, y) a integrar, SE(t) contorno parametrizado, valores extremos ta y tb
OUTPUTS: double - valor de la integral de línea sobre el contorno
----------------------*/
double Integrals::lineIntegration(function<double(const double& _x, const double& _y)>& toInt, function<Point(const double& t_)>& SE, function<Point(const double& t_)>& DSE, const double ta, const double tb)
{
    //Ingresar al integrador
    double result;
    function<double(const double&)> f = [this, &toInt, &SE, &DSE](const double& t) {
        double al = DSE(t).length();
        Point p = SE(t);
        return toInt(p.getX(), p.getY()) * al;
    };

    result = Simpsons_comp1D(f, ta, tb);

    return result;
}

/* ---------------------
Integrador 2D usando el método cuadratura Gaussiana
INPUTS: función 2D (integrando), límites a y b númericos, límites funcionales c y d
OUTPUT: aproximación númerica al valor de la integral en el intervalo dado
-----------------------*/
double Integrals::Gaussian_quad2D(function<double(const double& _x, const double& _y)>& Function,
    double a, double b, double c, function<double(const double& yy_)>& Fd)
{
    int m = 5 - 1;
    int n = 5 - 1;
    double x, y, c1, d1, k1, k2, JX, Q;

    double h1 = (b - a) / 2.0;
    double h2 = (b + a) / 2.0;
    double J = 0;

    for (int i = 0; i <= m; i++) {
        JX = 0;
        x = h1 * r_ij[m][i] + h2;
        c1 = c;
        d1 = Fd(x);
        k1 = (d1 - c1) / 2.0;
        k2 = (d1 + c1) / 2.0;

        for (int j = 0; j <= n; j++) {
            y = k1 * r_ij[n][j] + k2;
            Q = Function(x, y);
            JX += C_ij[n][j] * Q;
        }

        J += C_ij[m][i] * k1 * JX;
    }

    J = h1 * J;

    return J;
}

/*---------------------
Integrador numerico 1D
INPUTS: función a integrar F(x), limites a,b
OUTPUTS: double - valor de la integral de F(x) en el intervalo [a,b] 
---------------------*/
double Integrals::Simpsons_comp1D(function<double(const double&)>& func, double a, double b)
{
    int n = 100;
    double X, XI;

    double h = (b - a) / n;
    double XI0 = func(a) + func(b);
    double XI1 = 0;
    double XI2 = 0;

    for (int i = 0; i < n; i++) {
        X = a + i * h;

        if (i % 2 == 0) {
            XI2 += func(X);
        }
        else {
            XI1 += func(X);
        }
    }
    XI = h * (XI0 + 2 * XI2 + 4 * XI1) / 3.0;

    return XI;
}
