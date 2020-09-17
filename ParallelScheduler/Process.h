#pragma once
#include <thread>
#include <mutex>

enum class ProcessStatus {
	WaitingIfNotStarted = -2,
	WaitingIfStarted,
	Started,
	InProgress,
	Finished
};


class Process {
public:
	Process(int number) : number(number) {
		startTime = 0;
		workingTime = 0;
		staus = ProcessStatus::WaitingIfNotStarted;

		waitingTime = 0;
	}
	Process(int number, int stratTime, int workingTime) : number(number), startTime(stratTime), workingTime(workingTime) { staus = ProcessStatus::WaitingIfNotStarted;  waitingTime = 0; }
	Process()
	{
		number = 0;
		startTime = 0;
		workingTime = 0;
		staus = ProcessStatus::WaitingIfNotStarted;

		waitingTime = 0;
	}

	void CountWaitingTime();
	bool ChangeStatus(const int& globalTimer);

	void CheckChanges(const int& globalTimer);

	std::thread ProcessThread(const int& globalTimer) {
		return std::thread(&Process::CheckChanges, this, globalTimer);
	}

	int number;
	int startTime;
	int workingTime;


	int startedTime;
	int waitingTime;
	int finishedTime;

	ProcessStatus staus;
};

 