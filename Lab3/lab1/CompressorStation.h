#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Utilities.h"

using namespace std;

class CompressorStation
{
	static int maxId;
	int Id;
	string name = "";
	int workshopCount = 0;
	int activeWorkshopCount = 0;
	int efficiency = 0;
public:
	int GetId();
	string GetName() const;
	void PrintWorkshopStatus() const;
	int GetPercentOfActiveWorkshops() const;
	friend void EditCompressorStations(vector <CompressorStation*>& compressorStations);
	friend void EditCompressorStation(CompressorStation& compressorStation);
	friend ostream& operator << (ostream& out, const CompressorStation& CS);
	friend istream& operator >> (istream& in, CompressorStation& CS);
	friend ofstream& operator << (ofstream& fout, const CompressorStation& CS);
	friend ifstream& operator >> (ifstream& fin, CompressorStation& CS);

};

