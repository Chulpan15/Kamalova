#pragma once
#include <iostream>
#include <string>
#include <unordered_map>


class CompressionStation
{
public:
	static int MaxIDcs;
	int csid;
	std::string name;
	int NumberOfWorkshops;
	int NumberOfWorkshopsInOperation;
	int effiency;

	CompressionStation();

	friend std::istream& operator >> (std::istream& in, CompressionStation& cs);
	friend std::ostream& operator << (std::ostream& out, const CompressionStation& cs);
	static void EditCompressionStation(CompressionStation& cs);
};

