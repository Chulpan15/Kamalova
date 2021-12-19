#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>
#include <tuple>
#include "Pipe.h"
#include "CompressionStation.h"
#include "utilss.h"
#include <unordered_map>
#include <set>

using namespace std;


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
	    << " 10. Пакетное редактирование труб" << endl
	    << " 11. Газотранспортная система" << endl
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
		cout << "Ошибка. Компрессорной станции с таким идентификатором не существует.";
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
	cout << "Введите идентификатор КС: ";
    int id = GetCorrectNumber<uint64_t>(1, cs.size());
	if (cs.count(id) != 0)
	{
		cs.erase(id);
	}
	else
		cout << "Произошла ошибка. Не существует КС с таким идентификатором" << endl;;
}

void Load(ifstream& filein, unordered_map<int, Pipe>& group, unordered_map<int, CompressionStation>& groupp)
{
	Pipe p;
	CompressionStation cs;
	int i = 0;
	int kol_pipe;
	filein >> kol_pipe;
	while (kol_pipe != 0)
	{
		filein >> p;
		for (auto& [id, pipe] : group)
		{
			if (p.GetId() == id)
				i++;
		}
		if (i == 0)
		{
			p.MaxIDPipe++;
			group.emplace(p.MaxIDPipe, p);
		}
		else
			i = 0;
		--kol_pipe;
	}

	int j = 0;
	int kol_cs;
	filein >> kol_cs;
	while (kol_cs != 0)
	{
		filein >> cs;
		for (auto& [id, compst] : groupp)
		{
			if (cs.GetID() == id)
				j++;
		}
		if (j == 0)
		{
			cs.MaxIDCs++;
			groupp.emplace(cs.MaxIDCs, cs);
		}
		else
			j = 0;
		--kol_cs;
	}
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
	for (auto& p : group)
	{
		if (f(p.second, param))
			res.push_back(p.first);
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
	return ((cs.GetNumberOfWorkshops() - cs.GetNumberOfWorkshopsInOperation()) / cs.GetNumberOfWorkshops()) * 100 >= param;
}

template<typename Tcs>
vector<int> FindCsByFilter(const unordered_map<int, CompressionStation>& groupp, Filterr<Tcs> f, Tcs param)
{
	vector <int> res;
	int i = 0;
	for (auto& cs : groupp)
	{
		if (f(cs.second, param))
			res.push_back(cs.first);
	}

	return res;
}

void PacketEditPipe(unordered_map<int, Pipe>& group)
{
			cout << " Редактировать все трубы или определенные? (1 - все/2 - определенные): ";
			if (GetCorrectNumber(1, 2) == 1)
			{
				for (auto& p : group)
					SelectPipe(group).EditPipe();
			}
			else
			{
				set <int> vectID;
				while (true)
				{
					cout << "Введите идентификатор трубы, чтобы отредактировать или 0, чтобы завершить: ";
					int i = GetCorrectNumber(0, Pipe::MaxIDPipe);
					if (i)
					{
						if (group.count(i) == 0)
							cout << "Произошла ошибка. Труба с таким идентификатором отсутсвует.";
						else
							vectID.insert(i);
					}
					else
						break;

				}
				for (int i : vectID)
					group[i].pInRepair = !group[i].pInRepair;
			}
}

void PacketDeletePipe(unordered_map<int, Pipe>& p)
{
	    cout << "Удалить трубы, которые (0 - работающие ; 1 - находятся в ремонте):  ";
		int status = GetCorrectNumber(0, 1);
		vector <int> vectID = FindPipeByFilter(p, CheckByRepairp, status);
		for (auto& id : vectID)
			cout << id << p[id] << endl;

		cout << "Удалить все трубы - 1 / удалить определенные - 2: ";
		if (GetCorrectNumber(1, 2) == 1)
		{
			for (auto& id : vectID)
				p.erase(id);
		}
		else
		{
			while (true)
			{
				int i = 0;
				int pid;
				cout << "Введите идентификатор трубы, чтобы удалить или 0, чтобы завершить операцию: ";
				cin >> pid;
				if (pid)
				{
					for (auto& id : vectID)
					{
						if (pid == id)
						{
							i++;
						}
					}
					if (i == 0)
					{
						cout << "Ошибка!";
					}
					else
					{
						p.erase(pid);
					}
				}
				else
					break;
			}
		}
	
}

void Connect(unordered_map<int, Pipe>& group,unordered_map<int, CompressionStation>& groupp)
{
	if ((group.size() > 0) && (groupp.size() > 0))
	{
		int IDpipeConnect = Proverka(group, "Введите id трубы, чтобы прикрепить: ", "Ошибка! Попробуйте снова!", 1, Pipe::MaxIDPipe, 0);
		if (group[IDpipeConnect].CSin == 0 && group[IDpipeConnect].CSout == 0)
		{
			int IDout = Proverka(groupp, "Введите id Компрессорной станции, из которой будет выходить труба: ", "Ошибка! Попробуйте снова!", 1, CompressionStation::MaxIDCs, 0);
			int IDin = Proverka(groupp, "Введите id Компрессорной станции, в которую будет входить труба: ", "Ошибка! Попробуйте снова!", 1, CompressionStation::MaxIDCs, IDout);
			group[IDpipeConnect].CSin = IDin;
			group[IDpipeConnect].CSout = IDout;
			groupp[IDin].STzaxoda += 1;
			groupp[IDout].STisxoda += 1;
		}
		else
		{
			cout << "Труба уже подключена";
		}
	}
	else
	{
		cout << "Недостаточно труб и компрессорных станций, чтобы создать подключение";
	}
}

void PrintSystem(unordered_map<int, Pipe>& group)
{
	for (auto& p : group)
	{
		if (p.second.CSin > 0 && p.second.CSout> 0)
		{
			cout << "\nPipe's ID: " << p.first << endl;
			cout << "Pipe is connected" << endl;
			cout << "CS's IDout: " << p.second.CSout << endl;
			cout << "CS's IDin: " << p.second.CSin << endl;
		}
		else
		{
			cout << "\nPipe's ID: " << p.first << endl;
			cout << "Pipe isn't connected" << endl;
		}
	}
}

void Disconnect(unordered_map<int, Pipe>& group, unordered_map<int, CompressionStation>& groupp)
{
	if (group.size() > 0)
	{
		int IDpipeDisconnect = Proverka(group, "Введите id трубы, которую хотите отсоединить: ", "Произошла ошибка, попробуйте снова!", 1, Pipe::MaxIDPipe, 0);
		if (group[IDpipeDisconnect].CSin == 0)
		{
			cout << "Труба не подключена" << endl;
		}
		else
		{
			group[IDpipeDisconnect].CSin = 0;
			group[IDpipeDisconnect].CSout = 0;
			groupp[group[IDpipeDisconnect].CSin].STzaxoda -= 1;
			groupp[group[IDpipeDisconnect].CSout].STisxoda -= 1;
		}
	}
	else
		cout << "Отсутствует труба";
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	unordered_map <int, Pipe> group = {};
	unordered_map <int, CompressionStation> groupp = {};
	Pipe p;
	CompressionStation cs;

 	while (1)
	{
		Menu();

		switch (GetCorrectNumber(0, 11))
		{
		case 0:
		{
			return 0;
		}

		case 1:
		{
			cin >> p;
			group.emplace(p.MaxIDPipe, p);
			cout << "  " << endl;
			break;
		}

		case 2:
		 {
			cout << "  " << endl;
			cin >> cs;
			groupp.emplace(cs.MaxIDCs, cs);
			cout << "  " << endl;
			break;
		  }

		case 3:
		{
			cout << "  " << endl;
			if (group.size() != 0)
			{
				for (const auto& [id, p] : group)
				{
					cout << p << endl;
				}
			}
			else cout << "Нет данных по трубам" << endl;
			if (groupp.size() != 0)
			{
				for (const auto& [id, cs] : groupp)
				{
					cout << cs << endl;
				}
			}
			else
				cout << "Нет данных по компрессорным станциям" << endl;
			break;
		}

		case 4:
		{
			if (group.size() > 0)
			{
				SelectPipe(group).EditPipe();
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
				fileoutt << group.size() << endl;
				for (const auto& [id, pp] : group)
					fileoutt << pp;
				fileoutt << groupp.size() << endl;
				for (const auto& [id, c] : groupp)
					fileoutt << c;
				fileoutt.close();
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
			cout << "Введите имя файла: ";
			cin.ignore(10000, '\n');
			getline(cin, filenamee);
			filein.open(filenamee + ".txt", ios::in);

			if (filein.is_open())
			{
				Load(filein, group, groupp);
				filein.close();
			}

			else
				cout << "Произошла ошибка, не удалось открыть файл, попробуйте снова!";
			cout << "  " << endl;
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
					cin.ignore(10000, '\n');
					getline(cin,name);
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
			cout << "Хотите отредактировать трубы - 1/Хотите удалить - 2: ";
			int choice;
			choice = GetCorrectNumber(1, 2);
			if (choice == 1)
			{
				PacketEditPipe(group);
			}
			else
			{
				PacketDeletePipe(group);
			}
			break;
		}

		case 11:
		{
			cin.clear();
			system("cls");
			cout << "Вы хотите: [1] - Подсоединить КС к трубам; [2] - показать существующие соединения; [3] - отсоединить КС от труб: ";
			switch (GetCorrectNumber(1, 3))
			{
			case 1:
			{
				cin.clear();
				system("cls");
				Connect(group, groupp);
				break;
			}
			case 2:
			{
				cin.clear();
				system("cls");
				PrintSystem(group);
				break;
			}
			case 3:
			{
				cin.clear();
				system("cls");
				Disconnect(group, groupp);
				break;
			}
			}
			break;
		}

		default:
		{
			cout << "Неправильно выбран пункт меню, попробуйте снова" << endl;
		}
      }
	}
};
