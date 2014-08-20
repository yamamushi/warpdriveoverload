// BootStrap

#include <iostream>
#include <string>
#include <memory>

#include "player.h"
#include "room.h"

int main(){
    
    std::shared_ptr<Player> one_player = std::make_shared<Player>("Fred");
    
    Room room_one = Room(5,5,5);
    room_one.enterDescription("A cold dark room with no windows");
    
    room_one.addEntity(one_player);
    
    std::cout << room_one.getDescription() << std::endl;
    
    return 0;
    
}