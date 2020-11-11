/*
Implementación de la clase Integration
*/

#include <iostream>
#include <cmath>
#include <functional>

#include "Triangle.h"
#include "Integration.h"

using namespace std;

//constructor 
Integration::Integration( void )
{
	//lo que se necesite inicializar
	r_ij = {
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

	C_ij = {
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

}

/* ---------------------
Integrador 2D usando el método cuadratura Gaussiana
INPUTS: función 2D (integrando), límites a y b númericos, límites funcionales c y d
OUTPUT: aproximación númerica al valor de la integral en el intervalo dado
-----------------------*/ 
double Integration::Gaussian_quad2D( double (*Function)( const double x_, const double y_),
				double a, double b, double (*Fc)(const double xx_), double (*Fd)(const double yy_) )
{
	int m = 5 - 1;
	int n = 5 - 1; 
	double x, y, d1, c1, k1, k2, JX, Q;

	double h1 = (b-a)/2.0;
	double h2 = (b+a)/2.0;
	double J = 0;

	for ( int i = 0; i<=m; i++)
	{
		JX = 0;
		x = h1*r_ij[m][i] + h2;
		d1 = Fd(x);
		c1 = Fc(x);
		k1 = (d1 - c1)/2.0;
		k2 = (d1 + c1)/2.0;

		for ( int j = 0; j<=n; j++)
		{
			y = k1*r_ij[n][j] + k2;
			Q = Function( x, y );
			JX += C_ij[n][j]*Q;
		}

		J += C_ij[m][i]*k1*JX;
	}

	J = h1*J;

	return J;
}