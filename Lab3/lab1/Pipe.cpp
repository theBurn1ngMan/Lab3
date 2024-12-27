#include "Pipe.h"

int Pipe::maxId = 0;

int Pipe::GetId()
{
	return Id;
}

void Pipe::PrintPipeStatus()
{
	setlocale(LC_ALL, "Russian");
	cout << (isRepairing ? "����� �� �������" : "���������� �����") << endl;
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
		cout << "������! ������� �������� ��������� (500, 700, 1000, 1400): ";
		cin >> diameter;
	}
}

void EditPipes(vector <Pipe*>& pipes)
{
	setlocale(LC_ALL, "Russian");
	cout << endl << "������ �������� ������ �������?" << endl
		<< "1. ��" << endl
		<< "2. ���" << endl
		<< "��� �����: ";
	int commandNumber;
	InputCorrectNumber(commandNumber);
	switch (commandNumber)
	{
	case 1:
		bool isRepairing;
		cout << "����� ��� ������? (1 - ��, 0 - ���) ";
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
		cout << "������! ������� �������� ��������� " << endl;
		break;
	}
}

void EditPipe(Pipe& pipe)
{
	setlocale(LC_ALL, "Russian");
	cout << "������ �������� ������ �������?" << endl
		<< "1. ��" << endl
		<< "2. ���" << endl
		<< "��� �����: ";
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
		cout << "������! ������� �������� ��������� " << endl;
		break;
	}
}

ostream& operator<<(ostream& out, const Pipe& pipe)
{
	setlocale(LC_ALL, "Russian");
	out << endl << "Id �����: " << pipe.Id << endl;
	out << "�������� ������������: " << pipe.kilometerMark << endl;
	out << "����� �����: " << pipe.length << " km" << endl;
	out << "������� ����� (500, 700, 1000, 1400): " << pipe.diameter << " mm" << endl;
	if (pipe.isRepairing)
		out << "����� �� �������." << endl;
	else
		out << "����� ��������." << endl;
	return out;
}

istream& operator>>(istream& in, Pipe& pipe)
{
	setlocale(LC_ALL, "Russian");
	pipe.Id = ++pipe.maxId;
	cout << "Id: " << pipe.Id << endl;
	cout << "������� �������� ������������: ";
	in.ignore();
	getline(in, pipe.kilometerMark);
	cout << "������� ����� ����� (� ����������): ";
	InputCorrectNumber(pipe.length);
	cout << "������� ������� ����� (500, 700, 1000, 1400) (� ����������): ";
	InputCorrectDiameter(pipe.diameter);
	cout << "����� ������? (1 - ��, 0 - ���) ";
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
	cout << "������ ���������!" << endl;
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
	cout << "������ ���������!" << endl;
	return fin;
}

