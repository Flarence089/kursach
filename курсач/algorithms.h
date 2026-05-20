#pragma once
#include "data.h"
#include <string>

int linearSearchByName(Node* head, std::string target, Product* result);
int linearSearchByFabric(Node* head, int target, Product* result);
int linearSearchByCount(Node* head, int target, Product* result);
int linearSearchByDate(Node* head, Product::Date target, Product* result);
long long getDateWeight(const Product::Date& d);
bool compareProducts(const Product& a, const Product& b, int sortBy, bool ascending);
int hoarePartition(Product* arr, int low, int high, int sortBy, bool ascending);
void quickSort(Product* arr, int low, int high, int sortBy, bool ascending);