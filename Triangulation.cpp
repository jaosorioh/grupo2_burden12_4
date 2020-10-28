#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include "include/Triangulation.h"

using namespace std;

Triangulation::Triangulation()
{
    triangles = new vector<Triangle>;
}

Triangulation::Triangulation(const char* fname)
{
    triangles = new vector<Triangle>;
    setTriangles(triangles);
    loadTriangles(fname);
}

Triangulation::~Triangulation()
{
    delete triangles;
}

vector<Triangle>* Triangulation::getTriangles() const
{
    return triangles;
}

void Triangulation::setTriangles(vector<Triangle>* triangles_)
{
    triangles = triangles_;
}

void Triangulation::loadTriangles(const char* fname)
{
    ifstream triangsFile(fname);

    if (triangsFile.fail()) {
        cout << "Triangles file cannot be opened." << endl;
        exit(1);
    }

    while (!triangsFile.eof()) {
        Point p1;
        Point p2;
        Point p3;

        triangsFile >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
        Triangle t(p1, p2, p3);
        getTriangles()->push_back(t);
    }

    triangsFile.close();
}

void Triangulation::buildTriangles(vector<Point>* nodes)
{

    for (int i = 0; i < nodes->size() - 1; i++) {
        cout << nodes->at(i).y << endl;
        for (int j = 0; j < nodes->size() - 1; j++) {

            if ((nodes->at(i).y >= nodes->at(j).y) && (nodes->at(i + 1).y >= nodes->at(j).y) && (nodes->at(i + 1).y >= nodes->at(j + 1).y)) {
                Point p1;
                p1.x = nodes->at(i).x;
                p1.y = nodes->at(j).y;

                Point p2;
                p2.x = nodes->at(i + 1).x;
                p2.y = nodes->at(j).y;

                Point p3;
                p3.x = nodes->at(i + 1).x;
                p3.y = nodes->at(j + 1).y;

                Triangle t(p1, p2, p3);
                getTriangles()->push_back(t);
            }
        }
    }
}

void Triangulation::saveFile(const char* fname)
{
    ofstream triangsFile(fname);

    if (triangsFile.fail()) {
        cout << "Triangles file cannot be saved." << endl;
        exit(1);
    }

    for (int i = 0; i < triangles->size(); i++) {
        triangsFile << getTriangles()->at(i).toTuples() << endl;
    }
    triangsFile.close();
}