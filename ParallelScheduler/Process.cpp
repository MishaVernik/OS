#include "Process.h"
#include "CommonData.h"
#include <iostream>

void Process::CountWaitingTime() {
	if (this->staus == ProcessStatus::WaitingIfStarted) {
		this->waitingTime = this->waitingTime + CommonData::WAITING_TIME();
	}
}

bool Process::ChangeStatus(const int& globalTimer)
{
	if (this->startTime <= globalTimer
		&& this->staus != ProcessStatus::Finished
		&& this->staus != ProcessStatus::InProgress
		&& this->staus != ProcessStatus::Started) {

		this->staus = ProcessStatus::WaitingIfStarted;

		return true;
	}
	return false;
}

void Process::CheckChanges(const int& globalTimer)
{
	std::lock_guard<std::mutex> lock(m);
#ifdef DEBUG
	std::cout << this->number << " ";
#endif // DEBUG

	this->ChangeStatus(globalTimer);
	this->CountWaitingTime();

}
