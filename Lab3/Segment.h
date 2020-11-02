#pragma once
#include "Process.h"

enum State{
    FREE,
    OCCUPIED
};

class Segment {
public:
    Segment(int segmentId, int startAddress, int endAddress) : segmentId(segmentId), startAddress(startAddress), endAddress(endAddress){
        state = State::FREE;
        size = endAddress - startAddress;
        process = nullptr;
    }
    Segment(const Segment &obj){
        this->segmentId = obj.segmentId;      
        this->startAddress = obj.startAddress;
        this->size = obj.size;       
        this->endAddress = obj.endAddress;
        this->state = obj.state;
        this->process = obj.process;
    }

    int segmentId;
    int startAddress;
    int endAddress;
    int size;
    Process* process;
    State state;
};