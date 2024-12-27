#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Logger {
    ofstream logFile;
    int logNumber = 0;
public:
    Logger() {
        logFile.open("log.txt");
    }

    ~Logger() {
        if (!logFile.is_open())
            cout << "File \"log.txt\" opening error!" << endl;
        else
            logFile.close();
    }

    template <typename T>
    void log(const T& message) {
        if (!logFile.is_open())
            cout << "File \"log.txt\" opening error!" << endl;
        else
        {
            logFile << "[" << logNumber << "] " << message << endl;
            logNumber++;
        }
    }
};