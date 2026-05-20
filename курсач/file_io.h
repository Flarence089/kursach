#pragma once
#include "data.h"
#include <string>

void clearList(Node*& head, Node*& tail, int& size);
void saveToFile(Node* head, int size, const std::string& filename, bool isBinary);
void loadFromFile(Node*& head, Node*& tail, int& size, const std::string& filename, bool isBinary);
bool deleteFile(const std::string& filename);
void createFile(bool isBinaryMode);