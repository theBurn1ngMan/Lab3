#include "Pipe.h"

int Pipe::maxId = 0;

int Pipe::GetId()
{
	return Id;
}

void Pipe::PrintPipeStatus()
{
	setlocale(LC_ALL, "Russian");
	cout << (isRepairing ? "Трубы на ремонте" : "Работающие трубы") << endl;
}

string Pipe::GetName() const
{
	return kilometerMark;
}

int Pipe::GetDiameter() const
{
	return diameter;
}

bool Pipe::GetStatus() const
{
	return isRepairing;
}

bool Pipe::FreeConnections() const
{
	return csId1 < 1 || csId2 < 1;
}

void Pipe::Connect(const int& id1, const int& id2)
{
	csId1 = id1;
	csId2 = id2;
}

void Pipe::DeleteConnection()
{
	csId1 = 0;
	csId2 = 0;
}

void InputCorrectDiameter(int& diameter)
{
	setlocale(LC_ALL, "Russian");
	cin >> diameter;
	while ((diameter != 500 && diameter != 700 && diameter != 1000 && diameter != 1400)  || cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Ошибка! Введите значение корректно (500, 700, 1000, 1400): ";
		cin >> diameter;
	}
}

void EditPipes(vector <Pipe*>& pipes)
{
	setlocale(LC_ALL, "Russian");
	cout << endl << "Хотите поменять статус ремонта?" << endl
		<< "1. Да" << endl
		<< "2. Нет" << endl
		<< "Ваш выбор: ";
	int commandNumber;
	InputCorrectNumber(commandNumber);
	switch (commandNumber)
	{
	case 1:
		bool isRepairing;
		cout << "Трубу уже чинили? (1 - Да, 0 - Нет) ";
		InputCorrectNumberNull(isRepairing, true);

		for (auto& pipe : pipes)
		{
			pipe->isRepairing = isRepairing;
			cout << "ID: " << pipe->Id << " - ";
			pipe->PrintPipeStatus();
		}
		break;
	case 2:
		return;
	default:
		cout << "Ошибка! Введите значение корректно " << endl;
		break;
	}
}

void EditPipe(Pipe& pipe)
{
	setlocale(LC_ALL, "Russian");
	cout << "Хотите поменять статус ремонта?" << endl
		<< "1. Да" << endl
		<< "2. Нет" << endl
		<< "Ваш выбор: ";
	int commandNumber;
	InputCorrectNumber(commandNumber);
	switch (commandNumber)
	{
	case 1:
		bool isRepairing;
		cout << "Is the pipe being repaired? (1 - Yes, 0 - No) ";
		InputCorrectNumberNull(isRepairing, true);

		pipe.isRepairing = isRepairing;
		cout << "ID: " << pipe.Id << " - ";
		pipe.PrintPipeStatus();
		break;
	case 2:
		return;
	default:
		cout << "Ошибка! Введите значение корректно " << endl;
		break;
	}
}

ostream& operator<<(ostream& out, const Pipe& pipe)
{
	setlocale(LC_ALL, "Russian");
	out << endl << "Id трубы: " << pipe.Id << endl;
	out << "Километр трубопровода: " << pipe.kilometerMark << endl;
	out << "Длину труба: " << pipe.length << " km" << endl;
	out << "диаметр трубы (500, 700, 1000, 1400): " << pipe.diameter << " mm" << endl;
	if (pipe.isRepairing)
		out << "Труба на ремонте." << endl;
	else
		out << "Труба работает." << endl;
	return out;
}

istream& operator>>(istream& in, Pipe& pipe)
{
	setlocale(LC_ALL, "Russian");
	pipe.Id = ++pipe.maxId;
	cout << "Id: " << pipe.Id << endl;
	cout << "Введите километр трубопровода: ";
	in.ignore();
	getline(in, pipe.kilometerMark);
	cout << "Введите длину трубы (в километрах): ";
	InputCorrectNumber(pipe.length);
	cout << "Введите диаметр трубы (500, 700, 1000, 1400) (в милиметрах): ";
	InputCorrectDiameter(pipe.diameter);
	cout << "Трубу чмнмлм? (1 - Да, 0 - Нет) ";
	InputCorrectNumberNull(pipe.isRepairing, true);
	return in;
}

ofstream& operator<<(ofstream& fout, const Pipe& pipe)
{
	setlocale(LC_ALL, "Russian");
	fout << pipe.Id << endl;
	fout << pipe.length << endl;
	fout << pipe.kilometerMark << endl;
	fout << pipe.diameter << endl;
	fout << pipe.isRepairing << endl;
	cout << "Данные сохранены!" << endl;
	return fout;
}

ifstream& operator>>(ifstream& fin, Pipe& pipe)
{
	setlocale(LC_ALL, "Russian");
	fin >> pipe.Id;
	pipe.maxId = pipe.Id;
	fin >> pipe.length;
	fin.ignore();
	getline(fin, pipe.kilometerMark);
	fin >> pipe.diameter;
	fin >> pipe.isRepairing;
	cout << "Данные загружены!" << endl;
	return fin;
}

