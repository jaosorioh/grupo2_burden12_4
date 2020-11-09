#include "include/Triangulation.h"
#include <algorithm>
//prototipos

using namespace std;

int findNodeIndex(vector<Point> nodes, Point p);
//step 4-Nicole
void doubleIntegrals(Triangle &triangles, vector<vector<vector<double>>> &Z, vector<vector<double>> &H);

//step 5-Nicole
void lineIntegrals(Triangle & trianglesS2, vector<vector<vector<double>>> &J, vector<vector<double>> &I);

//step 6-12-Brayan
void assembleDoubleIntegrals(Triangle &t, vector<vector<double>> & alpha, vector<double> & beta, vector<double> &gamma, vector<vector<vector<double>>> &Z, vector<vector<double>> &H);

//step 13-19-Brayan
void assembleDoubleIntegrals(Triangle &trianglesS2, vector<vector<double>> & alpha, vector<double> & beta, vector<double> &gamma, vector<vector<vector<double>>> &J, vector<vector<double>> &I);

//step 8, 10, 15, 17
int findNodeIndex(vector<Point> & nodes, Point &p){
    int i = 0;
    while(i<nodes.size())
    {
        if(p.getX() == nodes.at(i).getX() && p.getY() == nodes.at(i).getY())
            break;
        i++;
    }
    if(i == nodes.size())
        i = -1;
    return i;
}

void solve(double* (*S2Fx)(const double &, double &), double* (*S2Fy)(double &, const double &), double (*g)(const double &, const double &), vector<double> & x_i, vector<double> &y_i, int &N, int &M)
{
    
    vector<Point> nodesS1;
    vector<Point> nodesS2;
    vector<Triangle> trianglesS1;
    vector<Triangle> trianglesS2;
    vector<Triangle> trianglesnotS1S2;
    
    vector<double> x;

    vector<double> y;

    Triangulation t;
    t.multi_linspace(x_i, N, x);
    t.multi_linspace(y_i, M, y);
    
    t.buildTrianglesAndNodes(trianglesS1, trianglesS2, trianglesnotS1S2, nodesS1, nodesS2, S2Fx, S2Fy, x, y);
    /*
    string fname = "dat/S1Triangles.dat";
    t.saveTriangles(trianglesS1, fname);
    fname = "dat/S2Triangles.dat";
    t.saveTriangles(trianglesS2, fname);
    fname = "dat/NotS1S2Triangles.dat";
    t.saveTriangles(trianglesnotS1S2, fname);
    
    fname = "dat/nodesS1.dat";
    t.saveNodes(nodesS1, fname);
    fname = "dat/nodesS2.dat";
    t.saveNodes(nodesS2, fname);*/
    
    const int n = nodesS1.size();
    const int m = nodesS2.size();
    
    vector<double> gammaS1;
    
    for(int i = 0; i<n-1; i++)
    {
        gammaS1.push_back(g(nodesS1.at(i).getX(), nodesS1.at(i).getY()));
    }
    //step 2
    
    vector<vector<double>> alpha(n, vector<double> (n, 0));
    vector<double> beta(n, 0);
    
}