#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include "Triangle.h"

using namespace std;

class Triangulation {
public:
    void linspace(double &, double &, int &, bool &, vector<double> &); 
    void multi_linspace(vector < double > &, int &, vector < double > &);
    void loadNodes(vector<Point> &, const string &);
    void saveNodes(vector<Point> &, const string &);
    void saveTriangles(vector<Triangle> &, const string &);
    void buildTrianglesAndNodes(vector<Triangle> &, vector<Triangle> &, vector<Triangle> &, vector<Point> &, vector<Point>&, double* (*)(const double &, double &), double* (*)(double &, const double &), vector<double> &, vector<double> &, int &, int &);
private:
    bool inside(const Point&, double* (*)(const double&, double&));
    bool inside(const Triangle&, double* (*)(const double&, double&));
    bool onS(const Point&, double* (*)(const double&, double&), double* (*)(double&, const double&));
    bool onS(const Triangle&, double* (*)(const double&, double&), double* (*)(double&, const double&));

};
#endif
