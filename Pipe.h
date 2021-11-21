#pragma once
#include <iostream>
#include <string>


class Pipe
{
public:
	static int MaxIDpipe;
	int pid;
	std::string pName;
	int pDiametr;
	int pLength;
	bool pInRepair;

	Pipe();

	static void EditPipe(Pipe& p);
	friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
};

