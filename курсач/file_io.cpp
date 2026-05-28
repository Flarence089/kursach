#include "file_io.h"
#include <fstream>
#include <iostream>

using namespace std;

void clearList(Node*& head, Node*& tail, int& size) {
    Node* curr = head;
    while (curr != nullptr) {
        Node* nextNode = curr->next; 
        delete curr;                 
        curr = nextNode;             
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}


void saveToFile(Node* head, int size, const string& filename, bool isBinary) {

    ofstream file(filename, isBinary ? ios::binary : ios::out);
    if (!file.is_open()) {
        cout << "Ошибка! Не удалось открыть файл для записи.\n";
        return;
    }

    if (isBinary) {
        file.write((char*)&size, sizeof(int)); 
        Node* curr = head;
        while (curr != nullptr) {
            size_t nameLen = curr->data.name.size();
            file.write((char*)&nameLen, sizeof(size_t));
            file.write(curr->data.name.c_str(), nameLen);

            file.write((char*)&curr->data.count, sizeof(int));
            file.write((char*)&curr->data.fabric_number, sizeof(int));
            file.write((char*)&curr->data.date, sizeof(Product::Date));
            curr = curr->next;
        }
    }
    else {
    
        file << size << "\n";
        Node* curr = head;
        while (curr != nullptr) {
            file << curr->data.name << "\n"
                << curr->data.count << "\n"
                << curr->data.fabric_number << "\n"
                << curr->data.date.day << " " << curr->data.date.month << " " << curr->data.date.year << "\n";
            curr = curr->next;
        }
    }
    file.close();
    cout << "Данные успешно сохранены в файл: " << filename << "\n";
}

void loadFromFile(Node*& head, Node*& tail, int& size, const string& filename, bool isBinary) {
    ifstream file(filename, isBinary ? ios::binary : ios::in);
    if (!file.is_open()) {
        cout << "Ошибка! Не удалось открыть файл для чтения.\n";
        return;
    }

    int newSize;
    if (isBinary) {
        file.read((char*)&newSize, sizeof(int));
    }
    else {
        if (!(file >> newSize)) {
            cout << "Файл пуст или поврежден.\n";
            return;
        }
    }

    clearList(head, tail, size); 

    for (int i = 0; i < newSize; i++) {
        Product p;
        if (isBinary) {

            size_t nameLen;
            file.read((char*)&nameLen, sizeof(size_t));
            p.name.resize(nameLen);
            file.read(&p.name[0], nameLen);

            file.read((char*)&p.count, sizeof(int));
            file.read((char*)&p.fabric_number, sizeof(int));
            file.read((char*)&p.date, sizeof(Product::Date));
        }
        else {

            file >> ws;
            getline(file, p.name);
            file >> p.count >> p.fabric_number >> p.date.day >> p.date.month >> p.date.year;
        }

        Node* newNode = new Node{ p, nullptr, nullptr };
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }
    file.close();
    cout << "Данные успешно загружены! Количество записей: " << size << "\n";
}

bool deleteFile(const string& filename) {
    if (remove(filename.c_str()) == 0) {
        cout << "Файл '" << filename << "' успешно удален!\n";
        return true;
    }
    else {
        cout << "Ошибка! Не удалось удалить файл.\n";
        return false;
    }
}

void createFile(bool isBinaryMode) {
    cout << "Введите имя нового файла (например, my_data" << (isBinaryMode ? ".bin" : ".txt") << "): ";
    string filename;
    cin >> ws;
    getline(cin, filename);


    ofstream file(filename, isBinaryMode ? ios::binary : ios::out);
    if (!file.is_open()) {
        cout << "Ошибка! Не удалось создать файл.\n";
        return;
    }


    int initialSize = 0;
    if (isBinaryMode) {
        file.write((char*)&initialSize, sizeof(int));
    }
    else {
        file << initialSize << "\n";
    }

    file.close();
    cout << "Пустой файл базы данных '" << filename << "' успешно создан!\n";
}