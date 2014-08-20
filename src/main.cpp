// BootStrap

#include <iostream>
#include <string>
#include <memory>

#include "term_control.h"
#include "player.h"
#include "room.h"

int main(){
    
    std::shared_ptr<Player> one_player = std::make_shared<Player>("Fred");
    
    Room room_one = Room(5,5,5);
    room_one.enterDescription("A cold dark room with no windows");
    
    room_one.addEntity(one_player);
    
    
    
    while(true){
        
        std::string command;
        std::cout << term_reset + "> ";
        
        std::cin >> command;
        
        if(command == "l" || command == "look"){
            std::cout << room_one.getDescription() << std::endl;
        }
        else if(command == "h" || command == "help"){
            std::cout << "Valid Commands are: look, help" << std::endl;
        }
        else{
            std::cout << "Unknown Command: " + command << std::endl;
        }
        
    }
    
    return 0;
    
}