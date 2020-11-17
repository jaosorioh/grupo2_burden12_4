#include "../include/Triangulation.h"
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

void Triangulation::loadNodes(vector<Point>& nodes, const string& fname)
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

void Triangulation::saveNodes(vector<Point>& nodes, const string& fname)
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

void Triangulation::saveTriangles(vector<Triangle>& triangles, const string& fname)
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

bool Triangulation::inside(const Point& p, double* (*SFx)(const double& x_, double& y_))
{
    double yy;

    return (SFx(p.getX(), yy) != NULL && (p.getY() < yy || abs(p.getY() - yy) <= 1e-5));
}

bool Triangulation::inside(const Triangle& t, double* (*SFx)(const double& x_, double& y_))
{
    return inside(t.getV1(), SFx) && inside(t.getV2(), SFx) && inside(t.getV3(), SFx);
}

bool Triangulation::onS(const Point& p, double* (*SFx)(const double& x_, double& y_), double* (*SFy)(double& x_, const double& y_))
{
    double xx;
    double yy;
    return ((SFx(p.getX(), yy) != NULL && abs(yy - p.getY()) <= 1e-4) || (SFy(xx, p.getY()) != NULL && abs(xx - p.getX()) <= 1e-4));
}

bool Triangulation::onS(const Triangle& t, double* (*SFx)(const double& x_, double& y_), double* (*SFy)(double& x_, const double& y_))
{
    return (onS(t.getV1(), SFx, SFy) || onS(t.getV2(), SFx, SFy) || onS(t.getV3(), SFx, SFy));
}

void Triangulation::buildTrianglesAndNodes(vector<Triangle>& trianglesS1, vector<Triangle>& trianglesS2, vector<Triangle>& trianglesnotS1S2, double* (*SFx)(const double& x_, double& y_), double* (*SFy)(double& x_, const double& y_), vector<double>& x, vector<double>& y)
{
    double Area = abs((x[1]-x[0])*(y[1]-y[0]));
    for (int i = 0; i < x.size(); i++) {
        Point p1(x.at(i), y.at(0));
        if(i < x.size()-1){
            Point p2(x.at(i), y.at(1));
            Point p3(x.at(i + 1), y.at(0));

            if ((p1.getX() != p2.getX() || p1.getY() != p2.getY()) && (p1.getX() != p3.getX() || p1.getY() != p3.getY()) && (p2.getX() != p3.getX() || p2.getY() != p3.getY())) {
                Triangle t(p1, p2, p3);
                t.setArea(Area);
                if (inside(t, SFx))
                    trianglesS1.push_back(t);
                p1.setXY(x.at(i + 1), y.at(1));
                Triangle t2(p1, p2, p3);
                t2.setArea(Area);
                if (inside(t2, SFx))
                    trianglesS1.push_back(t2);
            }
        }
    }

    for (int j = 1; j < y.size(); j++) {
        
        Point p1(x.at(0), y.at(j));
        if(j<y.size()-1)
        {
            Point p2(x.at(1), y.at(j));
            Point p3(x.at(0), y.at(j + 1));

            if ((p1.getX() != p2.getX() || p1.getY() != p2.getY()) && (p1.getX() != p3.getX() || p1.getY() != p3.getY()) && (p2.getX() != p3.getX() || p2.getY() != p3.getY())) {
                Triangle t(p1, p2, p3);
                t.setArea(Area);
                if (inside(t, SFx))
                    trianglesS1.push_back(t);
            }
            p1.setXY(x.at(1), y.at(j + 1));
            if ((p1.getX() != p2.getX() || p1.getY() != p2.getY()) && (p1.getX() != p3.getX() || p1.getY() != p3.getY()) && (p2.getX() != p3.getX() || p2.getY() != p3.getY())) {
                Triangle t2(p1, p2, p3);
                t2.setArea(Area);
                if (inside(t2, SFx))
                    trianglesS1.push_back(t2);
        }
        }
    }

    for (int i = 1; i < x.size(); i++) {
        for (int j = 1; j < y.size(); j++) {
            Area = abs((x[i+1]-x[i])*(y[j+1]-y[j]));
            Point p1(x.at(i), y.at(j));
            if (i < x.size() - 1 && j < y.size() - 1) {
                Point p2(x.at(i), y.at(j+1));
                Point p3(x.at(i+1), y.at(j));
                if ((p1.getX() != p2.getX() || p1.getY() != p2.getY()) && (p1.getX() != p3.getX() || p1.getY() != p3.getY()) && (p2.getX() != p3.getX() || p2.getY() != p3.getY())) {
                    Triangle t(p1, p2, p3);
                    t.setArea(Area);
                    if (inside(t, SFx)) {
                        if (onS(t, SFx, SFy))
                            trianglesS2.push_back(t);
                        else
                            trianglesnotS1S2.push_back(t);
                    }
                }
                if ((p1.getX() != p2.getX() || p1.getY() != p2.getY()) && (p1.getX() != p3.getX() || p1.getY() != p3.getY()) && (p2.getX() != p3.getX() || p2.getY() != p3.getY())) {
                    p1.setXY(x.at(i + 1), y.at(j + 1));
                    Triangle t2(p1, p2, p3);
                    t2.setArea(Area);
                    if (inside(t2, SFx)) {
                        if (onS(t2, SFx, SFy))
                            trianglesS2.push_back(t2);
                        else
                            trianglesnotS1S2.push_back(t2);
                    }
                }
            }
        }
    }
}
