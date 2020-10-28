#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <vector>
#include "global.h"

using namespace std;

class Triangulation {
public:
    Triangulation();
    Triangulation(const char*);
    ~Triangulation();
    vector<Triangle>* getTriangles() const;
    void setTriangles(vector<Triangle>*);
    void loadTriangles(const char*);
    void buildTriangles(vector<Point>*);
    void saveFile(const char*);

private:
    vector<Triangle>* triangles;
};

#endif
