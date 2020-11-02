#pragma once
#include <vector>
#include <iostream>

#include "Segment.h"
#include "Process.h"
#include "msoftcon.h"

using namespace std;
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>
#include <thread>
#include <chrono>

class OperationSystem
{
private:
    vector<Segment> segments;
    vector<Process> processes;
    int MEMORY_SIZE;
    std::string item = " \t *\t";
public:
    OperationSystem();
    ~OperationSystem();

    void RunSimulation();
    std::string GetProgressBar(float progress);
    void SetMemory();
    void AddSegment();
    void DeleteSegment(int segmentId);
    void AddProcess();
    void ShowAll();
    void ShowAllInRealTime();
    void IncreaseTimer();

    std::thread t1;
    int TIMER = 0;
};
