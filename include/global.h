#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>
#include <cmath>

using namespace std;

struct Point{
	double x;
	double y;
	string toStr()
	{
		string s = std::to_string(x) + " " + std::to_string(y) ;
		return s;
	}
	double length()
	{
		return pow(x*x + y*y, 0.5);
	}
};

struct Triangle{

	Triangle(Point coord1_, Point coord2_, Point coord3_)
	{
		coord1 = coord1_;
		coord2 = coord2_;
		coord3 = coord3_;
	}
	Point coord1;
	Point coord2;
	Point coord3;
	
	string toTuples()
	{
		string s = coord1.toStr() + " " + coord2.toStr() + " " + coord3.toStr();
		return s;
	}

};
#endif
