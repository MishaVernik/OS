#include "OperationSystem.h"


OperationSystem::OperationSystem(){

}

OperationSystem::~OperationSystem(){
    
}

std::string OperationSystem::GetProgressBar(float progress){
    
    int barWidth = 20;
    std::string progressBar = "";
    progressBar += this->item  + "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) progressBar += "=";
        else if (i == pos) progressBar += ">";
        else progressBar += " ";
    }   
    progressBar +="] " +  to_string((int)(progress * 100.0)) + " %\n";
    //std::cout.flush();
    return progressBar;
}

void  OperationSystem::getAddress(){

    this->mx.lock();
    item = " \t *";
    int pid;
    set_cursor_pos(10, 8,  this->item + "Please enter process Id: ");
    std::cin >> pid;    
    for (auto process : this->processes){
        if (process.processId == pid){
            set_cursor_pos(10, 9,  this->item + " Start address: ");             
            if (process.segment == nullptr){
                std::cout <<"This proccess not in the memory!\n";
            }else{
                std::cout << "\t" << process.segment->startAddress + process.startAddress << "\n";
            }
            
            break;
        }
    }
    item = " \t *\t";
    getch();
    this->mx.unlock();
}

void OperationSystem::RunSimulation(){
    this->mx.lock();
    // If the Disk speed much bigger than MEMORY SIZE
    // then we can say that loading process into memory takes 0 seconds!   
   for (auto& process: this->processes){
        if (process.endTime < this->TIMER && process.state != ProcessState::NOT_STARTED && process.state != ProcessState::FINISHED){
            process.state = ProcessState::FINISHED;
            process.segment->state = State::FREE;
            
            clear_real_time_table();
        }else if (process.startTime > this->TIMER && process.endTime < this->TIMER && process.state == ProcessState::STARTED){
            process.state = ProcessState::IN_PROGRESS;
        } 
    }
    for (auto& process: this->processes){
        if (process.startTime > this->TIMER){
            process.state = ProcessState::NOT_STARTED;
        }else if (process.startTime <= this->TIMER && process.state == ProcessState::NOT_STARTED){                       
            for (auto& segment : this->segments){
                if (segment.state == State::FREE && segment.size >= process.size){                    
                    segment.process = &process;
                    segment.state = State::OCCUPIED;
                    
                    process.segment = &segment;
                    process.state = ProcessState::STARTED;
                    
                    break;
                }
            }
        }else if (process.startTime > this->TIMER && process.endTime < this->TIMER && process.state == ProcessState::STARTED){
            process.state = ProcessState::IN_PROGRESS;
        } 
    } 
    this->mx.unlock(); 
}
 
void OperationSystem::ShowAllInRealTime(){
    this->mx.lock();
    this->item = "";
    int column = 7;
    int row = 70;
    cout << "\n";
    set_cursor_pos(row,column++,  this->item + "MEMORY SIZE: " +  to_string(this->MEMORY_SIZE) + "\n");
 
    set_cursor_pos(row,column++, this->item + "Segment ID\tStart address\tEnd address\tSize\tProcess Id\tState\n");    
    for (auto segment : this->segments){
        
        float progress = (segment.process == nullptr || segment.state == State::FREE) ? 0 : (segment.process->size)  / (float)segment.size;
        set_cursor_pos(row,column, string(100, ' '));
        set_cursor_pos(row,column++,  this->item  + to_string(segment.segmentId) + "\t\t" + to_string(segment.startAddress) + "\t\t" + 
        to_string(segment.endAddress - 1) + "\t\t" + to_string(segment.size) + "\t" + ((segment.process == nullptr || segment.state == State::FREE) ? "-"  : to_string(segment.process->processId)) + "\t" +
        ((segment.state == State::FREE) ?"Free" : "Occupied") + " " +  this->GetProgressBar(progress));          
    }
    column++;
    set_cursor_pos(row,column++, this->item + "Process queue number: " + to_string(this->processes.size()) + "\n");        
    set_cursor_pos(row,column++, this->item + "Process ID\tStart time\tEnd time\tStart address\tEnd address\tSize\tState\n");    
    for (auto process : this->processes){
        string state = "";
        switch (process.state)
        {
            case  ProcessState::NOT_STARTED :
                state = "NOT_STARTED";
                break;
            case  ProcessState::STARTED :
                state = "STARTED";
                break;
            case  ProcessState::IN_PROGRESS :
                state = "IN_PROGRESS";
                break;
            case  ProcessState::STOPPED :
                state = "STOPPED";
                break;
            case  ProcessState::FINISHED :
                state = "FINISHED";
                break;            
            default:
                break;
        }
        std::string s = this->item  +
         to_string(process.processId) +
          "\t\t" +
           to_string(process.startTime) + "\t\t" + to_string(process.endTime) + "\t\t" + to_string(process.startAddress) +
            "\t\t" + to_string(process.endAddress - 1) + "\t\t" + to_string(process.size) + "\t";
            
        set_cursor_pos(s.size() + row,column, string(state.size() + 120, ' '));
        set_cursor_pos(row,column, s + state + "\n");        
        column++;
    }
     this->item = " \t *\t";
     this->mx.unlock();
}
void OperationSystem::ShowAll(){

    cout << "\n"<< this->item << "MEMORY SIZE: " << this->MEMORY_SIZE << "\n";
    cout << this->item << "Segment ID\tStart address\tEnd address\tSize\tProcess Id\tState\n";
    for (auto segment : this->segments){
        float progress = (segment.process == nullptr || segment.state == State::FREE) ? 0 : (segment.process->size)  / (float)segment.size;
        cout <<this->item  + to_string(segment.segmentId) + "\t\t" + to_string(segment.startAddress) + "\t\t"  
        + to_string(segment.endAddress - 1) + "\t\t" + to_string(segment.size) + "\t" + ((segment.process == nullptr || segment.state == State::FREE) ? "-"  : to_string(segment.process->processId)) + "\t" +
        ((segment.state == State::FREE) ?"Free" : "Occupied") + " " +  this->GetProgressBar(progress);          
    }
    cout << "\n";
    cout << this->item << "Process queue number: " << this->processes.size() << "\n";
    cout << this->item << "Process ID\tStart time\tEnd time\tStart address\tEnd address\tSize\tState\n";
    for (auto process : this->processes){
        string state = "";
        switch (process.state)
        {
            case  ProcessState::NOT_STARTED :
                state = "NOT_STARTED";
                break;
            case  ProcessState::STARTED :
                state = "STARTED";
                break;
            case  ProcessState::IN_PROGRESS :
                state = "IN_PROGRESS";
                break;
            case  ProcessState::STOPPED :
                state = "STOPPED";
                break;
            case  ProcessState::FINISHED :
                state = "FINISHED";
                break;            
            default:
                break;
        }        
        cout << this->item  <<
         process.processId <<
          "\t\t" <<
           process.startTime << "\t\t" << process.endTime << "\t\t" << process.startAddress << "\t\t" << process.endAddress - 1 << "\t\t" << process.size << "\t" << state << "\n";        
    }
     
}
void OperationSystem::DeleteSegment(int segmentId){
    
}

void OperationSystem::SetMemory(){            
    set_cursor_pos(47, 6, "\n" + this->item + "Please enter the memory size: ");
    std::cin >> this->MEMORY_SIZE;
}

void OperationSystem::AddSegment(){
    int startPos = 0;
    int endPos = -1;
    do {
        if (startPos == endPos){
            cout << "\n" << this->item << "The start segment position must be less than end position.\n";            
        }
        cout << "\n"<< this->item <<"Start position: ";
        std::cin >> startPos;
        cout << "\n"<< this->item <<"End position: ";
        std::cin >> endPos;
        if (endPos > this->MEMORY_SIZE){
            cout << "\n"<< this->item <<"The end segment position must be less or equal than MEMORY SIZE.\n";            
        }
        bool isCrossed = false;
        for (auto segment : this->segments){            
            if (segment.startAddress < endPos && segment.endAddress > startPos){                
                isCrossed = true;
                cout << "\n"<< this->item <<"There is a cross in memory.\n";
                // Show current memory table.     
                this->ShowAll();       
                break;
            }
        }
        if (isCrossed){            
            endPos = startPos - 1;
        }
    } while (startPos > endPos);
    
    this->segments.push_back(Segment(this->segments.size() + 1, startPos, endPos));

    sort(this->segments.begin(), this->segments.end(),[](Segment& left, Segment& right){
        return left.startAddress < right.startAddress;
    });  
}

void OperationSystem::AddProcess(){
    int startPos = 0;
    int endPos = 0;

    int startTime = 0;
    int endTime = 0;
    int times = 0;
    do {
        if (startPos >= endPos){
            cout << "\n"<< this->item <<"The start process position must be less than end position.\n";            
        }else
        if (startTime >= endTime){
            cout << "\n"<< this->item <<"The start time must be less than end time.\n";            
        }
        cout << "\n"<< this->item <<"Start position: ";
        std::cin >> startPos;
        cout << "\n"<< this->item <<"End position: ";
        std::cin >> endPos;
        
        cout << "\n"<< this->item <<"Start time: ";
        std::cin >> startTime;
        cout << "\n"<< this->item <<"End time: ";
        std::cin >> endTime;
        
        times++;
    } while ((startPos > endPos || startTime > endTime) || times > 2);
    if (startPos > endPos || startTime > endTime){
        // Error message.
        // The proccess hasn't been added to the Queue.
    }else{
        this->processes.push_back(Process(this->processes.size() + 1, startTime, endTime, startPos, endPos));
    }

    sort(this->processes.begin(), this->processes.end(),[](Process& left, Process& right){
        return left.startTime > right.startTime;
    });  
}