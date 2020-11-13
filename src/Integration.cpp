/*
Implementación de la clase Integration
*/

#include <iostream>
#include <cmath>
#include <functional>

#include "../include/Triangle.h"
#include "../include/Integration.h"

using namespace std;

//constructor 
Integration::Integration( void )
{
	//lo que se necesite inicializar

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

void Integration::set2D_params( const double E1x, const double E1y, const double E2x, const double E2y, 
            const double E3x, const double E3y )
{
	double m_, dm_, d_, a_, b_, c_;

	if (E2y > E3y)
	{
		m_ = (E2y-E3y)/(E2x-E3x);

		a_ = E2x;
		b_ = E3x;
		c_ = E2y;
		d_ = E2y;
		dm_ = E2x;

		//cout << "recta: " << m_ << " (x-" << dm_ << ") + " << d_ << endl;
	}
	else if ( E3y > E2y )
	{
		m_ = ( E3y - E2y )/( E3x - E2x );

		a_ = E3x;
		b_ = E2x;
		c_ = E3y;
		d_ = E3y;
		dm_ = E3x;

		//cout << "recta: " << m_ << " (x-" << dm_ << ") + " << d_ << endl;
	}

	//estableciendo variables privadas para los límites
	_slope = m_;
	_xm = dm_;
	_intr = d_;
	_aLim = a_;
	_bLim = b_;
	_cCon = c_;

}

double Integration::_cLim( const double _x )
{
	return _cCon;
}

double Integration::_dLim( const double _x )
{
	double yy = _slope*( _x - _xm ) + _intr;
	return yy;
}

double Integration::get_aLim( void ) const
{
	return _aLim;
}

double Integration::get_bLim( void ) const
{
	return _bLim;
}

