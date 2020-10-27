#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <string>
#include <vector>
#include "global.h"

using namespace std;

class Triangulation
{

public:
Triangulation(vector<Point>);

void setNodes(vector<Point>);
vector<Point> getNodes() const;

void buildTriangles();
void saveFile(string);

private:
 vector<Point> nodes;
 vector<Triangle> triangles;
 
};

#endif
