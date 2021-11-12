#pragma once
#include <iostream>
#include <string>


class Pipe
{
	int id;
public:
	std::string name;
	double diametr;
	int length;
	bool InRepair = true;


	friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
};

