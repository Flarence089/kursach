#include "console_io.h"
#include "algorithms.h" 
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;


//    БЕЗОПАСНЫЙ ВВОД И ВАЛИДАЦИЯ

int getInt() {
    int x;
    while (true) {
        if (!(cin >> x)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Ошибка! Введите число: ";
        }
        else if (x < 0) {
            cout << "Ошибка! Число не может быть отрицательным: ";
        }
        else {
            return x;
        }
    }
}

string getValidString(int maxLength) {
    string input;
    while (true) {
        getline(cin, input);

        // Проверка на пустоту
        if (input.empty() || input.find_first_not_of(' ') == string::npos) {
            cout << "Ошибка! Строка не может быть пустой. Введите заново: ";
            continue;
        }

        // Ограничение на количество символов
        if (input.length() > maxLength) {
            cout << "Ошибка! Превышен лимит символов (максимум " << maxLength << "). Введите заново: ";
            continue;
        }

        // Ограничение на спецсимволы (запрещаем символы, которые могут сломать файл)
        bool hasInvalid = false;
        for (char c : input) {
            if (c == '|' || c == ';' || c == '<' || c == '>') {
                hasInvalid = true;
                break;
            }
        }

        if (hasInvalid) {
            cout << "Ошибка! Нельзя использовать спецсимволы ( | ; < > ). Введите заново: ";
            continue;
        }

        return input;
    }
}

bool isValidYear(int year) { return (year >= 1900 && year <= 2026); }
bool isValidMonth(int month) { return (month >= 1 && month <= 12); }
bool isLeapYear(int year) { return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0); }
bool isValidDay(int day, int month, int year) {
    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (isLeapYear(year)) daysInMonth[1] = 29;
    return (day >= 1 && day <= daysInMonth[month - 1]);
}

// Ввод даты с подробным выводом ошибок
void inputDate(Product::Date& date) {
    while (true) {
        cout << "Введите год выпуска: ";
        date.year = getInt();
        if (isValidYear(date.year)) break;
        cout << "Ошибка! Год должен быть от 1900 до 2026.\n";
    }
    while (true) {
        cout << "Введите месяц выпуска: ";
        date.month = getInt();
        if (isValidMonth(date.month)) break;
        cout << "Ошибка! Месяц должен быть от 1 до 12.\n";
    }
    while (true) {
        cout << "Введите день выпуска: ";
        date.day = getInt();
        if (isValidDay(date.day, date.month, date.year)) break;
        cout << "Ошибка! Неверное количество дней для этого месяца (" << date.month << "." << date.year << ").\n";
    }
}


//    ОСНОВНЫЕ ФУНКЦИИ УПРАВЛЕНИЯ СПИСКОМ


void insertProduct(Node*& head, Node*& tail, int& size) {
    Product p;
    cout << "Введите название (до 30 символов): ";
    cin >> ws; // очищаем буфер
    p.name = getValidString(30);
    cout << "Введите количество: "; p.count = getInt();
    cout << "Введите номер цеха: "; p.fabric_number = getInt();

  
    inputDate(p.date);

    cout << "\nВведите индекс для вставки (от 0 до " << size << "): ";
    int index;
    while (true) {
        index = getInt();
        if (index >= 0 && index <= size) break;
        cout << "Ошибка! Индекс должен быть от 0 до " << size << ": ";
    }

    Node* newNode = new Node{ p, nullptr, nullptr };

    if (size == 0) {
        head = tail = newNode;
    }
    else if (index == 0) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    else if (index == size) {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    else {
        Node* curr = head;
        for (int i = 0; i < index; i++) curr = curr->next;
        newNode->prev = curr->prev;
        newNode->next = curr;
        curr->prev->next = newNode;
        curr->prev = newNode;
    }
    size++;
    cout << "\n[УСПЕШНО] Элемент добавлен!\n";
}

void deleteProduct(Node*& head, Node*& tail, int& size) {
    if (size == 0) {
        cout << "Список пуст, удалять нечего!\n";
        return;
    }

    cout << "\nВведите индекс для удаления (от 0 до " << size - 1 << "): ";
    int index;
    while (true) {
        index = getInt();
        if (index >= 0 && index < size) break;
        cout << "Ошибка! Индекс должен быть от 0 до " << size - 1 << ": ";
    }

    Node* toDelete = nullptr;

    if (size == 1) {
        toDelete = head;
        head = tail = nullptr;
    }
    else if (index == 0) {
        toDelete = head;
        head = head->next;
        head->prev = nullptr;
    }
    else if (index == size - 1) {
        toDelete = tail;
        tail = tail->prev;
        tail->next = nullptr;
    }
    else {
        Node* curr = head;
        for (int i = 0; i < index; i++) curr = curr->next;
        toDelete = curr;
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }

    delete toDelete;
    size--;
    cout << "\n[УСПЕШНО] Элемент по индексу " << index << " удален!\n";
}


void editProduct(Node* head, int size) {
    if (size == 0) {
        cout << "Список пуст, редактировать нечего!\n";
        return;
    }

    cout << "\nВведите индекс записи для редактирования (от 0 до " << size - 1 << "): ";
    int index;
    while (true) {
        index = getInt();
        if (index >= 0 && index < size) break;
        cout << "Ошибка! Индекс должен быть от 0 до " << size - 1 << ": ";
    }

    Node* curr = head;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }

    bool editing = true;
    while (editing) {
        system("cls");
        cout << "--- РЕДАКТИРОВАНИЕ ЗАПИСИ (Индекс " << index << ") ---\n";
        cout << "1. Название   : " << curr->data.name << "\n";
        cout << "2. Количество : " << curr->data.count << "\n";
        cout << "3. Номер цеха : " << curr->data.fabric_number << "\n";
        cout << "4. Дата       : " << setfill('0') << setw(2) << curr->data.date.day << "."
            << setw(2) << curr->data.date.month << "."
            << setw(4) << curr->data.date.year << setfill(' ') << "\n";
        cout << "0. Завершить редактирование (Выход)\n";
        cout << "---------------------------------------\n";
        cout << "Выберите пункт для изменения: ";

        int choice = getInt();
        switch (choice) {
        case 1:
            cout << "Новое название (до 30 символов): ";
            cin >> ws;
            curr->data.name = getValidString(30);
            cout << "[УСПЕШНО] Название обновлено!\n";
            break;
        case 2:
            cout << "Введите новое количество: ";
            curr->data.count = getInt();
            cout << "[УСПЕШНО] Количество обновлено!\n";
            break;
        case 3:
            cout << "Введите новый номер цеха: ";
            curr->data.fabric_number = getInt();
            cout << "[УСПЕШНО] Номер цеха обновлен!\n";
            break;
        case 4:
            inputDate(curr->data.date);
            cout << "[УСПЕШНО] Дата обновлена!\n";
            break;
        case 0:
            editing = false; 
            break;
        default:
            cout << "Ошибка! Выберите пункт от 0 до 4.\n";
            pauseConsole();
        }
    }
}


//          ПОИСК И ВЫВОД НА ЭКРАН


void findProduct(Node* head, int size) {
    if (size == 0) { cout << "База данных пуста.\n"; return; }

    cout << "Искать по: 1-Названию, 2-Кол-ву, 3-Цеху, 4-Дате: ";
    int searchType;
    while (true) { searchType = getInt(); if (searchType >= 1 && searchType <= 4) break; }

    Product* foundData = new Product[size];
    int foundCount = 0;

    if (searchType == 1) {
        cout << "Введите название: ";
        string target; cin >> ws; getline(cin, target);
        foundCount = linearSearchByName(head, target, foundData);
    }
    else if (searchType == 2) {
        cout << "Введите точное количество: ";
        int target = getInt();
        foundCount = linearSearchByCount(head, target, foundData);
    }
    else if (searchType == 3) {
        cout << "Введите номер цеха: ";
        int target = getInt();
        foundCount = linearSearchByFabric(head, target, foundData);
    }
    else if (searchType == 4) {
        cout << "Введите дату для поиска:\n";
        Product::Date targetDate;
        inputDate(targetDate);
        foundCount = linearSearchByDate(head, targetDate, foundData);
    }

    if (foundCount == 0) cout << "Не найдено.\n";
    else {
        cout << "\nНайдены совпадения (" << foundCount << "):\n";
        cout << setfill(' ') << left << setw(25) << "Название" << setw(12) << "Кол-во" << setw(10) << "Цех" << "Дата\n";
        cout << string(55, '-') << "\n";
        for (int i = 0; i < foundCount; i++) {
            string n = foundData[i].name;
            if (n.length() >= 25) n = n.substr(0, 21) + "...";

            cout << left << setfill(' ')
                << setw(25) << n
                << setw(12) << foundData[i].count
                << setw(10) << foundData[i].fabric_number;

            cout << right << setfill('0')
                << setw(2) << foundData[i].date.day << "."
                << setw(2) << foundData[i].date.month << "."
                << setw(4) << foundData[i].date.year
                << left << setfill(' ') << "\n";
        }
    }
    delete[] foundData;
}
void printTableUnsorted(Node* head, int size) {
    if (size == 0) { cout << "Записей нет\n"; return; }

    // Красивая шапка таблицы
    cout << "\n+---------------------------+------------+--------+------------+\n";
    cout << "| " << left << setw(25) << "Название"
        << " | " << setw(10) << "Кол-во"
        << " | " << setw(6) << "Цех"
        << " | " << setw(10) << "Дата" << " |\n";
    cout << "+---------------------------+------------+--------+------------+\n";

    Node* curr = head;
    while (curr != nullptr) {
        string n = curr->data.name;
        if (n.length() > 25) n = n.substr(0, 22) + "..."; // 22 буквы + 3 точки

        cout << "| " << left << setfill(' ') << setw(25) << n
            << " | " << setw(10) << curr->data.count
            << " | " << setw(6) << curr->data.fabric_number
            << " | " << right << setfill('0') // Включаем выравнивание вправо для дат
            << setw(2) << curr->data.date.day << "."
            << setw(2) << curr->data.date.month << "."
            << setw(4) << curr->data.date.year
            << left << setfill(' ') << " |\n"; // Возвращаем пробелы и левое выравнивание
        curr = curr->next;
    }
    cout << "+---------------------------+------------+--------+------------+\n";
}

void printTableSorted(Node* head, int size) {
    if (size == 0) { cout << "Записей нет\n"; return; }

    Product* arr = new Product[size];
    Node* curr = head;
    for (int i = 0; i < size; i++) { arr[i] = curr->data; curr = curr->next; }

    cout << "Сортировать по: 1-Названию, 2-Кол-ву(*), 3-Цеху, 4-Дате: ";
    int sortBy;
    while (true) {
        sortBy = getInt();
        if (sortBy >= 1 && sortBy <= 4) break;

        
        cout << "Ошибка! Выберите пункт от 1 до 4: ";
    }

    cout << "Направление: 1-По возрастанию, 2-По убыванию(*): ";
    int dir; while (true) {
        dir = getInt(); if (dir == 1 || dir == 2) break;
        cout << "Ошибка! Выберите пункт от 1 до 2: ";
    }

    quickSort(arr, 0, size - 1, sortBy, (dir == 1));

    if (sortBy == 2 && dir == 2) {
        cout << "\n*** РЕЗУЛЬТАТ ВЫПОЛНЕНИЯ ИНДИВИДУАЛЬНОГО ЗАДАНИЯ ***";
    }

    // Красивая шапка таблицы
    cout << "\n+---------------------------+------------+--------+------------+\n";
    cout << "| " << left << setw(25) << "Название"
        << " | " << setw(10) << "Кол-во"
        << " | " << setw(6) << "Цех"
        << " | " << setw(10) << "Дата" << " |\n";
    cout << "+---------------------------+------------+--------+------------+\n";

    for (int i = 0; i < size; i++) {
        string n = arr[i].name;
        if (n.length() > 25) n = n.substr(0, 22) + "...";

        cout << "| " << left << setfill(' ') << setw(25) << n
            << " | " << setw(10) << arr[i].count
            << " | " << setw(6) << arr[i].fabric_number
            << " | " << right << setfill('0')
            << setw(2) << arr[i].date.day << "."
            << setw(2) << arr[i].date.month << "."
            << setw(4) << arr[i].date.year
            << left << setfill(' ') << " |\n";
    }
    cout << "+---------------------------+------------+--------+------------+\n";
    delete[] arr;
}



void printMenu(bool isBinaryMode, int currentSize) {
    cout << "===============================================\n";
    cout << "||        СИСТЕМА УЧЕТА ПРОДУКЦИИ            ||\n";
    cout << "===============================================\n";
    cout << "||             ВЫВОД ПРОДУКЦИИ               ||\n";
    cout << "===============================================\n";
    cout << "|| 1. Вставить продукцию по индексу          ||\n";
    cout << "|| 2. Удалить продукцию по индексу           ||\n";
    cout << "|| 3. Показать данные (исходная таблица)     ||\n";
    cout << "|| 4. Показать данные (с сортировкой)*       ||\n";
    cout << "===============================================\n";
    cout << "||          РАБОТА С БАЗОЙ ДАННЫХ            ||\n";
    cout << "===============================================\n";
    cout << "|| 5. Сохранить в файл                       ||\n";
    cout << "|| 6. Загрузить из файла                     ||\n";
    cout << "|| 7. Удалить файл базы данных               ||\n";
    cout << "|| 8. Создать файл базы данных               ||\n";
    cout << "===============================================\n";
    cout << "||                 ПРОЧЕЕ                    ||\n";
    cout << "===============================================\n";
    cout << "|| 9. Редактировать запись                   ||\n";
    cout << "|| 10. Найти продукцию (Название / Цех)      ||\n";
    cout << "|| 11. Очистка динамической памяти           ||\n";
    cout << "|| 12. Сменить режим (Текст/Бинарный)        ||\n";
    cout << "|| 0. Выход из программы                     ||\n";
    cout << "===============================================\n";
    cout << "Режим: [" << (isBinaryMode ? "Бинарный" : "Текстовый")
        << "] | Записей в памяти: " << currentSize << "\n";
    cout << "Ваш выбор: ";
}

void pauseConsole() {
    cout << "\nНажмите Enter для продолжения...";
    cin.ignore(1000, '\n');
    cin.get();
}