#include <iostream>
#include <algorithm>
#include <thread>
#include <functional>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <mutex>

#include "CommonData.h"
#include "Process.h"
#include "IFileReader.h"
#include "InputData.h"
#include "ParallelScheduler.h"

using namespace std;

class FIFO {
public:
	FIFO() {
	}

	void RunInThread() {
		std::thread threadFIFO(&FIFO::Init, this);
		threadFIFO.join();
	}

	void Init() {
		cout << "\t\t\t FIFO \n";
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
		cout << "\n\nProcess" << "\tAppear time" << "\tWorking time" << "\tStarted time" << "\tWaiting time" << "\tFinished time" << "\tFull time" << endl;
		for (auto& process : data) {
			cout << "" << process.number << "\t"
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

};

class SJF {
private:
	unordered_set<int> visited;
public:
	SJF() {

	}
	void RunInThread() {
		std::thread threadSJF(&SJF::Init, this);
		threadSJF.join();
	}

	void Init() {
		cout << "\t\t\t SJF \n";
		ifstream file("input.txt");
		InputData inputData;

		auto data = inputData.ReadFromFile(file);
		sort(data.begin(), data.end(), [](Process a, Process b) {
		
			if (a.startTime == b.startTime) {
				return a.waitingTime < b.waitingTime;
			}
			return a.startTime < b.startTime;
		});

		InitVisitedProcess(data);
		ProcessData(data);
		ShowResults(data);
	}

	void ProcessData(std::vector<Process>& data)
	{
		int currentProcess = 0;

		while (!visited.empty()) {
			if (!IsProcessReady(data, currentProcess)) {
				IncreaseGlobalTimer(data);
			}
		}
	}

	void ShowResults(std::vector<Process>& data)
	{
		int waitingTime = 0;
		cout << "\n\nProcess" << "\tAppear time" << "\tWorking time" << "\tStarted time" << "\tWaiting time" << "\tFinished time" << "\tFull time" << endl;
		for (auto& process : data) {
			cout << "" << process.number << "\t"
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

	void InitVisitedProcess(std::vector<Process>& data)
	{
		for (auto process : data) {
			visited.insert(process.number);
		}
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

	pair<Process, int> GetAvailableProcess(std::vector<Process>& data) {
		int minStartTime = INT_MAX;
		int minWaitingTime = INT_MAX;
		int indexToReturn = -1;
		int index = 0;

		for (const auto& process : data) {
			if (process.staus != ProcessStatus::Finished
				&& process.staus != ProcessStatus::InProgress
				&& process.staus != ProcessStatus::Started) {

				if (process.startTime <= CommonData::GET_GLOBAL_COUNTER()) {
					if (minWaitingTime > process.waitingTime) {
						minWaitingTime = process.waitingTime;
						indexToReturn = index;
					}
				}
			}
			index = index + 1;
		}
		// No available process at this momemnt.
		if (indexToReturn == -1) {
			return { NULL, -1 };
		}
		// OK.
		return { data[indexToReturn], indexToReturn };
	}

	bool IsProcessReady(std::vector<Process>& data, int& currentProcess)
	{
		auto availableProcess = GetAvailableProcess(data);
		if (availableProcess.second != -1) {
			currentProcess = availableProcess.second;
			ChangeProcessStatus(data, currentProcess, ProcessStatus::Started);
			ProcessWorkingTime(data, currentProcess);
			ChangeProcessStatus(data, currentProcess, ProcessStatus::Finished);
			if (visited.find(data[currentProcess].number) != visited.end()) {
				visited.erase(data[currentProcess].number);
			}			

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

};

int main()
{
	mutex m;
	m.lock();
	FIFO* fifo = new FIFO();
	fifo->RunInThread();
	delete fifo;
	m.unlock();
	CommonData::SET_GLOBAL_COUNTER(-CommonData::GET_GLOBAL_COUNTER());
	m.lock();
	SJF* sjf = new SJF();
	sjf->RunInThread();
	delete sjf;
	m.unlock();

	return 0;
}
