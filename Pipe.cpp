#include "Pipe.h"
#include "utilss.h"
using namespace std;


istream& operator >> (istream& in, Pipe& p)
{
	cout << "Please, enter name: ";
	cin.ignore(10000, '\n');
	getline(cin, p.name);
	cout << "Please, enter diametr: ";
	p.diametr = GetCorrectNumber(1,10000000);
	cout << "Please, enter length: ";
	p.length = GetCorrectNumber(1,10000000);
	cout << "Is pipe in repair? (1 - Yes and 0 - No) ";
	p.InRepair = GetCorrectNumber(0, 1);
	return in;
}

ostream& operator << (ostream& out, const Pipe& p)
{
	if (p.diametr != 0)
	{
		out << "Pipe's name: " << p.name << endl;
		out << "Pipe's diametr: " << p.diametr << endl;
		out << "Pipe's length: " << p.length << endl;
		if (p.InRepair == 1)
		{
			out << "Pipe does not work" << endl;
		}
		if (p.InRepair == 0)
		{
			out << "Pipe works" << endl;
		}
	}
	return out;
}

