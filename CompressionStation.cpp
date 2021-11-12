#include "CompressionStation.h"
#include "utilss.h"
#include <vector>
using namespace std;

istream& operator >> (istream& in, CompressionStation& cs)
{
	cout << "Please, enter name: ";
	cin.ignore(10000, '\n');
	getline(cin, cs.name);
	cout << "Please, enter number of workshops: ";
	cs.NumberOfWorkshops = GetCorrectNumber(1,10000000);
	cout << "Please, enter number of active workshops: ";
	cs.NumberOfWorkshopsInOperation = GetCorrectNumber(0, cs.NumberOfWorkshops);
	cout << "Please, point out effiency: ";
	cs.effiency = GetCorrectNumber(1,10000000);
	return in;
}

ostream& operator << (ostream& out, const CompressionStation& cs)
{
	if (cs.NumberOfWorkshops != 0)
	{
		out << "Compression Station's name: " << cs.name << endl;
		out << "Compression Station's number of workshops: " << cs.NumberOfWorkshops << endl;
		out << "Compression Station's number of workshops in operation: " << cs.NumberOfWorkshopsInOperation << endl;
		out << "Compression Station's effiency: " << cs.effiency << endl;
	}
	return out;
}

