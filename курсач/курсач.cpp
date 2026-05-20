#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
using namespace std;

struct Product {
    string name;        // название продукции
    int count;          // количество изделий
    int fabric_number;  // номер цеха
    struct Date {
        int day;
        int month;
        int year;
    } date;
};

// безопасный ввод числа
int getInt() {
    int x;
    while (true) {
        if (!(cin >> x)) {
            cin.clear();             // очистка ошибки
            cin.ignore(1000, '\n');  // очистка буфера
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

bool isValidYear(int year) {
    return (year >= 1900 && year <= 2026);
}

bool isValidMonth(int month) {
    return (month >= 1 && month <= 12);
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDay(int day, int month, int year) {
    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    if (isLeapYear(year))
        daysInMonth[1] = 29;

    return (day >= 1 && day <= daysInMonth[month - 1]);
}

// функция добавления продукции
void addProduct(Product*& pr, int& size) {
    // создаём новый массив на 1 элемент больше
    Product* arr = new Product[size + 1];

    // копируем старые данные в новый массив
    for (int i = 0; i < size; i++) {
        arr[i] = pr[i];
    }

    // ввод новой записи
    cout << "Введите название: ";
    cin >> ws;
    getline(cin, arr[size].name);

    cout << "Введите количество: ";
    arr[size].count = getInt();

    cout << "Введите номер цеха: ";
    arr[size].fabric_number = getInt();

    int day, month, year;

    // год
    do {
        cout << "Введите год выпуска: ";
        year = getInt();
        if (!isValidYear(year))
            cout << "Ошибка! Год должен быть от 1900 до 2026\n";
    } while (!isValidYear(year));

    do {
        cout << "Введите месяц выпуска: ";
        month = getInt();
        if (!isValidMonth(month))
            cout << "Ошибка! Месяц должен быть от 1 до 12\n";
    } while (!isValidMonth(month));

    do {
        cout << "Введите день выпуска: ";
        day = getInt();
        if (!isValidDay(day, month, year))
            cout << "Ошибка! Неверное количество дней для этого месяца\n";
    } while (!isValidDay(day, month, year));

    arr[size].date.day = day;
    arr[size].date.month = month;
    arr[size].date.year = year;

    // удаляем старый массив
    delete[] pr;

    // указатель смотрит на новый массив
    pr = arr;

    // увеличиваем количество записей
    size++;

    cout << "\n[УСПЕШНО] Продукция успешно добавлена!\n";
}

// поле-значение
void printAll(Product* pr, int size) {
    if (size == 0) {
        cout << "Записей нет\n";
        return;
    }

    for (int i = 0; i < size; i++) {
        cout << "\n--- Продукция " << i + 1 << " ---" << endl;
        cout << "Название:   " << pr[i].name << endl;
        cout << "Количество: " << pr[i].count << endl;
        cout << "Номер цеха: " << pr[i].fabric_number << endl;
        cout << "Дата:       "
            << setfill('0') << setw(2) << pr[i].date.day << "."
            << setfill('0') << setw(2) << pr[i].date.month << "."
            << pr[i].date.year
            << setfill(' ') << endl; // <--- ВАЖНО: сброс заполнителя на пробел



    }
}

int hoarePartition(Product* arr, int low, int high) {
    int pivot = arr[(low + high) / 2].count; // Опорный элемент (по количеству)
    int i = low - 1;
    int j = high + 1;

    while (true) {
        // Ищем элемент слева, который МЕНЬШЕ опорного 
        // (измените знак на < , если нужна сортировка по возрастанию)
        do {
            i++;
        } while (arr[i].count > pivot); // Сортируем по УБЫВАНИЮ количества

        // Ищем элемент справа, который БОЛЬШЕ опорного
        do {
            j--;
        } while (arr[j].count < pivot);

        if (i >= j)
            return j;

        // Меняем элементы местами
        swap(arr[i], arr[j]);
    }
}

// Сама функция Быстрой сортировки (QuickSort)
void quickSort(Product* arr, int low, int high) {
    if (low < high) {
        // Получаем индекс разбиения
        int pi = hoarePartition(arr, low, high);

        // Рекурсивно сортируем элементы до и после разбиения
        quickSort(arr, low, pi);
        quickSort(arr, pi + 1, high);
    }
}

// таблица
void printTable(Product* pr, int size) {
    if (size == 0) {
        cout << "Записей нет\n";
        return;
    }

    // создаём копию массива, чтобы не менять оригинал
    Product* arr = new Product[size];

    for (int i = 0; i < size; i++)
        arr[i] = pr[i];

    quickSort(arr, 0, size - 1);

    //// сортировка по убыванию количества
    //for (int i = 0; i < size - 1; i++) {
    //    for (int j = 0; j < size - i - 1; j++) {
    //        if (arr[j].count < arr[j + 1].count) {
    //            swap(arr[j], arr[j + 1]);
    //        }
    //    }
    //}

    // Задаем ширину колонок
    const int NAME_W = 25;
    const int CNT_W = 12;
    const int FAB_W = 10;

    // ШАПКА ТАБЛИЦЫ
    cout << "\n" << left
        << setw(NAME_W) << "Название"
        << setw(CNT_W) << "Кол-во"
        << setw(FAB_W) << "Цех"
        << "Дата"
        << "\n";

    // Линия подчеркивания
    cout << string(NAME_W + CNT_W + FAB_W + 12, '-') << "\n";

    // ВЫВОД ДАННЫХ
    for (int i = 0; i < size; i++) {

        string displayName = arr[i].name;

        // ПРОВЕРКА ДЛИНЫ: если название не влезает в колонку
        // Оставляем запас в 1 символ (NAME_W - 1), чтобы колонки не слипались
        if (displayName.length() >= NAME_W) {
            // Обрезаем строку и добавляем "..."
            displayName = displayName.substr(0, NAME_W - 4) + "...";
        }

        // Выводим обработанное название
        cout << setw(NAME_W) << displayName
            << setw(CNT_W) << arr[i].count
            << setw(FAB_W) << arr[i].fabric_number;

        // Вывод даты
        cout << setfill('0')
            << setw(2) << arr[i].date.day << "."
            << setw(2) << arr[i].date.month << "."
            << setw(4) << arr[i].date.year
            << setfill(' ') << "\n";
    }

    delete[] arr;
}

// Отрисовка главного меню
void printMenu() {
    cout << "============================================\n";
    cout << "||        СИСТЕМА УЧЕТА ПРОДУКЦИИ         ||\n";
    cout << "============================================\n";
    cout << "|| 1. Добавить новую продукцию            ||\n";
    cout << "|| 2. Показать данные (списком)           ||\n";
    cout << "|| 3. Показать данные (таблицей)          ||\n";
    cout << "|| 4. Выход из программы                  ||\n";
    cout << "============================================\n";
    cout << "Ваш выбор: ";
}

// Пауза для того, чтобы пользователь мог прочитать вывод
void pauseConsole() {
    cout << "\nНажмите Enter для продолжения...";
    cin.ignore(1000, '\n');
    cin.get();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru_RU");

    Product* pr = nullptr;  // указатель на динамический массив
    int size = 0;           // количество записей
    int choice;

    do {
        system("cls"); // Очистка экрана (работает на Windows благодаря <windows.h>)
        printMenu();
        choice = getInt();

        switch (choice) {
        case 1:
            system("cls");
            cout << "--- ДОБАВЛЕНИЕ ПРОДУКЦИИ ---\n\n";
            addProduct(pr, size);
            pauseConsole();
            break;

        case 2:
            system("cls");
            cout << "--- СПИСОК ПРОДУКЦИИ ---\n";
            printAll(pr, size);
            pauseConsole();
            break;

        case 3:
            system("cls");
            cout << "--- ТАБЛИЦА ПРОДУКЦИИ (сортировка по кол-ву) ---\n";
            printTable(pr, size);
            pauseConsole();
            break;

        case 4:
            system("cls");
            cout << "Завершение работы программы...\n";
            break;

        default:
            cout << "Ошибка! Пожалуйста, выберите пункт от 1 до 4.\n";
            pauseConsole();
        }

    } while (choice != 4);

    delete[] pr;
    return 0;
}