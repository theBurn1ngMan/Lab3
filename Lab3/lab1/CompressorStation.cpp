#include "CompressorStation.h"

int CompressorStation::maxId = 0;

int CompressorStation::GetId()
{
	return Id;
}

string CompressorStation::GetName() const
{
	return name;
}

void CompressorStation::PrintWorkshopStatus() const
{
	setlocale(LC_ALL, "Russian");
	cout << "������� " << activeWorkshopCount << "/" << workshopCount << " (" << GetPercentOfActiveWorkshops() << "%)" << endl;
}

int CompressorStation::GetPercentOfActiveWorkshops() const
{
	return activeWorkshopCount * 100 / workshopCount;
}

void EditCompressorStation(CompressorStation& compressorStation)
{
	setlocale(LC_ALL, "Russian");
	int commandNumber;
	while (true)
	{
		cout << "������ �������� ����� ���������� ��?" << endl
			<< "1. ��" << endl
			<< "2. ���" << endl
			<< "Your choice: ";
		InputCorrectNumber(commandNumber);
		switch (commandNumber)
		{
		case 1:
			cout << "������� ����� ���������� ��: ";
			InputCorrectNumber(compressorStation.activeWorkshopCount, true);
			while (compressorStation.activeWorkshopCount > compressorStation.workshopCount)
			{
				cout << "������! ����� �������� �� ����� ��������� ����� ����" << endl
					<< "����� ���� �� " << compressorStation.workshopCount << endl
					<< "������� �����: ";
				InputCorrectNumber(compressorStation.activeWorkshopCount, true);
			}
			cout << "ID: " << compressorStation.Id << " - ";
			compressorStation.PrintWorkshopStatus();
			return;
		case 2:
			return;
		default:
			cout << "������! ������� ���������: " << endl;
			break;
		}
	}
}

void EditCompressorStations(vector <CompressorStation*>& compressorStations)
{
	setlocale(LC_ALL, "Russian");
	cout << endl << "������ ������� ����� �������� �������?" << endl
		<< "1. ��" << endl
		<< "2. ���" << endl
		<< "��� �����: ";
	int commandNumber;
	InputCorrectNumber(commandNumber);
	switch (commandNumber)
	{
	case 1:
		cout << "������ �� 0 �� 100 ������� �������� �������: ";
		float percent;
		InputCorrectNumber(percent, true);

		for (auto& compressorStation : compressorStations)
		{
			compressorStation->activeWorkshopCount = round(compressorStation->workshopCount * percent / 100);
			cout << "ID: " << compressorStation->Id << " - ";
			compressorStation->PrintWorkshopStatus();
		}
		break;
	case 2:
		return;
	default:
		cout << "������! ������� ���������: " << endl;
		break;
	}
}

ostream& operator<<(ostream& out, const CompressorStation& CS)
{
	setlocale(LC_ALL, "Russian");
	out << endl << "�� ID: " << CS.Id << endl;
	CS.PrintWorkshopStatus();
	out << "����� �������� �������: " << CS.activeWorkshopCount << endl;
	out << "�������������: " << CS.efficiency << endl << endl;
	return out;
}

istream& operator>>(istream& in, CompressorStation& CS)
{
	setlocale(LC_ALL, "Russian");
	CS.Id = ++CS.maxId;
	cout << "Id: " << CS.Id << endl;
	cout << "������� �������� ��: ";
	in.ignore();
	getline(in, CS.name);
	cout << "������� ����� �������: ";
	InputCorrectNumber(CS.workshopCount);
	cout << "������� ����� �������� �������: ";
	InputCorrectNumber(CS.activeWorkshopCount, true);
	while (CS.workshopCount < CS.activeWorkshopCount)
	{
		cout << "������! ����� �������� �� ����� ��������� ����� ����" << endl
			<< "������! ������� ���������: ";
		InputCorrectNumber(CS.activeWorkshopCount, true);
	}
	cout << "Enter efficiency from 1 to 100: ";
	InputCorrectNumber(CS.efficiency, true);
	while (!(CS.efficiency >= 1 && CS.efficiency <= 100))
	{
		cout << "������! ������� ���������: ";
		InputCorrectNumber(CS.efficiency, true);
	}
	return in;
}

ofstream& operator<<(ofstream& fout, const CompressorStation& CS)
{
	setlocale(LC_ALL, "Russian");
	fout << CS.Id << endl;
	fout << CS.name << endl;
	fout << CS.workshopCount << endl;
	fout << CS.activeWorkshopCount << endl;
	fout << CS.efficiency << endl;
	cout << "������ � �� ���������!" << endl;
	return fout;
}


ifstream& operator>>(ifstream& fin, CompressorStation& CS)
{
	setlocale(LC_ALL, "Russian");
	fin >> CS.Id;
	CS.maxId = CS.Id;
	fin.ignore();
	getline(fin, CS.name);
	fin >> CS.workshopCount;
	fin >> CS.activeWorkshopCount;
	fin >> CS.efficiency;
	cout << "������ � �� ���������!" << endl;
	return fin;
}