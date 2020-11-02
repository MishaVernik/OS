#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <thread>
#include <mutex>          // std::mutex
#include <atomic>

#include "OperationSystem.h"

using namespace std;

struct MenuItem {
    string item;
    color col;
    MenuItem(string, color);
};

class Menu {
private:
    static const color DEFAULT_COLOR = cDARK_GRAY;
    static const char CARRET = '>';
    string name;
    vector<MenuItem> items;
    int pos;
    color col;
    OperationSystem* operationSystem;
    std::thread t1;
    bool isRunSimualtion = false;

    void printScroll();
    void printCarret();
public:   

    void RunThreads();
    void print();    
    void printItems();
    void RunSimulation();
    void SetOperationSystem(OperationSystem *operationSystem);
    Menu(string, color = DEFAULT_COLOR);
    void show();
    void addItem(string, color = DEFAULT_COLOR);
    void clearItems();
    int returnChoise();
};

#endif // MENU_H_INCLUDED