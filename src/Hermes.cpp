//
//  Hermes.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/6/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "Hermes.h"
#include <iostream>
#include <string>

#include "shipdata.pb.h"


Hermes* Hermes::m_pInstance = NULL;


Hermes* Hermes::Instance()
{
    if (!m_pInstance)   // Only allow one instance of class to be generated.
        m_pInstance = new Hermes;
    
    return m_pInstance;

}



Hermes::Hermes(){
    
    m_logger = new logger("hermes.log", 0);
    
}

// Command Queue Commands

void Hermes::startCommandQueue(){
    
    if(!m_commandQueuerunning){
        m_commandQueuerunning = true;
        m_commandQueuethread = _THREAD(&Hermes::runCommandQueue, this);
        return;
    }

}


void Hermes::stopCommandQueue() {
    
    if(!m_commandQueuerunning){
        INSTANTIATE_MLOCK(m_commandQueueprocessing); // Don't stop the thread in the middle of processing
        m_commandQueuerunning = false;
        m_commandQueuethread.join();
        mlock.unlock();
        return;
    }
}


bool Hermes::processingCommand(){
    
    return _ATOMIC_ISTRUE(m_commandQueueworking);
    
}

void Hermes::addToCommandQueue(_STD_FUNCTION(void()) command){
    
    CommandQueue.push(command);
    startCommandQueue();
    
}



int Hermes::getCommandQueueSize(){
    
    return CommandQueue.size();
    
}


void Hermes::clearCommandQueue(){
    
    CommandQueue.clear();
    
}



void Hermes::runCommandQueue(){
    
    while(m_commandQueuerunning){
        if(!parseNextCommand()){
            break;
        }
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
    //m_logger->logToFile("Command Processed", 0);
    
    return true;
}




// Network Queue Functions

void Hermes::startNetworkQueue(){
    
    if(!m_networkQueuerunning){
        m_networkQueuerunning = true;
        m_networkQueuethread = _THREAD(&Hermes::runNetworkQueue, this);
        return;
    }
}

void Hermes::stopNetworkQueue(){
    
    if(!m_networkQueuerunning){
        INSTANTIATE_MLOCK(m_networkQueueprocessing); // Don't stop the thread in the middle of processing
        m_networkQueuerunning = false;
        m_networkQueuethread.join();
        mlock.unlock();
        return;
    }
    
}

void Hermes::addToNetworkQueue(NetworkMessage message){
    
    NetworkQueue.push(message);
    startNetworkQueue();
    
}

bool Hermes::processingNetworkQueue(){
    
    return _ATOMIC_ISTRUE(m_networkQueueworking);

}


void Hermes::runNetworkQueue(){
    
    while(m_networkQueuerunning){
        if(!parseNextNetworkMessage()){
            break;
        }
    }
    
}

int Hermes::getNetworkQueueSize(){
    
    return NetworkQueue.size();

}
void Hermes::clearNetworkQueue(){
    
    NetworkQueue.clear();

}

bool Hermes::parseNextNetworkMessage(){
    
    if(getNetworkQueueSize() == 0){
        return false;
    }
    
    INSTANTIATE_MLOCK(m_networkQueueprocessing);  // Don't let other functions interfere with our message parsing
    
    m_networkQueueworking = true; // Notify our atomic boolean that we are in the middle of a process
    
    //_STD_FUNCTION(void()) message = CommandQueue.pop();  // Pull out our function to run
    
    NetworkMessage message = NetworkQueue.pop();
    
    //int messageHeaderLength = NetworkMessage::header_length;
    //char buffer[NetworkMessage::header_length];
    
    if(message.decode_header()){
        
        //boost::asio::buffer(read_msg_.body(), read_msg_.body_length())
        m_logger->logToFile("Message length is: " + std::to_string(message.body_length()), 0);

        WarpDriveOverloaded::User testUser;
        if(!testUser.ParseFromArray(message.body(), message.body_length())){
           
            m_logger->logToFile("Message Parse Failure", 0);

        }
        else{
            std::string username = testUser.name();
            m_logger->logToFile("Message Body is: " + username, 0);
        }


        
    }
    
    //message();
    
    mlock.unlock();
    // Let other functions know that we're done and they can continue.
    // This is primarily for when a request comes in to shut down the queue
    // While an action is in progress. This will notify our stop handler that it is safe
    // To shut down the thread.
    m_networkQueueconditional.notify_one();

    
    m_networkQueueworking = false; // Notify our atomic boolean that we are done with our processing
    //m_logger->logToFile("Network Message Processed", 0);

    
    return true;
    
}

