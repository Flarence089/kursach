#include "data.h"
#include "console_io.h"
#include "command_processor.h"
#include "file_io.h"
#include <windows.h>
#include <iostream>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;
    bool isRunning = true;
    bool isBinaryMode = false; 

    while (isRunning) {
        system("cls");

      
        printMenu(isBinaryMode, size);

        int choice = getInt();

        
        executeCommand(choice, head, tail, size, isRunning, isBinaryMode);
    }

    clearList(head, tail, size);
    return 0;
}