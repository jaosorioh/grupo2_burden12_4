#include <iostream>
#include <cmath> 
#include <iomanip>
#include <cstdlib>
#include <fstream> 
#include "include/Triangulation.h"

using namespace std;

Triangulation::Triangulation(vector<Point> nodes_) {
	setNodes(nodes_);
}

void Triangulation::setNodes(vector<Point> nodes_)
{
	nodes = nodes_;
}

vector<Point> Triangulation::getNodes() const
{
	return nodes;
}


void Triangulation::buildTriangles()
{
	
for(int i = 0; i<nodes.size()-1; i++)
{
	for(int j = 0; j<nodes.size()-1; j++)
	{
		Point p1;
		p1.x = nodes[i].x;
		p1.y = nodes[j].y;
		
		if((nodes[i].y>=nodes[j].y) && (nodes[i+1].y>=nodes[j].y) && (nodes[i+1].y>=nodes[j+1].y))
		{			
			Point p2;
			p2.x = nodes[i+1].x;
			p2.y = nodes[j].y;
			
			Point p3;
			p3.x = nodes[i+1].x;
			p3.y = nodes[j+1].y;
			
			Triangle t(p1, p2, p3);
			
			triangles.push_back(t);
		}
	}
}

}

void Triangulation::saveFile(string triangsFname)
{

ofstream triangsFile("triangles.dat");

if ( triangsFile.fail() )      
{
      cout << "Mesh file cannot be opened" << endl;
      exit( 1 );
}

for(int i=0; i<triangles.size();i++)
{
	triangsFile << triangles[i].toTuples() << endl;
}
triangsFile.close();
}

