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
 cout   << "  1. Добавить трубу" << endl
		<< "  2. Добавить КС" << endl
		<< "  3. Просмотр всех объектов" << endl
		<< "  4. Редактировать трубу" << endl
		<< "  5. Редактировать КС" << endl
		<< "  6. Сохранить" << endl
		<< "  7. Загрузить" << endl
	    << "  8. Найти трубу или кс" << endl
	    << "  9. Удалить трубу или кс" << endl
	    << "  10. Пакетное редактирование труб" << endl
		<< "  0. Выход" << endl
		<< "  Выберите действие: ";
}

Pipe& SelectPipe(unordered_map<int, Pipe>& p)
{
	cout << "Введите идентификатор трубы: ";
	int id = GetCorrectNumber<uint64_t>(1, p.size());
	if (p.count(id) == 0)
		cout << "Ошибка. Трубы с таким идентификатором не существует.";
	else
		return p[id];
}

CompressionStation& SelectCompSt(unordered_map<int, CompressionStation>& cs)
{
	cout << "Введите идентификатор трубы: ";
	int id = GetCorrectNumber<uint64_t>(1, cs.size());
	if (cs.count(id) == 0)
		cout << "Ошибка. Трубы с таким идентификатором не существует.";
	else
		return cs[id];
}

void DeletePipe(unordered_map<int, Pipe>& p)
{
	cout << "Введите идентификатор трубы: ";
	int id = GetCorrectNumber<uint64_t>(1, p.size());
	if (p.count(id) != 0)
	{
		p.erase(id);
	}
	else
		cout << "Произошла ошибка. Не существует трубы с таким идентификатором" << endl;;
}

void DeleteCompSt(unordered_map<int, CompressionStation>& cs)
{
	cout << "Введите индекс КС: ";
    int id = GetCorrectNumber<uint64_t>(1, cs.size());
	if (cs.count(id) != 0)
	{
		cs.erase(id);
	}
	else
		cout << "Произошла ошибка. Не существует КС с таким идентификатором" << endl;;
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
	cout << " Редактировать все трубы или определенные? (1 - все/2 - определенные): ";
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
			cout << "Введите идентификатор трубы, чтобы отредактировать или 0, чтобы завершить: ";
			int i = GetCorrectNumber(0, Pipe::MaxIDpipe);
			if (i)
			{
				if (group.count(i) == 0)
					cout << "Произошла ошибка. Труба с таким идентификатором отсутсвует.";
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
			cout << "Введите имя файла: ";
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
				cout << "Произошла ошибка. Файл не был открыт, попробуйте снова!" << endl;
			break;
	     }

	    case 7:
	     {
			cout << "  " << endl;
			ifstream filein;
			string filenamee;
			string text;
			cout << "Введите имя файла: ";
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
				cout << "Произошла ошибка, не удалось открыть файл, попробуйте снова!";
			break;
	     }

		case 8:
		{
			cout << "  " << endl;
			cout << "Вы хотите найти трубу или КС? (1 - Трубу/ 0 - КС) ";
			int choose;
			choose = GetCorrectNumber(0, 1);
			if (choose == 1)
			{
				cout << "Найти трубу по названию или по признаку 'в ремонте'? (1 - по названию/ 0 - по признаку 'в ремонте') ";
				int choice;
				choice = GetCorrectNumber(0, 1);
				if (choice == 1)
				{
					string name;
					cout << "Введите имя: " << name;
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
					cout << "Вывести трубы, которые в ремонте? (1 - Да/ 0 - Нет) ";
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
				cout << "Найти КС по названию или по проценту незадействованных цехов? (1 - по названию/ 0 - по цехам) ";
				int decision;
				decision = GetCorrectNumber(0, 1);
				cout << "  " << endl;
				if (decision == 1)
			 {
				string name;
				cout << "Введите имя: " << name;
				cin >> name;
				for (int i : FindCsByFilter(groupp, CheckByNameCs, name))
					cout << groupp[i];
			 }
				cout << "  " << endl;
				if (decision == 0)
				{
					double procent;
					cout << "Введите процент незадействованных цехов: ";
					cin >> procent;
					while (procent < 0.0 || procent > 100.0)
					{
						cin.clear();
						cin.ignore(10000, '\n');
						cout << "Ошибка, попробуйте еще раз. Введите число (0 - 100)";
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
			cout << "Вы хотите удалить трубу или кс? (1 - Трубу/0 - Кс) ";
			cin >> vybor;
			if (vybor == 1)
			{
				if (group.size() > 0)
				{
					DeletePipe(group);
				}
				else cout << "Доступных труб нет. Введите трубу" << endl;
			}
			if (vybor == 0)
			{
				if (groupp.size() > 0)
				{
					DeleteCompSt(groupp);
				}
				else cout << "Доступных компрессорных станций нет. Введите компрессорную станцию" << endl;
			}

			break;
		}
		case 10:
		{
			PacketEditPipe(group);
		}

		default:
		{
			cout << "Неправильно выбран пункт меню, попробуйте снова" << endl;
		}
      }
	}
};
