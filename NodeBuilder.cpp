#include <iostream>
#include <fstream> 
#include <cstdlib>

#include "include/NodeBuilder.h"

using namespace std;

NodeBuilder::NodeBuilder(int N_, double ti_, double tf_, double (*xt_)(double t), double (yt_)(double t))
{
	setN(N_);
	setTi(ti_);
	setTf(tf_);
	setXt(xt_);
	setYt(yt_);
	setDt(static_cast< double >(tf_-ti_)/(N_-1));
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


void NodeBuilder::setXt(double (*xt_)(double t))
{
	xt = xt_;
}

void NodeBuilder::setYt(double (*yt_)(double t))
{
	yt = yt_;
}

vector<Point> NodeBuilder::getNodes() const
{
	return nodes;
}

void NodeBuilder::buildNodes()
{
	double t = ti;
	for(int i = 0; i<N; i++)
	{	
		Point p;
		p.x = xt(t);
		p.y = yt(t);
		nodes.push_back(p);
		t+=dt;
	}
}

void NodeBuilder::loadNodes(string fname)
{

ifstream nodesFile(fname.c_str());

if ( nodesFile.fail() )      
{
	cout << "Nodes file cannot be opened." << endl;
	exit( 1 );
}

nodesFile.close();

Point node_act;
int i = 0;

while ( (nodesFile >> node_act.x) && (i < N))
{
	nodesFile >> node_act.y;
	nodes.push_back(node_act);
	i++;
}

nodesFile.close();

}

void NodeBuilder::saveFile(string fname)
{
	ofstream nodesFile(fname.c_str() );

	if ( nodesFile.fail() )      
	{
		cout << "Nodes file cannot be opened." << endl;
		exit( 1 );
	}

	for(int i = 0; i<nodes.size(); i++)
	{	
		nodesFile << nodes[i].toStr() <<endl;
	}

	nodesFile.close();

}
