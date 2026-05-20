#pragma once
#include <string>

struct Product {
    std::string name;   
    int count;          
    int fabric_number;  
    struct Date {
        int day;
        int month;
        int year;
    } date;
};

struct Node {
    Product data; 
    Node* prev;   
    Node* next;   
};