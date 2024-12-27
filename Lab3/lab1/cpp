#include <iostream> 
#include <Windows.h>
#include <vector>
#include <locale>

using namespace std;

void PrintMemoryStatus() {
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);

    cout << "Общий объем виртуальной памяти: "
        << statex.ullTotalPageFile / (1024 * 1024) << " МБ" << endl;
    cout << "Доступный объем виртуальной памяти: "
        << statex.ullAvailPageFile / (1024 * 1024) << " МБ" << endl << endl;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    const SIZE_T allocationSize = 100 * 1024 * 1024;
    vector<LPVOID> allocations;

    cout << "Cтатус памяти:" << endl;
    PrintMemoryStatus();

    int allocationCount = 0;

    while (true) {
        LPVOID block = VirtualAlloc(nullptr, allocationSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        if (block == nullptr) {
            break;
        }
        allocations.push_back(block);
        allocationCount++;
    }

    cout << "Статус памяти после выделения: " << endl;
    PrintMemoryStatus();
    cout << "Выделено блоков: " << allocationCount << endl << endl;

    for (size_t i = 1; i < allocations.size(); i += 2) {
        VirtualFree(allocations[i], 0, MEM_RELEASE);
        allocations[i] = nullptr;
    }

    cout << "Статус памяти после освобождения каждого второго блока: " << endl;
    PrintMemoryStatus();

    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    SIZE_T availableMemory = statex.ullAvailPageFile;

    LPVOID newBlock = VirtualAlloc(nullptr, availableMemory, MEM_RESERVE, PAGE_READWRITE);
    if (newBlock) {
        cout << "Успешно выделена область памяти размером: "
            << availableMemory / (1024 * 1024) << " MБ" << endl << endl;
    }
    else {
        cout << "Не удалось выделить область памяти." << endl << endl;
    }

    for (LPVOID block : allocations) {
        if (block != nullptr) {
            VirtualFree(block, 0, MEM_RELEASE);
        }
    }

    cout << "Печатаем статус памяти после освобождения оставшихся выделенных блоков:" << endl;
    PrintMemoryStatus();

    LPVOID reservedBlock = VirtualAlloc(nullptr, availableMemory, MEM_RESERVE, PAGE_NOACCESS);
    if (reservedBlock) {
        cout << "Успешно зарезервирована область памяти размером: "
            << availableMemory / (1024 * 1024) << " Mɓ" << endl << endl;;
    }
    else {
        cout << "Не удалось зарезервировать область памяти. " << endl << endl;;
    }

    cout << "Повторяем пункты 1-6 : " << endl;
    PrintMemoryStatus();

    LPVOID newReservedBlock = VirtualAlloc(nullptr, availableMemory, MEM_RESERVE, PAGE_NOACCESS);
    if (newReservedBlock) {
        cout << "Успешно зарезервирована новая область памяти размером: "
            << availableMemory / (1024 * 1024) << " M5" << endl << endl;;
    }
    else {
        cout << "Не удалось зарезервировать новую область памяти." << endl << endl;;
    }

    return 0;
}
