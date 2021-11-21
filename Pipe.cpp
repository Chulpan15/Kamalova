#include "Pipe.h"
#include "utilss.h"
#include <unordered_map>

using namespace std;

int Pipe::MaxIDpipe = 0;

Pipe::Pipe()
{
	pid = ++ MaxIDpipe;
}


istream& operator >> (istream& in, Pipe& p)
{
	cout << "Please, enter name: ";
	cin.ignore(10000, '\n');
	getline(cin, p.pName);
	cout << "Please, enter diametr: ";
	p.pDiametr = GetCorrectNumber(1,10000000);
	cout << "Please, enter length: ";
	p.pLength = GetCorrectNumber(1,10000000);
	cout << "Is pipe in repair? (1 - Yes and 0 - No) ";
	p.pInRepair = GetCorrectNumber(0, 1);
	return in;
}

ostream& operator << (ostream& out, const Pipe& p)
{
	if (p.pDiametr != 0)
	{
		out << "Pipe's identificator: " << p.pid << endl;
		out << "Pipe's name: " << p.pName << endl;
		out << "Pipe's diametr: " << p.pDiametr << endl;
		out << "Pipe's length: " << p.pLength << endl;
		if (p.pInRepair == 1)
		{
			out << "Pipe does not work" << endl;
		}
		if (p.pInRepair == 0)
		{
			out << "Pipe works" << endl;
		}
	}
	return out;
}


void Pipe::EditPipe(Pipe& p)
{
  p.pInRepair = !p.pInRepair;	
}
