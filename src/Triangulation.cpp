#include "../include/Triangulation.h"
#include <fstream>
#include <iostream>

using namespace std;

void Triangulation::linspace(double& i, double& f, int& N, bool& endpoint, vector<double>& a)
{
    if (N == 1) {
        a.push_back(i);
    }
    else if (N > 1) {
        a.push_back(i);
        double h;
        h = (f - i) / (static_cast<double>(N - (endpoint ? 1 : 0)));

        for (int j = 1; j < N - 1; j++) {
            a.push_back(a.back() + h);
        }

        a.push_back(endpoint == true ? f : a.back() + h);
    }
    else {
        cout << "Debe tener al menos 1 elemento para linspace";
    }
}

void Triangulation::multi_linspace(vector<double>& v, int& N, vector<double>& a)
{
    for (int i = 1; i < v.size(); i++) {
        double dvi = v.at(i) - v.at(i - 1);
        bool ep = true; //i == (v.size() - 1);
        vector<double> b;
        linspace(v.at(i - 1), v.at(i), N, ep, b);
        a.insert(a.end(), b.begin(), b.end());
    }
}

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
    return inside(t.getE1(), SFx) && inside(t.getE2(), SFx) && inside(t.getE3(), SFx);
}

bool Triangulation::onS(const Point& p, double* (*SFx)(const double& x_, double& y_), double* (*SFy)(double& x_, const double& y_))
{
    double xx;
    double yy;
    return ((SFx(p.getX(), yy) != NULL && abs(yy - p.getY()) <= 1e-4) || (SFy(xx, p.getY()) != NULL && abs(xx - p.getX()) <= 1e-4));
}

bool Triangulation::onS(const Triangle& t, double* (*SFx)(const double& x_, double& y_), double* (*SFy)(double& x_, const double& y_))
{
    return (onS(t.getE1(), SFx, SFy) || onS(t.getE2(), SFx, SFy) || onS(t.getE3(), SFx, SFy));
}

void Triangulation::buildTrianglesAndNodes(vector<Triangle>& trianglesS1, vector<Triangle>& trianglesS2, vector<Triangle>& trianglesnotS1S2, vector<Point>& nodesS1, vector<Point>& nodesS2, double* (*SFx)(const double& x_, double& y_), double* (*SFy)(double& x_, const double& y_), vector<double>& x, vector<double>& y)
{
    for (int i = 0; i < x.size() - 1; i++) {
        Point p1(x.at(i), y.at(0));
        Point p2(x.at(i), y.at(1));
        Point p3(x.at(i + 1), y.at(0));

        nodesS1.push_back(p1);
        if (i == x.size() - 2)
            nodesS1.push_back(p3);
        if ((p1.getX() != p2.getX() || p1.getY() != p2.getY()) && (p1.getX() != p3.getX() || p1.getY() != p3.getY()) && (p2.getX() != p3.getX() || p2.getY() != p3.getY())) {
            Triangle t(p1, p2, p3);
            if (inside(t, SFx))
                trianglesS1.push_back(t);
            p1.setXY(x.at(i + 1), y.at(1));
            Triangle t2(p2, p3, p1);
            if (inside(t2, SFx))
                trianglesS1.push_back(t2);
        }
    }

    for (int j = 0; j < y.size() - 1; j++) {
        Point p1(x.at(0), y.at(j));
        Point p2(x.at(1), y.at(j));
        Point p3(x.at(0), y.at(j + 1));

        nodesS1.push_back(p1);
        if (j == y.size() - 2)
            nodesS1.push_back(p3);

        if ((p1.getX() != p2.getX() || p1.getY() != p2.getY()) && (p1.getX() != p3.getX() || p1.getY() != p3.getY()) && (p2.getX() != p3.getX() || p2.getY() != p3.getY())) {
            Triangle t(p1, p2, p3);

            if (inside(t, SFx))
                trianglesS1.push_back(t);
        }
        p1.setXY(x.at(1), y.at(j + 1));
        if ((p1.getX() != p2.getX() || p1.getY() != p2.getY()) && (p1.getX() != p3.getX() || p1.getY() != p3.getY()) && (p2.getX() != p3.getX() || p2.getY() != p3.getY())) {
            Triangle t2(p1, p3, p2);
            if (inside(t2, SFx))
                trianglesS1.push_back(t2);
        }
    }

    for (int i = 1; i < x.size(); i++) {
        for (int j = 1; j < y.size(); j++) {
            Point p1(x.at(i), y.at(j));
            if (onS(p1, SFx, SFy)) {
                if (nodesS2.size() == 0 || (nodesS2.size() > 0 && (nodesS2.back().getX() != p1.getX() || nodesS2.back().getY() != p1.getY())))
                    nodesS2.push_back(p1);
            }
            if (i < x.size() - 1 && j < y.size() - 1) {
                Point p2(x.at(i + 1), y.at(j));
                Point p3(x.at(i), y.at(j + 1));
                if (onS(p1, SFx, SFy)) {
                    if (nodesS2.size() == 0 || (nodesS2.size() > 0 && (nodesS2.back().getX() != p1.getX() || nodesS2.back().getY() != p1.getY())))
                        nodesS2.push_back(p1);
                    if (onS(p1, SFx, SFy)) {
                        if (nodesS2.size() == 0 || (nodesS2.size() > 0 && (nodesS2.back().getX() != p1.getX() || nodesS2.back().getY() != p1.getY())))
                            nodesS2.push_back(p1);
                    }
                }
                if ((p1.getX() != p2.getX() || p1.getY() != p2.getY()) && (p1.getX() != p3.getX() || p1.getY() != p3.getY()) && (p2.getX() != p3.getX() || p2.getY() != p3.getY())) {
                    Triangle t(p1, p2, p3);

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
