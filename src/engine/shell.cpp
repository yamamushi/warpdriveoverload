//
//  shell.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "shell.h"
#include "wintypes/window.h"

#include "util/version.h"
#include "widgets/graphchart.h"
#include "tr1/tr1_threading.h"
#include "interfaces/navigation.h"
#include "interfaces/debugWindow.h"

#include "util/asciicodes.h"
#include "interfaces/terostest.h"

#include "engine/Hermes.h"
#include "network/NetworkMessage.h"

#include "messages/shipdata.pb.h"


#include "util/logger.h"

#include <algorithm>


#include "managers/NcursesManager.h"

void Shell::boot(){
    
    m_graphicsManager = new NcursesManager;
    
    
    if(!m_graphicsManager->start()){
        std::cout << "Error Starting Graphics Manager" << std::endl;
        exit(1);
    }
    else{
        m_rows = m_graphicsManager->getHeight();
        m_cols = m_graphicsManager->getWidth();
    }
 
    init();
    
}


void Shell::refreshShell(){
    
    m_rows = m_graphicsManager->getHeight();
    m_cols = m_graphicsManager->getWidth();
    
    for(size_t x = 0; x < m_windows.size(); x++){
        m_windows.at(x)->resize(m_rows, m_cols, 0, 0);
    }
    
    if(m_topInterface){
        m_topInterface->getWindow()->clearScreen();
        m_topInterface->getWindow()->refresh();
    }
}

bool Shell::init(){

    
    
    /*
    //std::cout << "Command Queue Starting" << std::endl;
    Hermes::Instance()->addToCommandQueue(_STD_BIND(&Shell::doNothing, this));
    sleep(1);
    
    //std::cout << "Network Message Interface Starting" << std::endl;

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    WarpDriveOverloaded::User *testUser = new WarpDriveOverloaded::User;
    
    testUser->set_name("Bob Saget");
    testUser->set_id(1);
    testUser->set_email("bob.saget@gmail.com");
    
    WarpDriveOverloaded::User_Character testCharacter = testUser->character();
    testUser->character().name();
    testCharacter.set_name("test");
    
    std::string output;
    testUser->SerializeToString(&output);
    //testUser->Serializeto

    
   // archive << newMessage;
    
    logger m_logmaker("proto.log", 0);
   // m_logmaker.logToFile(newUser.name(),0);
    
    

    NetworkMessage netMessage;
    netMessage.body_length(std::strlen(output.c_str()));
    std::string testarray;
    testUser->SerializeToArray(netMessage.body(), netMessage.body_length());
    //std::memcpy(netMessage.body(), &output, netMessage.body_length());
    
    
    WarpDriveOverloaded::User newUser;
    newUser.ParseFromString(netMessage.body());
    m_logmaker.logToFile(newUser.name(),0);
    
    
    netMessage.encode_header();
    Hermes::Instance()->addToNetworkQueue(netMessage);
*/
    
    //Hermes::Instance()->startNetworkQueue();
    
    return true;
    
}



bool Shell::run(){
    
    initMainWindow();
    organizeInterfaces();
    
    if(!m_topInterface){
        // Something went wrong this should not happen
        return false;
    }
    
    // This is about to get fun
    nodelay(stdscr, true);
    int keyInput;
    
    // Wait (int) seconds while loop is running
    // 1000 = 1 Second
    //timeout(1000);
    setmaxfps(10);

    m_running = true;

    while(m_running)
	{
        refresh();
        doupdate();

        if((keyInput = getch()) == ERR){
            execute();
        }
        else{
            handleKeys(keyInput);
            execute();
        }
        m_topInterface->getWindow()->refresh();
        m_topInterface->getWindow()->render();

        FpsCounter::Instance()->update();
    }
    
    shutdown();
    
    return true;
}




void Shell::initMainWindow(){

    m_topInterface = m_interfaceList.at(0);

    m_topInterface->init();
    
}

void Shell::execute(){
    
    if(checkForResize()){
        m_topInterface->getWindow()->clearScreen();
        m_topInterface->resizeConsole(m_cols, m_rows);
        m_topInterface->getWindow()->refresh();
    }

    if(!m_topInterface->initialized()){
        m_topInterface->getWindow()->clearScreen();
        m_topInterface->init();
    }
    m_topInterface->run();
}


void Shell::handleKeys(int input){
    
    switch(input)
    {
        // This is defined in asciicodes.h
        case KEY_TAB:
            m_topInterface->getWindow()->clearScreen();
            m_topInterface->getWindow()->refresh();
            
            if(m_topInterface->getNext() == m_interfaceList.at(0))
                m_topInterface = m_interfaceList.at(1);
            else
                m_topInterface = m_topInterface->getNext();

            m_topInterface->getWindow()->clearScreen();
            break;
            
        default:
            m_topInterface->handleKeys(input);
            break;
    }
}



bool Shell::checkForResize(){
    
    int newRows, newCols;
    
    getmaxyx(stdscr, newRows, newCols);

    if(newRows != m_rows || newCols != m_cols){
        m_rows = newRows;
        m_cols = newCols;
        return true;
    }
    else
        return false;
}


int Shell::getfps(){
    
    return m_graphicsManager->getfps();
    
}


void Shell::setmaxfps(int fps){
    
    m_graphicsManager->setmaxfps(fps);
    
}


void Shell::loadInterfaces(_SharedPtr<Shell> parent){
    
    // Launch our debug Interface which will attach to the root Interface on this shell
    _SharedPtr<DebugInterface> debugInterface(new DebugInterface(parent));
    addToInterfaceList(debugInterface);
    
    _SharedPtr<TerosTestInterface> terosTest(new TerosTestInterface(parent));
    addToInterfaceList(terosTest);
    
    _SharedPtr<NavigationInterface> navigationInterface(new NavigationInterface(parent));
    addToInterfaceList(navigationInterface);
    
    initMainWindow();

}

void Shell::populateInterfaces(){
    
    organizeInterfaces();
    
}



void Shell::printDebug(){
    
    mvwprintw(stdscr, m_rows/2, m_cols/2, "%s", "Testing Debug Output");
    
}



void Shell::quit(){
    
    m_running = false;
    
}



void Shell::addToInterfaceList(_SharedPtr<Interface> target){
    
    m_interfaceList.push_back(target);

    size_t InterfaceListSize = m_interfaceList.size();

    if(InterfaceListSize > 0){
        
        m_interfaceList.at(InterfaceListSize-1)->addNext(m_interfaceList.back());
        m_interfaceList.back()->addPrev(m_interfaceList.at(InterfaceListSize-1));
        m_interfaceList.back()->addNext(m_interfaceList.at(0));
        
    }
}



void Shell::organizeInterfaces(){
    
    size_t InterfaceListSize = m_interfaceList.size();
    
    for(size_t x = 0; x < m_interfaceList.size(); x++){
        
        if(x > 0){

            m_interfaceList.at(x-1)->addNext(m_interfaceList.at(x));
            m_interfaceList.at(x)->addPrev(m_interfaceList.at(x-1));
            
        }
        else{
            m_interfaceList.back()->addNext(m_interfaceList.at(0));
            m_interfaceList.back()->addPrev(m_interfaceList.at(0));
        }
    }
    
    m_interfaceList.back()->addPrev(m_interfaceList.at(InterfaceListSize-2));
    m_interfaceList.back()->addNext(m_interfaceList.at(0));
    
}



void Shell::createWindow(int ysize, int xsize){
    
    _SharedPtr<GenericWindow> new_window = _SharedPtr<GenericWindow>(new GenericWindow(m_rows, m_cols, 0, 0)); // Initialize our root window
    m_windows.push_back(new_window); // Add to the list of Windows for the window manager.
    
}


void Shell::addToWindowList(_SharedPtr<GenericWindow> target){
    
    m_windows.push_back(target); // Add to the list of Windows for the window manager.
    
}


void Shell::removeFromInterfaceList(_SharedPtr<Interface> target){
    
    std::vector<_SharedPtr<Interface>>::iterator it = std::find(m_interfaceList.begin(), m_interfaceList.end(), target);
    if (it != m_interfaceList.end()){
        m_interfaceList.erase(std::remove(m_interfaceList.begin(), m_interfaceList.end(), target), m_interfaceList.end());
    }
    
}



void Shell::removeFromWindowList(_SharedPtr<GenericWindow> target){
    
    std::vector<_SharedPtr<GenericWindow>>::iterator it = std::find(m_windows.begin(), m_windows.end(), target);
    if (it != m_windows.end()){
        m_windows.erase(std::remove(m_windows.begin(), m_windows.end(), target), m_windows.end());
    }
    
}



void Shell::shutdown(){
    
    for(size_t x = 0; x < m_windows.size(); x++){
        m_windows.at(x)->close();
    }
    endwin();
    
}


void Shell::close_win(_SharedPtr<GenericWindow> target_window){
    
    target_window->close();
    
}
