#ifndef FEM_H
#define FEM_H

#include "Triangulation.h"
#include <algorithm>
#include <iostream>
#include <functional>
#include "linearalgebra.cpp"
#include "Integrals.h"

using namespace std;

class FEM {
    public:
    FEM(double* (*)(const double&, double&), double* (*)(double&, const double&), function<double(const double &, const double &)> &, function<double(const double &, const double &)> &, function<double(const double &, const double &)> &, function<double(const double &, const double &)> &, function<double(const double &, const double &)> &, function<double(const double &, const double &)> &, function<double(const double &, const double &)> &, vector<double>&, vector<double>&, int& , int& , function<Point(const double &)> &, function<Point(const double &)> &, const double &, const double &);
    void solve();
    
    private:
    void coefABC(Triangle&, vector<double>&, vector<double>&, vector<double>&);
    void coefABC();
    void doubleIntegrals();
    void lineIntegrals();
    int findNodeIndex(Point&);
    int findNodeIndex(Point&, vector<Point>);
    void assembleDoubleIntegrals();
    void assembleLineIntegrals();
    vector<Triangle> Triangles;
    vector<Point> Nodes;
    int K, N, M, n, m;
    
    vector<vector<double>> alpha;
    vector<double> beta;
    vector<double> gamma;
    vector<double> xx;
    vector<double> yy;
    vector<vector<vector<double>>> Z;
    vector<vector<double>> H;
    
    vector<vector<vector<double>>> J;
    vector<vector<double> > I;
    
    function<double(const double &, const double &)> p;
    function<double(const double &, const double &)>q;
    function<double(const double &, const double &)>r;
    function<double(const double &, const double &)>f;
    function<double(const double &, const double &)>g;
    function<double(const double &, const double &)>g1;
    function<double(const double &, const double &)>g2;
    function<Point(const double &)>SE;
    function<Point(const double &)>DSE;
    double ta;
    double tb;
    
    Integrals Integrator;
    vector<vector<double> > A;
    vector<vector<double> > B;
    vector<vector<double> > C;
};


#endif