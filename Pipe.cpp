#include "Pipe.h"
#include "utilss.h"

using namespace std;

int Pipe::MaxIDPipe = 0;


int Pipe::GetId() const
{
	return id;
}

void Pipe::SetId()
{
	id = ++MaxIDPipe;
}

istream& operator >> (istream& in, Pipe& p)
{
	p.SetId();
	cout << "Please, enter name: ";
	cin.ignore(10000, '\n');
	getline(cin, p.pName);
	cout << "Please, enter diametr: ";
	p.pDiametr = GetCorrectNumber(1,10000000);
	cout << "Please, enter length: ";
	p.pLength = GetCorrectNumber(1,10000000);
	cout << "Is pipe in repair? (1 - Yes and 0 - No) ";
	p.pInRepair = GetCorrectNumber(0, 1);
	p.CSout = 0;
	p.CSin = 0;
	return in;
}

ostream& operator << (ostream& out, const Pipe& p)
{
	if (p.pDiametr != 0)
	{
		out << "Pipe's identificator: " << p.id << endl;
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

std::ifstream& operator >> (std::ifstream& in, Pipe& p)
{
	in >> p.id;
	in >> p.pName;
	in >> p.pDiametr;
	in >> p.pLength;
	in >> p.pInRepair;
	in >> p.CSout;
	in >> p.CSin;
	return in;
}

std::ofstream& operator << (std::ofstream& out, const Pipe& p)
{
	out << p.GetId() << endl
		<< p.pName << endl
		<< p.pDiametr << endl
		<< p.pLength << endl
		<< p.pInRepair << endl
	    << p.CSout << endl
		<< p.CSin << endl;

	return out;
}


 void Pipe::EditPipe()
{
  pInRepair = !pInRepair;	
}

