#include "CompressionStation.h"
#include "utilss.h"
using namespace std;

int CompressionStation::MaxIDCs = 0;


int CompressionStation::GetID() const
{
	return id;
}

void CompressionStation::SetID()
{
	id = ++MaxIDCs;
}


int CompressionStation::GetNumberOfWorkshops() const
{
	return NumberOfWorkshops;
}

void CompressionStation::SetNumberOfWorkshops()
{
	NumberOfWorkshops = GetCorrectNumber(0, 10000000);
}

int CompressionStation::GetNumberOfWorkshopsInOperation() const
{
	return NumberOfWorkshopsInOperation;
}

void CompressionStation::SetNumberOfWorkshopsInOperation()
{
	NumberOfWorkshopsInOperation = GetCorrectNumber(0, 10000000);
}

istream& operator >> (istream& in, CompressionStation& cs)
{
	cs.SetID();
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
		out << "Compression Station's identificator: " << cs.id << endl;
		out << "Compression Station's name: " << cs.name << endl;
		out << "Compression Station's number of workshops: " << cs.NumberOfWorkshops << endl;
		out << "Compression Station's number of workshops in operation: " << cs.NumberOfWorkshopsInOperation << endl;
		out << "Compression Station's effiency: " << cs.effiency << endl;
	}
	return out;
}

std::ifstream& operator >> (std::ifstream& in, CompressionStation& cs)
{
	in >> cs.id;
	in >> cs.name;
	in >> cs.NumberOfWorkshops;
	in >> cs.NumberOfWorkshopsInOperation;
	in >> cs.effiency;
	return in;
}

std::ofstream& operator << (std::ofstream& out, const CompressionStation& cs)
{
	out << cs.GetID() << endl
		<< cs.name << endl
		<< cs.GetNumberOfWorkshops() << endl
		<< cs.GetNumberOfWorkshopsInOperation() << endl
		<< cs.effiency << endl;
	return out;
}



void CompressionStation::EditCompressionStation(CompressionStation& cs)
{
	cout << "Добавить цех или остановить один работающий? (1 - Добавить/ 2 - Остановить):  ";
	int parametr;
	parametr = GetCorrectNumber(1, 2);
	if (parametr == 1 && (cs.NumberOfWorkshopsInOperation < cs.NumberOfWorkshops))
	{
		cout << cs.NumberOfWorkshopsInOperation++;
		return;
	}
	if (parametr == 2 && (cs.NumberOfWorkshopsInOperation > 0))
	{
		cs.NumberOfWorkshopsInOperation--;
		return;
	}
	cout << "Редактирование невозможно";
}
