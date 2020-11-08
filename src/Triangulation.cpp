#include "../include/Triangulation.h"
#include <fstream>
#include <iostream>

using namespace std;

void Triangulation::linspace(double &i, double &f, int &N, bool &endpoint, vector<double> &a) {
    if (N == 1) {
        a.push_back(i);
    } else if (N > 1) {
        a.push_back(i);
        double h;
        h = (f - i) / (static_cast < double > (N - (endpoint ? 1 : 0)));

        for (int j = 1; j < N - 1; j++) {
            a.push_back(a.back() + h);
        }

        a.push_back(endpoint == true ? f : a.back() + h);
    } else {
        cout << "Debe tener al menos 1 elemento para linspace";
    }
}

    
void Triangulation::multi_linspace(vector < double > & v, int & N, vector < double > & a) {
    for (int i = 1; i < v.size(); i++) {
        double dvi = v.at(i) - v.at(i - 1);
        bool ep = true;//i == (v.size() - 1);
        vector < double > b;
        linspace(v.at(i - 1), v.at(i), N, ep, b);
        a.insert(a.end(), b.begin(), b.end());
    }
    

}   

void Triangulation::loadNodes(vector<Point> &nodes, const string & fname)
{
    ifstream nodesFile(fname.c_str());

    if (nodesFile.fail()) {
        cout << "Nodes file cannot be opened." << endl;
        exit(1);
    }

    while (!nodesFile.eof()) {
        double x;
        double y;
        nodesFile >> x >> y;

        Point node(x, y);
        nodes.push_back(node);
    }

    nodesFile.close();
}

void Triangulation::saveNodes(vector<Point> &nodes, const string & fname)
{
    ofstream nodesFile(fname.c_str());

    if (nodesFile.fail()) {
        cout << "Nodes file cannot be opened." << endl;
        exit(1);
    }

    for (int i = 0; i < nodes.size(); i++) {
        nodesFile << nodes.at(i).toStr() << endl;
    }

    nodesFile.close();
}

void Triangulation::saveTriangles(vector<Triangle> &triangles, const string & fname)
{
    ofstream trianglesFile(fname.c_str());

    if (trianglesFile.fail()) {
        cout << "Triangles file cannot be opened." << endl;
        exit(1);
    }

    for (int i = 0; i < triangles.size(); i++) {
        trianglesFile << triangles.at(i).toStr() << endl;
    }

    trianglesFile.close();
}

void Triangulation::buildTrianglesAndNodes(vector<Triangle> & trianglesS1, vector<Triangle> & trianglesS2, vector<Triangle> & trianglesnotS1S2, vector<Point> & nodesS1, vector<Point>& nodesS2, double* (*SFx)(const double & x_, double &y_), double* (*SFy)(double &x_, const double &y_), vector<double> & x_i, vector<double> & y_i, int & N, int &M)
{
    vector < double > x;

    vector < double > y;
    
    multi_linspace(x_i, N, x);
    multi_linspace(y_i, M, y);
    
    for(int i = 0; i<x.size()-1; i++)
    {
        for(int j = 0; j<y.size()-1; j++)
        {
            double xx;
            double yy;
            if(SFx(x.at(i), yy)!=NULL && (y.at(j)<yy || abs(y.at(j) - yy)<=1e-5))
            {
                if(SFx(x.at(i+1), yy)!=NULL && (y.at(j)<yy || abs(y.at(j) - yy)<=1e-5))
                {                    
                    if(SFx(x.at(i), yy)!=NULL && (y.at(j+1)<yy || abs(y.at(j+1) - yy)<=1e-5))
                    {
                        Point p1(x.at(i), y.at(j));
                        Point p2(x.at(i), y.at(j+1));
                        Point p3(x.at(i+1), y.at(j));
                        Triangle t(p1, p2, p3);
                        
                        double x1, x2, x3;
                        double y1, y2, y3;
                        
                        SFx(p1.getX(), y1);
                        SFx(p2.getX(), y2);
                        SFx(p3.getX(), y3);
                        
                        SFy(x1, p1.getY());
                        SFy(x2, p2.getY());
                        SFy(x3, p3.getY());
                                        
                        if((abs(p1.getX() - x1)<=1e-5 || abs(p1.getY() - y1)<=1e-5) || (abs(p2.getX() - x2)<=1e-5 || abs(p2.getY() - y2)<=1e-5) || (abs(p3.getX() - x3)<=1e-5 || abs(p3.getY() - y3)<=1e-5))
                        {
                            trianglesS2.push_back(t);
                        }
                        else if(p1.getX() != x_i.at(0) && p1.getY()!=y_i.at(0) && p2.getX()!=x_i.at(0) && p2.getY()!=y_i.at(0) && p3.getX()!=x_i.at(0) && p3.getY()!=y_i.at(0))
                        {
                            trianglesnotS1S2.push_back(t);
                        }
                        else
                        {
                            trianglesS1.push_back(t);
                        }
                    }
                }
            }
            
            if(SFx(x.at(i), yy)!=NULL && (y.at(j+1)<yy || abs(y.at(j+1) - yy)<=1e-5))
            {
                if(SFx(x.at(i+1), yy)!=NULL && (y.at(j+1)<yy || abs(y.at(j+1) - yy)<=1e-5))
                {                    
                    if(SFx(x.at(i+1), yy)!=NULL && (y.at(j)<yy || abs(y.at(j) - yy)<=1e-5))
                    {
                        Point p1(x.at(i), y.at(j+1));
                        Point p2(x.at(i+1), y.at(j+1));
                        Point p3(x.at(i+1), y.at(j));
                        Triangle t(p1, p2, p3);
                        
                        double x1, x2, x3;
                        double y1, y2, y3;
                        
                        SFx(p1.getX(), y1);
                        SFx(p2.getX(), y2);
                        SFx(p3.getX(), y3);
                        
                        SFy(x1, p1.getY());
                        SFy(x2, p2.getY());
                        SFy(x3, p3.getY());
                                        
                        if((abs(p1.getX() - x1)<=1e-5 || abs(p1.getY() - y1)<=1e-5) || (abs(p2.getX() - x2)<=1e-5 || abs(p2.getY() - y2)<=1e-5) || (abs(p3.getX() - x3)<=1e-5 || abs(p3.getY() - y3)<=1e-5))
                        {
                            trianglesS2.push_back(t);
                        }
                        else if(p1.getX() != x_i.at(0) && p1.getY()!=y_i.at(0) && p2.getX()!=x_i.at(0) && p2.getY()!=y_i.at(0) && p3.getX()!=x_i.at(0) && p3.getY()!=y_i.at(0))
                        {
                            trianglesnotS1S2.push_back(t);
                        }
                        else
                        {
                            trianglesS1.push_back(t);
                        }
                    }
                }
            }
            
        } 
    }
}
