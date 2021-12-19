#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>


class CompressionStation
{
	int id;
	int NumberOfWorkshops;
	int NumberOfWorkshopsInOperation;

public:

	std::string name;
	int effiency;
	static int MaxIDCs;
	int STisxoda = 0;
	int STzaxoda = 0;

	int GetID() const;
	void SetID();
	int GetNumberOfWorkshops() const;
	void SetNumberOfWorkshops();
	int GetNumberOfWorkshopsInOperation() const;
	void SetNumberOfWorkshopsInOperation();

	friend std::istream& operator >> (std::istream& in, CompressionStation& cs);
	friend std::ostream& operator << (std::ostream& out, const CompressionStation& cs);
	friend std::ifstream& operator >> (std::ifstream& in, CompressionStation& cs);
	friend std::ofstream& operator << (std::ofstream& out, const CompressionStation& cs);
	static void EditCompressionStation(CompressionStation& cs);
};

