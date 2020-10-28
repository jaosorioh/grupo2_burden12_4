#include <iostream>
#include <fstream>
#include <cstdlib>

#include "include/NodeBuilder.h"

using namespace std;

NodeBuilder::NodeBuilder(int N_, double ti_, double tf_, double (*xt_)(double* t), double (*yt_)(double* t))
{
    nodes = new vector<Point>;
    setN(N_);
    setTi(ti_);
    setTf(tf_);
    setXt(xt_);
    setYt(yt_);
    setDt(static_cast<double>(tf_ - ti_) / (N_ - 1));
}

NodeBuilder::NodeBuilder(const char* fname)
{
    nodes = new vector<Point>;
    loadNodes(fname);
}

void NodeBuilder::setN(int N_)
{
    N = N_;
}

int NodeBuilder::getN() const
{
    return N;
}

void NodeBuilder::setDt(double dt_)
{
    dt = dt_;
}

double NodeBuilder::getDt() const
{
    return dt;
}

void NodeBuilder::setTi(double ti_)
{
    ti = ti_;
}

double NodeBuilder::getTi() const
{
    return ti;
}

void NodeBuilder::setTf(double tf_)
{
    tf = tf_;
}

double NodeBuilder::getTf() const
{
    return tf;
}

void NodeBuilder::setXt(double (*xt_)(double* t))
{
    xt = xt_;
}

void NodeBuilder::setYt(double (*yt_)(double* t))
{
    yt = yt_;
}

void NodeBuilder::setNodes(vector<Point>* nodes_)
{
    nodes = nodes_;
}

vector<Point>* NodeBuilder::getNodes() const
{
    return nodes;
}

void NodeBuilder::buildNodes()
{
    double t = getTi();
    for (int i = 0; i < getN(); i++) {
        Point p;
        p.x = xt(&t);
        p.y = yt(&t);
        getNodes()->push_back(p);
        t += dt;
    }
}

void NodeBuilder::loadNodes(const char* fname)
{
    ifstream nodesFile(fname);

    if (nodesFile.fail()) {
        cout << "Nodes file cannot be opened." << endl;
        exit(1);
    }

    Point node_act;
    int i = 1;

    while (!nodesFile.eof()) {
        nodesFile >> node_act.x >> node_act.y;
        getNodes()->push_back(node_act);
        i++;
    }
    
    setN(i);
    nodesFile.close();
}

void NodeBuilder::saveFile(const char* fname)
{
    ofstream nodesFile(fname);

    if (nodesFile.fail()) {
        cout << "Nodes file cannot be opened." << endl;
        exit(1);
    }

    for (int i = 0; i < nodes->size(); i++) {
        nodesFile << nodes->at(i).toStr() << endl;
    }

    nodesFile.close();
}
