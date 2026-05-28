#include "command_processor.h"
#include "console_io.h"
#include "file_io.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void executeCommand(int choice, Node*& head, Node*& tail, int& size, bool& isRunning, bool& isBinaryMode) {
    string filename = isBinaryMode ? "database.bin" : "database.txt";

    switch (choice) {
        // --- ВЫВОД ПРОДУКЦИИ ---
    case 1:
        system("cls");
        insertProduct(head, tail, size);
        pauseConsole();
        break;
    case 2:
        system("cls"); deleteProduct(head, tail, size); pauseConsole();
        break;
    case 3:
        system("cls"); printTableUnsorted(head, size); pauseConsole();
        break;
    case 4:
        system("cls"); printTableSorted(head, size); pauseConsole();
        break;

        // --- РАБОТА С БАЗОЙ ДАННЫХ ---
   
    case 5:
        system("cls");
        cout << "Введите имя файла для СОХРАНЕНИЯ (имя файла.txt): ";
        {
            string saveFile;
            cin >> ws;
            getline(cin, saveFile);
            saveToFile(head, size, saveFile, isBinaryMode);
        }
        pauseConsole();
        break;

    case 6:
        system("cls");
        cout << "Введите имя файла для ЗАГРУЗКИ (имя файла.txt): ";
        {
            string loadFile;
            cin >> ws;
            getline(cin, loadFile);
            loadFromFile(head, tail, size, loadFile, isBinaryMode);
        }
        pauseConsole();
        break;
    case 7:
        system("cls");
        cout << "Введите имя файла для удаления (например, " << filename << "): ";
        { string delFile; cin >> ws; getline(cin, delFile); deleteFile(delFile); }
        pauseConsole();
        break;
    case 8:
        system("cls"); createFile(isBinaryMode); pauseConsole();
        break;

        // --- ПРОЧЕЕ ---
    case 9:
        system("cls"); editProduct(head, size); pauseConsole();
        break;
    case 10:
        system("cls"); findProduct(head, size); pauseConsole();
        break;
    case 11:
        system("cls");
        clearList(head, tail, size);
        cout << "Динамическая память успешно очищена!\n";
        pauseConsole();
        break;
    case 12:
        system("cls"); filterData(head);pauseConsole();
        break;
   

        // --- ВЫХОД ---
    case 0:
        system("cls"); isRunning = false;
        break;

    default:
        cout << "Ошибка ввода! Выберите пункт от 0 до 12.\n";
        pauseConsole();
    }
}