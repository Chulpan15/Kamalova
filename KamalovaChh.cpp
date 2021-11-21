#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include <vector>
#include <tuple>
#include "Pipe.h"
#include "CompressionStation.h"
#include "utilss.h"
#include <unordered_map>

using namespace std;

int pid = 1;
int csid = 1;

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
	    << "  10. �������� �������������� ����" << endl
		<< "  0. �����" << endl
		<< "  �������� ��������: ";
}

Pipe& SelectPipe(unordered_map<int, Pipe>& p)
{
	cout << "������� ������������� �����: ";
	int id = GetCorrectNumber<uint64_t>(1, p.size());
	if (p.count(id) == 0)
		cout << "������. ����� � ����� ��������������� �� ����������.";
	else
		return p[id];
}

CompressionStation& SelectCompSt(unordered_map<int, CompressionStation>& cs)
{
	cout << "������� ������������� �����: ";
	int id = GetCorrectNumber<uint64_t>(1, cs.size());
	if (cs.count(id) == 0)
		cout << "������. ����� � ����� ��������������� �� ����������.";
	else
		return cs[id];
}

void DeletePipe(unordered_map<int, Pipe>& p)
{
	cout << "������� ������������� �����: ";
	int id = GetCorrectNumber<uint64_t>(1, p.size());
	if (p.count(id) != 0)
	{
		p.erase(id);
	}
	else
		cout << "��������� ������. �� ���������� ����� � ����� ���������������" << endl;;
}

void DeleteCompSt(unordered_map<int, CompressionStation>& cs)
{
	cout << "������� ������ ��: ";
    int id = GetCorrectNumber<uint64_t>(1, cs.size());
	if (cs.count(id) != 0)
	{
		cs.erase(id);
	}
	else
		cout << "��������� ������. �� ���������� �� � ����� ���������������" << endl;;
}

void SavePipe(ofstream& fileoutt, const Pipe& p)
{
	if (p.pDiametr != 0)
	{
		fileoutt << "Pipe" << endl;
		fileoutt << p.MaxIDpipe << endl;
		fileoutt << p.pid << endl;
		fileoutt << p.pName << endl;
		fileoutt << p.pDiametr << endl;
		fileoutt << p.pLength << endl;
		fileoutt << p.pInRepair << endl;
	}
}

void SaveCompSt(ofstream& fileoutt, const CompressionStation& cs)
{
	if (cs.NumberOfWorkshops != 0)
	{
		fileoutt << "CompressionStation" << endl;
		fileoutt << cs.MaxIDcs << endl;
		fileoutt << cs.csid << endl;
		fileoutt << cs.name << endl;
		fileoutt << cs.NumberOfWorkshops << endl;
		fileoutt << cs.NumberOfWorkshopsInOperation << endl;
		fileoutt << cs.effiency << endl;
	}
}

Pipe LoadPipe(ifstream& filein)
{
	Pipe p;
		filein >> p.MaxIDpipe;
		filein >> p.pid;
		filein.ignore(10000, '\n');
		getline(filein, p.pName);
		filein >> p.pDiametr;
		filein >> p.pLength;
		filein >> p.pInRepair;
	return p;
}

CompressionStation LoadCompSt(ifstream& filein)
{
	CompressionStation cs;
	  filein >> cs.MaxIDcs;
	  filein >> cs.csid;
	  filein.ignore(10000, '\n');
	  getline(filein, cs.name);
	  filein >> cs.NumberOfWorkshops;
	  filein >> cs.NumberOfWorkshopsInOperation;
	  filein >> cs.effiency;
	return cs;
}

template <typename Tp>
using Filter = bool(*)(const Pipe& p, Tp param);

bool CheckByNamep(const Pipe& p, string param)
{
	return p.pName == param;
}
bool CheckByRepairp(const Pipe& p, int param)
{
	return p.pInRepair == param;
}

template <typename Tp>
vector<int> FindPipeByFilter(const unordered_map<int, Pipe>& group, Filter <Tp> f, Tp param)
{
	vector <int> res;
	int i = 0;
	for (auto& p : group)
	{
		if (f(p.second, param))
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
	double procent = ((double)cs.NumberOfWorkshops -(double)cs.NumberOfWorkshopsInOperation)*100 / cs.NumberOfWorkshops;
	return procent >= param;
}

template<typename Tcs>
vector<int> FindCsByFilter(const unordered_map<int, CompressionStation>& groupp, Filterr<Tcs> f, Tcs param)
{
	vector <int> res;
	int i = 0;
	for (auto& cs : groupp)
	{
		if (f(cs.second, param))
			res.push_back(i);
		i++;
	}

	return res;
}

void PacketEditPipe(unordered_map<int, Pipe>& group)
{
	cout << " ������������� ��� ����� ��� ������������? (1 - ���/2 - ������������): ";
	if (GetCorrectNumber(1, 2) == 1)
	{
		for (auto& p : group)
			Pipe::EditPipe(p.second);
	}
	else
	{
		vector <int> vectID;
		while (true)
		{
			cout << "������� ������������� �����, ����� ��������������� ��� 0, ����� ���������: ";
			int i = GetCorrectNumber(0, Pipe::MaxIDpipe);
			if (i)
			{
				if (group.count(i) == 0)
					cout << "��������� ������. ����� � ����� ��������������� ����������.";
				else
					vectID.push_back(i);
			}
			else
				break;


			
		}
		for (int i : vectID)
			group[i].pInRepair = !group[i].pInRepair;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	unordered_map <int, Pipe> group = {};
	unordered_map <int, CompressionStation> groupp = {};

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
			group.insert({ pid,p });
			cout << "  " << endl;
			pid++;
			break;
		}

		case 2:
		 {
			cout << "  " << endl;
			CompressionStation cs;
			cin >> cs;
			groupp.insert({ csid,cs });
			csid++;
			cout << "  " << endl;
			break;
		  }

		case 3:
		{
			cout << "  " << endl;
			if ((group.size() != 0) && (groupp.size() == 0))
			{
				for (auto& p: group)
					cout << p.second <<endl;
			}
		    if ((group.size() == 0) && (groupp.size() != 0))
			{
				for (auto& cs : groupp)
					cout << cs.second << endl;
			}
			if ((group.size() != 0) && (groupp.size() != 0))
			{
				for (auto& p : group)
					cout << p.second << endl;
				for (auto& cs : groupp)
					cout << cs.second << endl;
			}
			break;
		}

		case 4:
		{
			if (group.size() > 0)
			{
				Pipe::EditPipe(SelectPipe(group));
			}
			cout << " " << endl;
			break;
		}

		case 5:
		{
			if (groupp.size() > 0)
			{
				CompressionStation::EditCompressionStation(SelectCompSt(groupp));
			}
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
				for (auto& p : group)
					SavePipe(fileoutt, p.second);
				for (auto& cs : groupp)
					SaveCompSt(fileoutt, cs.second);
				break;
			}
			else
				cout << "��������� ������. ���� �� ��� ������, ���������� �����!" << endl;
			break;
	     }

	    case 7:
	     {
			cout << "  " << endl;
			ifstream filein;
			string filenamee;
			string text;
			cout << "������� ��� �����: ";
			cin.ignore(10000, '\n');
			getline(cin, filenamee);
			filein.open(filenamee + ".txt", ios::in);
			if (filein.is_open())
			{
				while (!filein.eof())
				{
					getline(filein, text);
					{
						if (text == "Pipe")
						group.insert({ pid,LoadPipe(filein) });
						pid++;
					}
					if (text == "CompressionStation")
					{
						groupp.insert({ csid,LoadCompSt(filein) });
						csid++;
					}
				}
				break;
				cout << "  " << endl;
			}
			else
				cout << "��������� ������, �� ������� ������� ����, ���������� �����!";
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
				cout << "  " << endl;
				if (decision == 1)
			 {
				string name;
				cout << "������� ���: " << name;
				cin >> name;
				for (int i : FindCsByFilter(groupp, CheckByNameCs, name))
					cout << groupp[i];
			 }
				cout << "  " << endl;
				if (decision == 0)
				{
					double procent;
					cout << "������� ������� ����������������� �����: ";
					cin >> procent;
					while (procent < 0.0 || procent > 100.0)
					{
						cin.clear();
						cin.ignore(10000, '\n');
						cout << "������, ���������� ��� ���. ������� ����� (0 - 100)";
					}
					for (int i : FindCsByFilter(groupp, CheckByNumberOfWorkshops, procent))
						cout << groupp[i];
					cout << "  " << endl;
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
		case 10:
		{
			PacketEditPipe(group);
		}

		default:
		{
			cout << "����������� ������ ����� ����, ���������� �����" << endl;
		}
      }
	}
};
