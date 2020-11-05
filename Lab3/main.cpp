#include "menu.h"
#include "msoftcon.h"

using namespace std;

void Simulation(){
    
    init_graphics();
    OperationSystem* os = new OperationSystem();

    Menu m("Fixed Memory");
    
    m.SetOperationSystem(os);
    m.addItem("Set memory size");
    m.addItem("Add segment");
    m.addItem("Delete segment");
    m.addItem("Add process");
    m.addItem("Show all");    
    m.addItem("Run simulation");    
    m.addItem("Stop simulation");        
    m.addItem("Virtual to Physical");        
    m.addItem("Exit"); 
    

    m.RunThreads();  
}

int main()
{
    Simulation();

    return 0;
}