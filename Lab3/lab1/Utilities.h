#pragma once
#include <iostream>

using namespace std;

template <typename T>
void InputCorrectNumber(T& var, bool canEqualToZero = false)
{
	cin >> var;
	while (cin.fail() || cin.peek() != '\n' || (canEqualToZero ? var < 0 : var <= 0))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Error! Please enter correct data: ";
		cin >> var;
	}
}
template <typename T>
void InputCorrectNumberNull(T& var, bool canEqualToZero = true)
{
	cin >> var;
	while (cin.fail() || cin.peek() != '\n' || (canEqualToZero ? var < 0 : var <= 0))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Error! Please enter correct data: ";
		cin >> var;
	}
}

template <typename T>
void InputCorrectDiameter(T& var, int& diameter)
{
	cin >> diameter;
	while ((diameter != 500 && diameter != 700 && diameter != 1000 && diameter != 1400) || cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Error! Please enter correct data (500, 700, 1000, 1400): ";
		cin >> diameter;
	}
}