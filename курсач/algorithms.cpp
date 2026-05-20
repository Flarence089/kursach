#include "algorithms.h"
#include <utility>


int linearSearchByName(Node* head, std::string target, Product* result) {
    int foundCount = 0;
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data.name == target) {
            result[foundCount] = curr->data;
            foundCount++;
        }
        curr = curr->next;
    }
    return foundCount;
}

int linearSearchByFabric(Node* head, int target, Product* result) {
    int foundCount = 0;
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data.fabric_number == target) {
            result[foundCount] = curr->data;
            foundCount++;
        }
        curr = curr->next;
    }
    return foundCount;
}

int linearSearchByCount(Node* head, int target, Product* result) {
    int foundCount = 0;
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data.count == target) {
            result[foundCount] = curr->data;
            foundCount++;
        }
        curr = curr->next;
    }
    return foundCount;
}

int linearSearchByDate(Node* head, Product::Date target, Product* result) {
    int foundCount = 0;
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data.date.day == target.day &&
            curr->data.date.month == target.month &&
            curr->data.date.year == target.year) {
            result[foundCount] = curr->data;
            foundCount++;
        }
        curr = curr->next;
    }
    return foundCount;
}

// ==========================================
//          УМНАЯ СОРТИРОВКА ХОАРА
// ==========================================

// Превращаем дату в одно число (приблизительно в дни), чтобы легко сравнивать
long long getDateWeight(const Product::Date& d) {
    // Превращаем дату в одно число для удобного сравнения
    return (long long)d.year * 365 + d.month * 30 + d.day;
}

// Компаратор должен использовать СТРОГИЕ неравенства (< или >)
bool compareProducts(const Product& a, const Product& b, int sortBy, bool ascending) {
    if (sortBy == 1) {
        return ascending ? a.name < b.name : a.name > b.name;
    }
    else if (sortBy == 2) {
        return ascending ? a.count < b.count : a.count > b.count;
    }
    else if (sortBy == 3) {
        return ascending ? a.fabric_number < b.fabric_number : a.fabric_number > b.fabric_number;
    }
    else if (sortBy == 4) {
        long long w1 = getDateWeight(a.date);
        long long w2 = getDateWeight(b.date);
        return ascending ? w1 < w2 : w1 > w2;
    }
    return false;
}

// Безопасное разделение Хоара (с опорным элементом посередине)
int hoarePartition(Product* arr, int low, int high, int sortBy, bool ascending) {
    Product pivot = arr[low + (high - low) / 2];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do { i++; } while (compareProducts(arr[i], pivot, sortBy, ascending));
        do { j--; } while (compareProducts(pivot, arr[j], sortBy, ascending));

        if (i >= j) return j;

        // Меняем элементы местами
        Product temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// Сама быстрая сортировка с защитой от бесконечной рекурсии
void quickSort(Product* arr, int low, int high, int sortBy, bool ascending) {
    if (low < high) {
        int pi = hoarePartition(arr, low, high, sortBy, ascending);
        quickSort(arr, low, pi, sortBy, ascending);
        quickSort(arr, pi + 1, high, sortBy, ascending);
    }
}