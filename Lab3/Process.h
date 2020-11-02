#pragma once
class Segment;

enum ProcessState{
    NOT_STARTED,
    STARTED,
    IN_PROGRESS,
    STOPPED,
    FINISHED
};

class Process {
public:
    Process(int processId, int startTime, int endTime, int startAddress, int endAddress) 
    : processId(processId), startTime(startTime), endTime(endTime), startAddress(startAddress), endAddress(endAddress) {

        size = endAddress - startAddress;
        state = ProcessState::NOT_STARTED;
        segment = nullptr;
    };
    Process(const Process &obj){
        this->state = obj.state;
        this->startTime = obj.startTime;
        this->startAddress = obj.startAddress;
        this->size = obj.size;
        this->segment = obj.segment;
        this->processId = obj.processId;
        this->endTime = obj.endTime;
        this->endAddress = obj.endAddress;
    }

    
    int processId;
    int startTime;
    int endTime;
    int startAddress;
    int endAddress;
    int size;
    Segment* segment;
    ProcessState state;
};

 