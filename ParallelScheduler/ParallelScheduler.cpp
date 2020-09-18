#include <iostream>
#include <algorithm>
#include <thread>
#include <functional>
#include <utility>
#include <mutex>

#include "CommonData.h"
#include "Process.h"
#include "IFileReader.h"
#include "InputData.h"
#include "ParallelScheduler.h"

using namespace std;

int main()
{
	std::thread threadFIFO(FIFO);
	threadFIFO.join();
	
	return 0;
}

void FIFO() {
	ifstream file("input.txt");
	InputData inputData;

	auto data = inputData.ReadFromFile(file);
	sort(data.begin(), data.end(), [](Process a, Process b) {
		return a.startTime < b.startTime;
		});
	
	int currentProcess = 0;
	 

	while (currentProcess < data.size()) {
		if (!IsProcessReady(data, currentProcess)) {
			IncreaseGlobalTimer(data);
		}
	}
	int waitingTime = 0;
	cout << "Process" << "\tAppear time" << "\tWorking time" << "\tStarted time" << "\tWaiting time" << "\tFinished time" << "\tFull time" << endl;
	for (auto& process : data) {
		cout <<  "" << process.number << "\t"
			<< process.startTime << "\t\t" 
			<< process.workingTime << "\t\t" 
			<< process.startedTime << "\t\t" 
			<< process.waitingTime << "\t\t" 
			<< process.finishedTime << "\t\t" 
			<< process.waitingTime + process.workingTime << endl;
		waitingTime = waitingTime + process.waitingTime;
	}
#ifdef DEBUG
	cout << "GlobalTimer: " << CommonData::GET_GLOBAL_COUNTER() << endl;
	cout << "WaitingTime: " << waitingTime << endl;
#endif
}

void EventParallelCheck(std::vector<Process>& data) {	
	// linear
#ifdef DEBUG
	for (auto& process : data) {
		process.CheckChanges(CommonData::GET_GLOBAL_COUNTER());
	}
	
	return;
#endif 

	// parallel
	vector<std::thread> threads;
	std::mutex m;
	int currentGlobalTimer = CommonData::GET_GLOBAL_COUNTER();
	for (auto& process : data) {			
		threads.push_back(process.ProcessThread(currentGlobalTimer));		
	}

	for (auto& thread : threads) {
		thread.join();
	} 
}

void IncreaseGlobalTimer(std::vector<Process>& data)
{
	EventParallelCheck(data);
	CommonData::SET_GLOBAL_COUNTER(CommonData::GLOBAL_TIMER());	
}

bool ChangeProcessStatus(std::vector<Process>& data, int& currentProcess, ProcessStatus status) {
	if (currentProcess < data.size()) {
		switch (status)
		{
		case ProcessStatus::WaitingIfNotStarted:
			break;
		case ProcessStatus::WaitingIfStarted:
			break;
		case ProcessStatus::Started:
			data[currentProcess].startedTime = CommonData::GET_GLOBAL_COUNTER();
			break;
		case ProcessStatus::InProgress:			
			break;
		case ProcessStatus::Finished:
			data[currentProcess].finishedTime = CommonData::GET_GLOBAL_COUNTER();
			break;
		default:
			break;
		}
		data[currentProcess].staus = status;
		return true;
	}
	return false;
}

bool IsProcessReady(std::vector<Process>& data, int& currentProcess)
{
	if (data[currentProcess].startTime <= CommonData::GET_GLOBAL_COUNTER()) {
		ChangeProcessStatus(data, currentProcess, ProcessStatus::Started);
		ProcessWorkingTime(data, currentProcess);
		MoveToTheNextProcess(data, currentProcess);
		
		return true;
	}
	return false;
}

void ProcessWorkingTime(std::vector<Process>& data, int currentProcess)
{
	ChangeProcessStatus(data, currentProcess, ProcessStatus::InProgress);
	for (int i = 0; i < data[currentProcess].workingTime; i++) {
		IncreaseGlobalTimer(data);
	}
}

void MoveToTheNextProcess(std::vector<Process>& data, int& currentProcess)
{
	ChangeProcessStatus(data, currentProcess, ProcessStatus::Finished);
	currentProcess = currentProcess + CommonData::CURRENT_PROCESS();
}
