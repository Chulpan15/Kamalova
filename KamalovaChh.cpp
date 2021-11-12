#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include <vector>
#include <sstream>
#include "Pipe.h"
#include "CompressionStation.h"
#include "utilss.h"
#include <cstdint>
#include "stdint.h"
#include "inttypes.h"
using namespace std;

void Menu()
{
 cout   << "  1. �������� �����" << endl
		<< "  2. �������� ��" << endl
		<< "  3. �������� ���� ��������" << endl
		<< "  4. ������������� �����" << endl
		<< "  5. ������������� ��" << endl
		<< "  6. ���������" << endl
		<< "  7. ���������" << endl
	    << "  8. ����� ����� ��� ��" << endl
	    << "  9. ������� ����� ��� ��" << endl
		<< "  0. �����" << endl
		<< "  �������� ��������: ";
}

//int GetCorrectNumber(int min=0, int max= 10000000)
//{
//	int x;
//	while((cin >> x).fail() || x<min || x>max)
//	{
//		cin.clear();
//		cin.ignore(10000, '\n');
//		cout << "Please, type number (" << min << "-" << max << "): ";
//	}
//	return x;
//}

//struct Pipe
//{
//	int id;
//	string name;
//	int diametr;
//	int length;
//	bool InRepair = true;
//};

//struct CompressionStation
//{
//	int id;
//    string name;
//	int NumberOfWorkshops;
//	int NumberOfWorkshopsInOperation;
//	int effiency;
//};


Pipe LoadPipe(ifstream& filein)
{
	Pipe p;
	string text;
	filein >> text;
	if (text == "Pipe")
	{
		filein.ignore(10000, '\n');
		getline(filein, p.name);
		filein >> p.diametr;
		filein >> p.length;
		filein >> p.InRepair;
	}
	return p;
}

CompressionStation LoadCompSt(ifstream& filein)
{
	CompressionStation cs;
	string text;
	filein >> text;
	if (text == "CompressionStation")
	{
	  filein.ignore(10000, '\n');
	  getline(filein, cs.name);
	  filein >> cs.NumberOfWorkshops;
	  filein >> cs.NumberOfWorkshopsInOperation;
	  filein >> cs.effiency;
	}
	return cs;
}
void PrintPipeCompSt(const Pipe& p, const CompressionStation& cs)
{
	if (p.diametr != 0)
	{
		cout << "Pipe's name: " << p.name << endl;
		cout << "Pipe's diametr: " << p.diametr << endl;
		cout << "Pipe's length: " << p.length << endl;
		if (p.InRepair == 1)
		{
			cout << "Pipe does not work" << endl;
		}
		if (p.InRepair == 0)
		{
			cout << "Pipe works" << endl;
		}
	}
	if (cs.NumberOfWorkshops != 0)
	{
		cout << "Compression Station's name: " << cs.name << endl;
		cout << "Compression Station's number of workshops: " << cs.NumberOfWorkshops << endl;
		cout << "Compression Station's number of workshops in operation: " << cs.NumberOfWorkshopsInOperation << endl;
		cout << "Compression Station's effiency: " << cs.effiency << endl;
	}
}

void EditPipe(Pipe &p)
{
	p.InRepair = !p.InRepair;
}

void SavePipeCompSt(ofstream& fileoutt, const Pipe& p, const CompressionStation& cs)
{
	if (p.diametr != 0)
	{
		fileoutt << "Pipe" << endl;
		fileoutt << p.name << endl;
		fileoutt << p.diametr << endl;
		fileoutt << p.length << endl;
		fileoutt << p.InRepair << endl;
	}
	if (cs.NumberOfWorkshops != 0)
	{
		fileoutt << "CompressionStation" << endl;
		fileoutt << cs.name << endl;
		fileoutt << cs.NumberOfWorkshops << endl;
		fileoutt << cs.NumberOfWorkshopsInOperation << endl;
		fileoutt << cs.effiency << endl;
	}
}

void EditCompressionStation(CompressionStation& cs)
{
	cout << "�������� ��� ��� ���������� ���� ����������? (1 - ��������/ 2 - ����������):  ";
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
	cout << "�������������� ����������";
}

void DeletePipe(vector<Pipe>& p)
{
	cout << "������� ������ �����: ";
	 int index = GetCorrectNumber<uint64_t>(1, p.size());
	auto i = p.cbegin();
	p.erase(i + index - 1);

}

void DeleteCompSt(vector<CompressionStation>& cs)
{
	cout << "������� ������ ��: ";
	int index = GetCorrectNumber<uint64_t>(1u, cs.size());
	auto i = cs.cbegin();
	cs.erase(i + index - 1);
}
//istream& operator >> (istream& in, Pipe& p)
//{
//	cout << "Please, enter name: ";
//	cin.ignore(10000, '\n');
//	getline(cin, p.name);
//	cout << "Please, enter diametr: ";
//	p.diametr = GetCorrectNumber();
//	cout << "Please, enter length: ";
//	p.length = GetCorrectNumber();
//	cout << "Is pipe in repair? (1 - Yes and 0 - No) ";
//	p.InRepair = GetCorrectNumber(0,1);
//	return in;
//}
//
//istream& operator >> (istream& in, CompressionStation& cs)
//{
//	cout << "Please, enter name: ";
//	cin.ignore(10000, '\n');
//	getline(cin, cs.name);
//	cout << "Please, enter number of workshops: ";
//	cs.NumberOfWorkshops = GetCorrectNumber();
//	cout << "Please, enter number of active workshops: ";
//	cs.NumberOfWorkshopsInOperation = GetCorrectNumber(0,cs.NumberOfWorkshops);
//	cout << "Please, point out effiency: ";
//	cs.effiency = GetCorrectNumber();
//	return in;
//}
//
//ostream& operator << (ostream& out, const Pipe& p)
//{
//	if (p.diametr != 0)
//	{
//		out << "Pipe's name: " << p.name << endl;
//		out << "Pipe's diametr: " << p.diametr << endl;
//		out << "Pipe's length: " << p.length << endl;
//		if (p.InRepair == 1)
//		{
//			out << "Pipe does not work" << endl;
//		}
//		if (p.InRepair == 0)
//		{
//			out << "Pipe works" << endl;
//		}
//	}
//	return out;
//}
//
//ostream& operator << (ostream& out, const CompressionStation& cs)
//{
//	if (cs.NumberOfWorkshops != 0)
//	{
//		out << "Compression Station's name: " << cs.name << endl;
//		out << "Compression Station's number of workshops: " << cs.NumberOfWorkshops << endl;
//		out << "Compression Station's number of workshops in operation: " << cs.NumberOfWorkshopsInOperation << endl;
//		out << "Compression Station's effiency: " << cs.effiency << endl;
//	}
//	return out;
//}

Pipe& SelectPipe(vector<Pipe>& p)
{
		cout << "Enter index: ";
	    unsigned int index = GetCorrectNumber<uint64_t>(1, p.size());
		return p[index - 1];
}

CompressionStation& SelectCompressionStation(vector<CompressionStation>& cs)
{
		cout << "Enter index: ";
	    unsigned int index = GetCorrectNumber<uint64_t>(1, cs.size());
		return cs[index - 1];
}

template <typename Tp>
using Filter = bool(*)(const Pipe& p, Tp param);

bool CheckByNamep(const Pipe& p, string param)
{
	return p.name == param;
}
bool CheckByRepairp(const Pipe& p, int param)
{
	return p.InRepair == param;
}

template <typename Tp>
vector<int> FindPipeByFilter(const vector<Pipe>& group, Filter<Tp> f, Tp param)
{
	vector <int> res;
	int i = 0;
	for (auto& p : group)
	{
		if (f(p, param))
			res.push_back(i);
		i++;
	}

	return res;
}

template <typename Tcs>
using Filterr = bool(*)(const CompressionStation& cs, Tcs param);

bool CheckByNameCs(const CompressionStation& cs, string param)
{
	return cs.name == param;
}

bool CheckByNumberOfWorkshops(const CompressionStation& cs, double param)
{
	double procent;
	procent = int(cs.NumberOfWorkshopsInOperation*100/ cs.NumberOfWorkshops*100)/100;
	double itog;
	itog = 100 - procent;
	return itog == param;
}

template<typename Tcs>
vector<int> FindCsByFilter(const vector<CompressionStation>& groupp, Filterr<Tcs> f, Tcs param)
{
	vector <int> res;
	int i = 0;
	for (auto& cs : groupp)
	{
		if (f(cs, param))
			res.push_back(i);
		i++;
	}

	return res;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Pipe p = {};
	CompressionStation cs = {};
	vector <Pipe> group;
	vector <CompressionStation> groupp;
 	while (1)
	{
		Menu();

		switch (GetCorrectNumber(0, 9))
		{
		case 0:
		{
			return 0;
		}

		case 1:
		{
			Pipe p;
			cin >> p;
			group.push_back(p);
			cout << "  " << endl;
			break;
		}

		case 2:
		 {
			cout << "  " << endl;
			CompressionStation cs;
			cin >> cs;
			groupp.push_back(cs);
			cout << "  " << endl;
			break;
		  }

		case 3:
		{
			cout << "  " << endl;
			for (auto& p:group)
			cout << p<< endl;;
			cout << "  " << endl;
			for (auto& cs: groupp)
			cout << cs << endl;;
			break;
		}

		case 4:
		{
			EditPipe(SelectPipe(group));
			cout << " " << endl;
			break;
		}

		case 5:
		{
			EditCompressionStation(SelectCompressionStation(groupp));
			cout << " " << endl;
			break;
		}

		case 6:
		 {  cout << "  " << endl;
			ofstream fileoutt;
			string filename;
			cout << "������� ��� �����: ";
			cin.ignore(10000, '\n');
			getline(cin, filename);
			fileoutt.open(filename + ".txt", ios::out);
			if (fileoutt.is_open())
			{
					fileoutt << group.size() << endl;
					for (Pipe p : group)
						SavePipeCompSt(fileoutt, p, cs);
					fileoutt << groupp.size() << endl;
					for (CompressionStation cs : groupp)
						SavePipeCompSt(fileoutt, p, cs);
					fileoutt.close();
			}
			break;
	     }

	    case 7:
	     {
			cout << "  " << endl;
			ifstream filein;
			string filenamee;
			cout << "������� ��� �����: ";
			cin.ignore(10000, '\n');
			getline(cin, filenamee);
			filein.open(filenamee + ".txt", ios::in);
			if (filein.is_open())
			{
			  int count;
			  filein >> count;
			  while(count--)
			  group.push_back(LoadPipe(filein));
			  filein >> count;
			  while (count--)
			  groupp.push_back(LoadCompSt(filein));
			  filein.close();
			  cout << "  "<< endl;
			}
			break;
	     }

		case 8:
		{
			cout << "  " << endl;
			cout << "�� ������ ����� ����� ��� ��? (1 - �����/ 0 - ��) ";
			int choose;
			choose = GetCorrectNumber(0, 1);
			if (choose == 1)
			{
				cout << "����� ����� �� �������� ��� �� �������� '� �������'? (1 - �� ��������/ 0 - �� �������� '� �������') ";
				int choice;
				choice = GetCorrectNumber(0, 1);
				if (choice == 1)
				{
					string name;
					cout << "������� ���: " << name;
					cin >> name;
					cout << "  " << endl;
					{
						for (int i : FindPipeByFilter(group, CheckByNamep, name))
							cout << group[i];
					}
				}
				if (choice == 0)
				{
					int repair;
					cout << "������� �����, ������� � �������? (1 - ��/ 0 - ���) ";
					cin >> repair;
					cout << "  " << endl;
					{
						for (int i : FindPipeByFilter(group, CheckByRepairp, repair))
							cout << group[i];
					}
				}
			}

			if (choose == 0)
			{
				cout << "����� �� �� �������� ��� �� �������� ����������������� �����? (1 - �� ��������/ 0 - �� �����) ";
				int decision;
				decision = GetCorrectNumber(0, 1);
				if (decision == 1)
			 {
				string name;
				cout << "������� ���: " << name;
				cin >> name;
				for (int i : FindCsByFilter(groupp, CheckByNameCs, name))
					cout << groupp[i];
			 }
				if (decision == 0)
				{
					double cexa = 0;
					cout << "������� ������� ����������������� �����: " << cexa;
					cin >> cexa;
					cexa = int(cexa * 100) / 100;
					for (int i : FindCsByFilter(groupp, CheckByNumberOfWorkshops, cexa))
						cout << groupp[i];
				}
		    }
			cout << "  " << endl;
			break;
			cout << "  " << endl;
		}
		case 9:
		{
			int vybor;
			cout << "�� ������ ������� ����� ��� ��? (1 - �����/0 - ��) ";
			cin >> vybor;
			if (vybor == 1)
			{
				if (group.size() > 0)
				{
					DeletePipe(group);
				}
				else cout << "��������� ���� ���. ������� �����" << endl;
			}
			if (vybor == 0)
			{
				if (groupp.size() > 0)
				{
					DeleteCompSt(groupp);
				}
				else cout << "��������� ������������� ������� ���. ������� ������������� �������" << endl;
			}

			break;
		}

		default:
		{
			cout << "����������� ������ ����� ����, ���������� �����" << endl;
		}
      }
	}
};
