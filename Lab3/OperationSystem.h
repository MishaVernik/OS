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
#include <mutex>

class OperationSystem
{
private:
    vector<Segment> segments;
    vector<Process> processes;
    int MEMORY_SIZE;
    std::string item = " \t *\t";
    mutex mx;
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
    void getAddress();

    std::thread t1;
    int TIMER = 0;
};
