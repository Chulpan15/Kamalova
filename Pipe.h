#pragma once
#include <iostream>
#include <string>
#include <fstream>


class Pipe
{
	int id;

public:
	static int MaxIDPipe;
	std::string pName;
	int pDiametr;
	int pLength;
	bool pInRepair;
	int CSout;
	int CSin;


	int GetId() const;
	void SetId();


	void EditPipe();
	friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::ifstream& operator >> (std::ifstream& in, Pipe& p);
	friend std::ofstream& operator << (std::ofstream& out, const Pipe& p);
};

