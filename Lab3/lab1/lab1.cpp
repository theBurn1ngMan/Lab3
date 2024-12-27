#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>
#include "Utilities.h"
#include "Pipe.h"
#include "CompressorStation.h"
#include "logger.h"

using namespace std;

template <typename T>
T& SelectElement(unordered_map <int, T>& elements)
{
	setlocale(LC_ALL, "Russian");
	int Id;
	cout << "Введите число: ";
	InputCorrectNumber(Id);
	while (elements.find(Id) == elements.end())
	{
		cout << "Ошибка! число превышает число элементов" << endl
			<< "Число элементов: " << elements.size() << endl
			<< "Введите правильно: ";
		InputCorrectNumber(Id);
	}
	return elements[Id];
}

void SearchPipes(unordered_map <int, Pipe>& pipes) {
	setlocale(LC_ALL, "Russian");
	while (true)
	{
		int commandNumber;
		cout << "Какой критерий трубы вам нужен?" << endl
			<< "1. Id" << endl
			<< "2. Имя" << endl
			<< "3. Статус ремонта" << endl
			<< "4. Назад" << endl
			<< "Ваш выбор: ";
		InputCorrectNumber(commandNumber);
		switch (commandNumber)
		{
		case 1:
		{
			int id;
			cout << "Выбирите ID трубы: ";
			InputCorrectNumber(id);
			while (pipes.find(id) == pipes.end())
			{
				cout << "Ошибка! число превышает число элементов" << endl
					<< "Число элементов: " << pipes.size() << endl
					<< "Введите правильно: ";
				InputCorrectNumber(id);
			}
			int commandNumber1;
			cout << "Хотите убрать трубу?" << endl
				<< "1. Да" << endl
				<< "2. Нет" << endl
				<< "Ваш выбор: ";
			InputCorrectNumber(commandNumber1);
			switch (commandNumber1)
			{
			case 1:
			{
				pipes.erase(id);
				cout << "Вы убрали трубу " << id << endl << endl;
			}
			case 2:
				return;
			default:
				cout << "Введите правильно:" << endl;
				break;
			}
		}
		break;
		case 2:
		{
			string name;
			cout << "Name: ";
			cin.ignore();
			getline(cin, name);
			vector<Pipe*> editPipes;
			for (auto& pair : pipes) {
				if (pair.second.GetName().find(name) != string::npos)
				{
					cout << pair.second << endl;
					editPipes.push_back(&(pair.second));
				}
			}
			if (editPipes.empty())
				cout << "Pipe with this name not found." << endl;
			else
				EditPipes(editPipes);
		}
		break;
		case 3:
		{
			bool isRepairing;
			cout << "Is the pipe being repaired? (1 - Yes, 0 - No) ";
			InputCorrectNumber(isRepairing, true);

			vector<Pipe*> editPipes;
			for (auto& pair : pipes) {
				if (pair.second.GetStatus() == isRepairing)
				{
					cout << pair.second << endl;
					editPipes.push_back(&(pair.second));
				}
			}
			if (editPipes.empty())
				cout << "Pipe with this name not found." << endl;
			else
				EditPipes(editPipes);
		}
		break;
		case 4:
			return;
		default:
			cout << "Введите правильно:" << endl;
			break;
		}
	}
}

void SearchCompressorStations(unordered_map <int, CompressorStation>& compressorStations) {
	setlocale(LC_ALL, "Russian");
	while (true)
	{
		int commandNumber;
		cout << "By what criteria do you want to find a Compressor Station?" << endl
			<< "1. Id" << endl
			<< "2. Name" << endl
			<< "3. Percent of active worskshops" << endl
			<< "4. Back" << endl
			<< "Ваш выбор: ";
		InputCorrectNumber(commandNumber);
		switch (commandNumber)
		{
		case 1:
		{
			int id;
			cout << "Select ID Compressor station: ";
			InputCorrectNumber(id);
			while (compressorStations.find(id) == compressorStations.end())
			{
				cout << "Ошибка! число превышает число элементов" << endl
					<< "Число элементов: " << compressorStations.size() << endl
					<< "Введите правильно: ";
				InputCorrectNumber(id);
			}
			int commandNumber1;
			cout << "Do you want to remove the pipe?" << endl
				<< "1. Да" << endl
				<< "2. Нет" << endl
				<< "Ваш выбор: ";
			InputCorrectNumber(commandNumber1);
			switch (commandNumber1)
			{
			case 1:
			{
				compressorStations.erase(id);
				cout << "Вы убрали КС " << id << endl << endl;
			}
			case 2:
				return;
			default:
				cout << "Введите правильно:" << endl;
				break;
			}
		}
		break;
		case 2:
		{
			string name;
			cout << "Имя: ";
			cin.ignore();
			getline(cin, name);
			vector<CompressorStation*> editCompressorStations;
			for (auto& pair : compressorStations) {
				if (pair.second.GetName().find(name) != string::npos)
				{
					cout << pair.second << endl;
					editCompressorStations.push_back(&(pair.second));
				}
			}
			if (editCompressorStations.empty())
				cout << "КС с таким именем не была найдена." << endl;
			else
				EditCompressorStations(editCompressorStations);
		}
		break;
		case 3:
		{
			int percent;
			cout << "Введите процент рабочих станций (0-100) +-5%: ";
			InputCorrectNumber(percent, true);

			vector<CompressorStation*> editCompressorStations;
			for (auto& pair : compressorStations) {
				if (pair.second.GetPercentOfActiveWorkshops() > percent - 5 && pair.second.GetPercentOfActiveWorkshops() < percent + 5)
				{
					cout << pair.second << endl;
					editCompressorStations.push_back(&(pair.second));
				}
			}
			if (editCompressorStations.empty())
				cout << "КС с таким именем не была найдена" << endl;
			else
				EditCompressorStations(editCompressorStations);
		}
		break;
		case 4:
			return;
		default:
			cout << "Введите правильно:" << endl;
			break;
		}
	}
}

bool HasPipeWithConnection(const unordered_map<int, Pipe>& pipes, const int& csId1, const int& csId2) {

	bool hasPipe = false;
	for (auto& pair : pipes) {
		if ((pair.second.csId1 == csId1 && pair.second.csId2 == csId2)
			|| (pair.second.csId1 == csId2 && pair.second.csId2 == csId1))
		{
			hasPipe = true;
		}
	}
	return hasPipe;
}

void ConnectPipe(unordered_map <int, Pipe>& pipes, unordered_map <int, CompressorStation>& compressorStations)
{
	setlocale(LC_ALL, "Russian");
	cout << endl << "[ Соединение трубы и КС ]" << endl;
	int diameterPipe;
	int diameter;
	cout << "Введите диаметр: ";
	InputCorrectNumber(diameter);
	diameterPipe = diameter;
	while ((diameter != 500 && diameter != 700 && diameter != 1000 && diameter != 1400) || cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Введите правильно: (500, 700, 1000, 1400): ";
		cin >> diameter;
	}

	int connectedPipeId = 0;
	for (auto& pair : pipes) {
		if (pair.second.GetDiameter() == diameterPipe && pair.second.FreeConnections())
		{
			connectedPipeId = pair.first;
			break;
		}
	}

	Pipe* connectedPipe{};
	if (connectedPipeId == 0) // если не найдено свободных труб с нужным диаметром
	{
		bool isRunning = true;
		while (isRunning) {
			int commandNumber1;
			cout << "Трубы с таким диаметром нет." << endl
				<< "Хотите добавить трубу?" << endl
				<< "1. Да" << endl
				<< "2. Нет" << endl
				<< "Ваш выбор: ";
			InputCorrectNumber(commandNumber1);
			switch (commandNumber1)
			{
			case 1:
			{
				Pipe pipe;
				cin >> pipe;
				connectedPipe = &pipe;
				pipes.insert(make_pair(connectedPipe->GetId(), *connectedPipe));
				isRunning = false;
				return;
			}
			break;
			case 2:
				return;
			default:
				cout << "Введите правильно:" << endl;
				break;
			}
		}
	}
	else
	{
		connectedPipe = &pipes[connectedPipeId];
	}

	// запрашиваем две кс
	// соединяем трубу с двумя кс
	cout << "Введите ID первой КС: ";
	int csId1;
	InputCorrectNumber(csId1);
	while (compressorStations.find(csId1) == compressorStations.end())
	{
		cout << "Ошибка! КС с таким именем не была найдена" << endl
			<< "Введите правильно: ";
		InputCorrectNumber(csId1);
	}
	cout << "Введите ID второй КС: ";
	int csId2;
	InputCorrectNumber(csId2);
	while (compressorStations.find(csId2) == compressorStations.end()
		|| csId2 == csId1
		|| HasPipeWithConnection(pipes, csId1, csId2))
	{
		cout << "Ошибка! КС с таким именем не была найдена" << endl
			<< "Введите правильно: ";
		InputCorrectNumber(csId2);
	}
	connectedPipe->Connect(csId1, csId2);
}

vector<int> topologicalSort(unordered_map<int, Pipe>& pipes, unordered_map<int, CompressorStation>& stations) {
	vector<int> result;
	unordered_map<int, int> inDegree; // Количество входящих ребер для каждой вершины

	// Инициализация inDegree для каждой вершины
	for (auto& pipe : pipes) {
		inDegree[pipe.second.csId2]++;
	}

	// Создаем очередь для хранения вершин с нулевым inDegree
	queue<int> q;
	for (auto& station : stations) {
		if (inDegree.find(station.first) == inDegree.end()) {
			q.push(station.first);
		}
	}

	// Выполняем топологическую сортировку
	while (!q.empty()) {
		int currentStation = q.front();
		q.pop();
		result.push_back(currentStation);

		// Уменьшаем inDegree для всех соседних вершин
		for (auto& pipe : pipes) {
			if (pipe.second.csId1 == currentStation) {
				inDegree[pipe.second.csId2]--;
				if (inDegree[pipe.second.csId2] == 0) {
					q.push(pipe.second.csId2);
				}
			}
		}
	}

	return result;
}



int main()
{
	setlocale(LC_ALL, "Russian");
	unordered_map <int, Pipe> pipes = {};
	unordered_map <int, CompressorStation> compressorStations = {};
	Logger logger;
	logger.log("Начало");

	int commandNumber;
	while (true)
	{
		cout << "Меню:" << endl
			<< "0. Выйти" << endl
			<< "1. Добавить трубу" << endl
			<< "2. Добавить КС" << endl
			<< "3. Посмотреть все объекты" << endl
			<< "4. Изменить трубу" << endl
			<< "5. Изменить КС" << endl
			<< "6. Сохранить" << endl
			<< "7. Загрузить" << endl
			<< "8. Искать" << endl
			<< "9. Соединить трубу с КС" << endl
			<< "10. Посмортеть соединения" << endl
			<< "11. Удалить соединения" << endl
			<< "12. Топологическая сортировка" << endl
			<< "Ваш выбор: ";
		InputCorrectNumberNull(commandNumber);
		switch (commandNumber)
		{
		case 0:
			cout << "[ Выйти ]" << endl;
			logger.log("Exit");
			return 0;
			break;
		case 1:
		{
			cout << "[ Добавить трубу ]" << endl;

			Pipe pipe;
			cin >> pipe;
			pipes.insert(make_pair(pipe.GetId(), pipe));

			break;
		}
		case 2:
		{
			cout << "[ Добавить КС ]" << endl;

			CompressorStation CS;
			cin >> CS;
			compressorStations.insert(make_pair(CS.GetId(), CS));

			break;
		}
		case 3:

			cout << "[ Посмотреть все объекты ]" << endl;

			if (pipes.size() == 0)
				cout << "Труба не найдена." << endl;
			for (const auto& pair : pipes)
				cout << pair.second;

			if (compressorStations.size() == 0)
				cout << "КС не найдена." << endl;
			for (const auto& pair : compressorStations)
				cout << pair.second;

			break;

		case 4:
		{
			cout << "[ Изменить трубу ]" << endl;

			if (pipes.size() == 0)
				cout << "Труба не найдена." << endl;
			else {
				Pipe pipe = SelectElement(pipes);
				EditPipe(pipe);
			}

			break;
		}
		case 5:
		{
			cout << "[ Добавить активную станцию ]" << endl;
			cout << "[ Изменить КС ]" << endl;

			if (compressorStations.size() == 0)
				cout << "КС не найдена." << endl;
			else {
				CompressorStation compressorStation = SelectElement(compressorStations);
				EditCompressorStation(compressorStation);
			}

			break;
		}
		case 6:
		{
			cout << "[ Сохранить ]" << endl;

			ofstream fout;
			string fileName;
			cout << "Введите имя файла: ";
			cin.ignore();
			getline(cin, fileName);
			fout.open(fileName);
			if (!fout.is_open())
			{
				cout << "Файл не открывается!" << endl;
			}
			else
			{
				fout << pipes.size() << endl;
				for (const auto& pair : pipes)
					fout << pair.second;
				fout << compressorStations.size() << endl;
				for (const auto& pair : compressorStations)
					fout << pair.second;
			}
			fout.close();

		}
			break;

		case 7:
		{
			cout << "[ Загрузить ]" << endl;

			ifstream fin;
			string fileName;
			int input;
			cout << "Введите имя файла: ";
			cin.ignore();
			getline(cin, fileName);
			fin.open(fileName);
			if (!fin.is_open())
			{
				cout << "Файл не открывается!" << endl;
			}
			else
			{
				int pipeSize;
				fin >> pipeSize;
				if (pipeSize == 0)
					cout << "Труба не найдеена." << endl;
				while (pipeSize-- > 0)
				{
					Pipe pipe;
					fin >> pipe;
					pipes.insert(make_pair(pipe.GetId(), pipe));
				}

				int compressorStationSize;
				fin >> compressorStationSize;
				if (compressorStationSize == 0)
					cout << "КС не найдена." << endl;
				while (compressorStationSize-- > 0)
				{
					CompressorStation CS;
					fin >> CS;
					compressorStations.insert(make_pair(CS.GetId(), CS));
				}

				fin.close();
			}

		}
			break;
		case 8:
		{
			bool isRunning = true;
			while (isRunning) {
				int commandNumber1;
				cout << "[ Поиск ]" << endl
					<< "Что хотите найти?" << endl
					<< "1. Труба" << endl
					<< "2. КС" << endl
					<< "3. Назад" << endl
					<< "Ваш выбор: ";
				InputCorrectNumber(commandNumber1);
				switch (commandNumber1)
				{
				case 1:
					if (pipes.size() == 0)
						cout << "Труба не найдеена." << endl;
					else {
						cout << "[ Труба ]" << endl;
						SearchPipes(pipes);
					}
					break;
				case 2:
					if (compressorStations.size() == 0)
						cout << "КС не найдена." << endl;
					else {
						cout << "[ КС ]" << endl;
						SearchCompressorStations(compressorStations);
					}
					break;
				case 3:
					isRunning = false;
					break;
				default:
					cout << "Введите правильно:" << endl;
					break;
				}

			}
		}
			break;
		case 9:
		{

			if (compressorStations.size() < 2)
				cout << "КС меньше двух." << endl;
			else
				ConnectPipe(pipes, compressorStations);

		}
		break;
		case 10:
		{
			cout << "[ Посмортеть связи ]" << endl;

			if (pipes.size() == 0)
				cout << "Труба не найдена." << endl;
			if (compressorStations.size() == 0)
				cout << "КС не найдена." << endl;
			int connectionCount = 0;
			for (const auto& pair : pipes)
				if (!pair.second.FreeConnections())
				{
					cout << "КС1 " << pair.second.csId1 << "- Труба " << pair.first << " - КС2 " << pair.second.csId2 << endl;
					connectionCount++;
				}
			cout << "Найдно " << connectionCount << " соединений." << endl;

		}
		break;
		case 11:
		{

			cout << "[ Удалить соединения ]" << endl;

			if (pipes.size() == 0)
				cout << "Труба не найдена." << endl;
			else {
				cout << "Введите ID для удаления: ";
				int deleteGasNetwork;
				InputCorrectNumber(deleteGasNetwork);
				while (pipes.find(deleteGasNetwork) == pipes.end())
				{
					cout << "Ошибка! Труба не найдена." << endl
						<< "Введите правильно: ";
					InputCorrectNumber(deleteGasNetwork);
				}
				if (pipes[deleteGasNetwork].FreeConnections()) {
					cout << "Труба не соединена." << endl;
				}
				else {
					pipes[deleteGasNetwork].DeleteConnection();
					cout << "Соединение удалено." << endl;
				}
			}
		}
		break;
		case 12:
		{
			cout << "[ Топологическая сортировка ]" << endl;
			// Вызов функции topologicalSort
			vector<int> sortedStations = topologicalSort(pipes, compressorStations);

			// Вывод отсортированных станций
			for (int stationId : sortedStations) {
				cout << stationId << " ";
			}
			cout << endl;
		}
		break;
		default:
			cout << "Ошибка! Введите правильно: " << endl;
			break;
		}
	}
}