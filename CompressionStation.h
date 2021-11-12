#pragma once
#include <iostream>
#include <string>


class CompressionStation
{
public:
	int id;
	std::string name;
	int NumberOfWorkshops;
	int NumberOfWorkshopsInOperation;
	int effiency;

	friend std::istream& operator >> (std::istream& in, CompressionStation& cs);
	friend std::ostream& operator << (std::ostream& out, const CompressionStation& cs);
};

