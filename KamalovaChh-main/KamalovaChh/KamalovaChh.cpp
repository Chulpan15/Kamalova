#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include <vector>

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
		<< "  0. Выход" << endl
		<< "  Выберите действие: ";
}

int GetCorrectNumber(int min=0, int max= 10000000)
{
	int x;
	while((cin >> x).fail() || x<min || x>max)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Please, type number (" << min << "-" << max << "): ";
	}
	return x;
}

struct Pipe
{
	int id;
	string name;
	int diametr;
	int length;
	bool InRepair = true;
};

struct CompressionStation
{
	int id;
    string name;
	int NumberOfWorkshops;
	int NumberOfWorkshopsInOperation;
	int effiency;
};


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

istream& operator >> (istream& in, Pipe& p)
{
	cout << "Please, enter name: ";
	cin.ignore(10000, '\n');
	getline(cin, p.name);
	cout << "Please, enter diametr: ";
	p.diametr = GetCorrectNumber();
	cout << "Please, enter length: ";
	p.length = GetCorrectNumber();
	cout << "Is pipe in repair? (1 - Yes and 0 - No) ";
	p.InRepair = GetCorrectNumber(0,1);
	return in;
}

istream& operator >> (istream& in, CompressionStation& cs)
{
	cout << "Please, enter name: ";
	cin.ignore(10000, '\n');
	getline(cin, cs.name);
	cout << "Please, enter number of workshops: ";
	cs.NumberOfWorkshops = GetCorrectNumber();
	cout << "Please, enter number of active workshops: ";
	cs.NumberOfWorkshopsInOperation = GetCorrectNumber(0,cs.NumberOfWorkshops);
	cout << "Please, point out effiency: ";
	cs.effiency = GetCorrectNumber();
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

Pipe& SelectPipe(vector<Pipe>& g)
{
		cout << "Enter index: ";
		unsigned int index = GetCorrectNumber(1u, g.size());
		return g[index - 1];
}

CompressionStation& SelectCompressionStation(vector<CompressionStation>& gr)
{
		cout << "Enter index: ";
		unsigned int index = GetCorrectNumber(1u, gr.size());
		return gr[index - 1];
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

		switch (GetCorrectNumber(0, 7))
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
			cout << "  " << endl;
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
			//jjjuytgh
			fileoutt.open("data.txt", ios::out);
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
			filein.open("data.txt", ios::in);
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

		default:
		{
			cout << "Неправильно выбран пункт меню, попробуйте снова" << endl;
		}
      }
	}
};
