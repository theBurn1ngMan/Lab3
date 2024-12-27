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
	cout << "Рабтают " << activeWorkshopCount << "/" << workshopCount << " (" << GetPercentOfActiveWorkshops() << "%)" << endl;
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
		cout << "Хотите поменять число работающих КС?" << endl
			<< "1. Да" << endl
			<< "2. Нет" << endl
			<< "Your choice: ";
		InputCorrectNumber(commandNumber);
		switch (commandNumber)
		{
		case 1:
			cout << "Введите число работающих КС: ";
			InputCorrectNumber(compressorStation.activeWorkshopCount, true);
			while (compressorStation.activeWorkshopCount > compressorStation.workshopCount)
			{
				cout << "Ошибка! Число активных не может превышать число всех" << endl
					<< "Число всех КС " << compressorStation.workshopCount << endl
					<< "Введите число: ";
				InputCorrectNumber(compressorStation.activeWorkshopCount, true);
			}
			cout << "ID: " << compressorStation.Id << " - ";
			compressorStation.PrintWorkshopStatus();
			return;
		case 2:
			return;
		default:
			cout << "Ошибка! Введите правильно: " << endl;
			break;
		}
	}
}

void EditCompressorStations(vector <CompressorStation*>& compressorStations)
{
	setlocale(LC_ALL, "Russian");
	cout << endl << "Хотите сменить число активных станций?" << endl
		<< "1. Да" << endl
		<< "2. Нет" << endl
		<< "Ваш выбор: ";
	int commandNumber;
	InputCorrectNumber(commandNumber);
	switch (commandNumber)
	{
	case 1:
		cout << "Ведите от 0 до 100 процкнт активных станций: ";
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
		cout << "Ошибка! Введите правильно: " << endl;
		break;
	}
}

ostream& operator<<(ostream& out, const CompressorStation& CS)
{
	setlocale(LC_ALL, "Russian");
	out << endl << "КС ID: " << CS.Id << endl;
	CS.PrintWorkshopStatus();
	out << "Число активных станций: " << CS.activeWorkshopCount << endl;
	out << "Эффективность: " << CS.efficiency << endl << endl;
	return out;
}

istream& operator>>(istream& in, CompressorStation& CS)
{
	setlocale(LC_ALL, "Russian");
	CS.Id = ++CS.maxId;
	cout << "Id: " << CS.Id << endl;
	cout << "Введите название КС: ";
	in.ignore();
	getline(in, CS.name);
	cout << "Введите чимло станций: ";
	InputCorrectNumber(CS.workshopCount);
	cout << "Введите число активных станций: ";
	InputCorrectNumber(CS.activeWorkshopCount, true);
	while (CS.workshopCount < CS.activeWorkshopCount)
	{
		cout << "Ошибка! Число активных не может превышать число всех" << endl
			<< "Ошибка! Введите правильно: ";
		InputCorrectNumber(CS.activeWorkshopCount, true);
	}
	cout << "Enter efficiency from 1 to 100: ";
	InputCorrectNumber(CS.efficiency, true);
	while (!(CS.efficiency >= 1 && CS.efficiency <= 100))
	{
		cout << "Ошибка! Введите правильно: ";
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
	cout << "Данный о КС сохранены!" << endl;
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
	cout << "Данные о КС загружены!" << endl;
	return fin;
}