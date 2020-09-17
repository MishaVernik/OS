#pragma once
 
void ProcessWorkingTime(std::vector<Process>& data, int currentProcess);

bool IsProcessReady(std::vector<Process>& data, int& currentProcess);

void IncreaseGlobalTimer(std::vector<Process>& data);

void MoveToTheNextProcess(std::vector<Process>& data, int& currentProcess);

void FIFO();