//
//  Hermes.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/6/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "Hermes.h"


Hermes* Hermes::m_pInstance = NULL;


Hermes* Hermes::Instance()
{
    if (!m_pInstance)   // Only allow one instance of class to be generated.
        m_pInstance = new Hermes;
    
    return m_pInstance;
}



Hermes::Hermes(){
    
    m_started = false;
    
}




void Hermes::start(){
    
    if(!m_running){
        m_running = true;
        m_thread = _THREAD(&Hermes::run, this);
        return;
    }

}


void Hermes::stop() {
    
    if(!m_running){
        INSTANTIATE_MLOCK(m_commandQueueprocessing); // Don't stop the thread in the middle of processing
        m_running = false;
        m_thread.join();
        mlock.unlock();
        return;
    }
}

bool Hermes::processingCommand(){
    
    return _ATOMIC_ISTRUE(m_commandQueueworking);
    
}

void Hermes::addToCommandQueue(_STD_FUNCTION(void()) command){
    
    CommandQueue.push(command);
    
}



int Hermes::getCommandQueueSize(){
    
    return CommandQueue.size();
    
}


void Hermes::clearCommandQueueQueue(){
    
    CommandQueue.clear();
    
}



void Hermes::run(){
    
    while(m_running){
        parseNextCommand();
    }
    
}


bool Hermes::parseNextCommand(){
    
    if(getCommandQueueSize() == 0){
        return false;
    }
    
    INSTANTIATE_MLOCK(m_commandQueueprocessing);  // Don't let other functions interfere with our message parsing
    
    m_commandQueueworking = true; // Notify our atomic boolean that we are in the middle of a process
    
    _STD_FUNCTION(void()) message = CommandQueue.pop();  // Pull out our function to run
    
    message();
    
    mlock.unlock();
    m_commandQueueconditional.notify_one(); // Let other functions know that we're done and they can continue.
    // This is primarily for when a request comes in to shut down the queue
    // While an action is in progress. This will notify our stop handler that it is safe
    // To shut down the thread.
    
    m_commandQueueworking = false; // Notify our atomic boolean that we are done with our processing
    
    
    return true;
}

