#include "include/NodeBuilder.h"
#include "include/Triangulation.h"
#include <cmath>
#include <iostream>

using namespace std;

//line

/*
double x_t(double t)
{
double x1 = 0.0;
double x2 = 0.5;

return x1 + (x2 - x1)*t;

}

double y_t(double t)
{
double y2 = 0.5;
double y1 = 1.0;
if(t<=1)
	return y1 + (y2 - y1)*t;
else if(t>=1)
	return y2;
else
	return 0;
}

*/
//circle

double x_t(double t)
{
double R = 100.0;
return R*cos(t);
}

double y_t(double t)
{
double R = 100.0;
return R*sin(t);
}

int main(){

int N = 10;

double ti = 0.0;
//line
//double tf = 1.0;
//circle
double tf = M_PI/2.0; 

NodeBuilder nb(N, ti, tf, x_t, y_t);
nb.buildNodes();
nb.saveFile("nodesS1.dat");

Triangulation tria(nb.getNodes());
tria.buildTriangles();
tria.saveFile("tria.dat");

return 0;
}
