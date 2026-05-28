#pragma once
#include "data.h"

int getInt();
std::string getValidString(int maxLength);
void insertProduct(Node*& head, Node*& tail, int& size);
void deleteProduct(Node*& head, Node*& tail, int& size);
void printTableUnsorted(Node* head, int size);
void printTableSorted(Node* head, int size);
void printMenu(bool isBinaryMode, int currentSize);
void pauseConsole();
void findProduct(Node* head, int size);
void editProduct(Node* head, int size);
void filterData(Node* head);