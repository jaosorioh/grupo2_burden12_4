#ifndef NODEBUILDER_H
#define NODEBUILDER_H

#include <string>
#include <vector>
#include "global.h"

using namespace std;

class NodeBuilder
{

public:
NodeBuilder(int, double, double, double (*)(double), double (*)(double));

void setN(int);
void setTi(double);
void setTf(double);
void setXt(double (*)(double));
void setYt(double (*)(double));
void setDt(double);
void buildNodes();
void saveFile(string);
void loadNodes(string);

int getN() const;
double getTi() const;
double getTf() const;
double getDt() const;
vector<Point> getNodes() const;

private: 
 int N; //number of nodes
 vector<Point> nodes;
 double ti;
 double tf;
 double dt;
 double (*xt)(double t); 
 double (*yt)(double t);

};

#endif
