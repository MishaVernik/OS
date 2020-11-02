#include "menu.h"

// ============ MenuItem =====================
MenuItem::MenuItem(string item, color col) {
    this->item = item;
    this->col = col;
}

// ============ Menu =========================
Menu::Menu(string name, color col) {
    this->col = col;
    this->name = name;
    pos = 0;
    items.clear();
}

void Menu::SetOperationSystem(OperationSystem *operationSystem){
    this->operationSystem = operationSystem;
}
void Menu::print(){    
    // print border
    clear_screen();        
    set_cursor_pos(10,5, std::string(160, '*'));

    for (int i=0;i<13;i++) {
        set_cursor_pos(10,5+i, "*");        
        set_cursor_pos(169,5+i, "*");        
    }
 
    set_cursor_pos(10,18, std::string(160, '*'));
    
    
    string s = name;
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    set_cursor_pos(40-name.length()/2-1, 5, " " + s + " ");    
}
void Menu::RunThreads(){     
    std::thread t1(&Menu::show, this);
    std::thread t2(&Menu::RunSimulation, this);

    t1.join();
    t2.join();      
}
void Menu::printItems(){
    for (int i=0; i<items.size(); i++) {
        set_color(DEFAULT_COLOR);
        set_cursor_pos(14,7+i, to_string(i+1));                
        set_color(items.at(i).col);
        set_cursor_pos(17,7+i, items.at(i).item + "\n" );        
    }

    printCarret();
    printScroll();

    char c = 0;
    do {
        c = getch();
        if (c != 0 && c!= -32) {
            switch(c) {
                case 'w': case 'W': pos--; break;
                case 's': case 'S': pos++; break;
            }
        } else {
            c = getch();
            switch(c) {
                case 72: pos--; break;
                case 80: pos++; break;
            }
        }
        if (pos < 0) pos = items.size()-1;
        if (pos >= items.size()) pos = 0;
        printCarret();
        printScroll();     
    } while (c != 13 && c != 27);    
  
}

void Menu::show() {
    while(true){
        this->print();
        //
        this->printItems();
        pos++;
        bool state = this->isRunSimualtion;
        switch (pos)
            {
                case 1:       
                    this->isRunSimualtion = false;
                    this->print();        
                    this->operationSystem->SetMemory();        
                    //this->isRunSimualtion = true;    
                    clear_menu();                  
                    break;
                case 2:         
                    this->isRunSimualtion = false;
                    this->print();       
                    this->operationSystem->AddSegment();       
                    //this->isRunSimualtion = true;                       
                    clear_menu();
                    break;
                case 3:
                    this->isRunSimualtion = false;
                    this->print();
                    this->operationSystem->DeleteSegment(0);                
                    //this->isRunSimualtion = true;              
                    clear_menu();
                    break;
                case 4:
                    this->isRunSimualtion = false;
                    this->print();
                    this->operationSystem->AddProcess();  
                    //this->isRunSimualtion = true;              
                    clear_menu();
                    break;
                case 5:
                    this->isRunSimualtion = false;
                    this->print();
                    this->operationSystem->ShowAll();                    
                    cin.get();
                    //this->isRunSimualtion = true;              
                    clear_menu();
                    break;
                case 6:         
                    this->isRunSimualtion = true;
                    clear_menu();
                    break;
                case 7:         
                    state = false;
                    this->isRunSimualtion = false;
                    clear_menu();
                    break;
                case 8:                
                default:
                    this->print();
                    exit(0);
                    break;
            }
            if (state){
                this->isRunSimualtion = true;
            }
            pos--; 
    }   
}

void Menu::RunSimulation(){       
    while (true){                
        if (this->isRunSimualtion){
            this->operationSystem->TIMER++;
            set_cursor_pos(80,5," TIME: " + to_string(this->operationSystem->TIMER) + " \n");    
            // RUN SYSTEM
            this->operationSystem->RunSimulation();                  
            this->operationSystem->ShowAllInRealTime();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));                                        
        }        
    }    
}

void Menu::addItem(string item, color col) {
    MenuItem mi(item, col);
    items.push_back(mi);
}

void Menu::clearItems() {
    items.clear();
}

int Menu::returnChoise() {
    return pos;
}

void Menu::printScroll() {
    for (int i=0;i<10; i++) {
        set_cursor_pos(65,7+i, "");        
        printf("%c", 176);
    }
    
    if (items.size()>10)        
        set_cursor_pos(65,7, "█");
}

void Menu::printCarret() {
    for (int i=0;i<10; i++) {
        set_cursor_pos(12,7+i, " ");        
    }

    set_color(cWHITE);
    set_cursor_pos(12, 7+pos, ">");    
}
