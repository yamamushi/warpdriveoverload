#include"logger.h"

#include "tr1/tr1_threading.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "util/Clock.h"


GlobalLogger* GlobalLogger::m_pInstance = NULL;


GlobalLogger *GlobalLogger::Instance() {

    if (!m_pInstance)   // Only allow one instance of class to be generated.
        m_pInstance = new GlobalLogger;

    return m_pInstance;
}


void GlobalLogger::writeToLogFile(std::string logFile, std::string output) {

    std::pair<std::string, std::string> logOutput(logFile, output);
    addToCommandQueue(logOutput);
}

void GlobalLogger::addToCommandQueue(std::pair<std::string, std::string> command) {
    CommandQueue.push(command);
    startCommandQueue();
}

bool GlobalLogger::processingCommand() {
    return _ATOMIC_ISTRUE(m_commandQueueworking);
}

void GlobalLogger::runCommandQueue() {
    while(m_commandQueuerunning){
        if(!parseNextCommand()){
            break;
        }
    }
}

void GlobalLogger::logToFileCommand(std::string logFile, std::string output) {

    std::ofstream log_file( logFile, std::ofstream::app );
    log_file << Clock::getTimeString() << " : " << output << std::endl;

    //log_file.close(); // Called automatically when log_file is destroyed

}

void GlobalLogger::startCommandQueue() {

    if(!m_commandQueuerunning){
        m_commandQueuerunning = true;
        m_commandQueuethread = _THREAD(&GlobalLogger::runCommandQueue, this);
        return;
    }
}

void GlobalLogger::stopCommandQueue() {
    if(!m_commandQueuerunning){
        INSTANTIATE_MLOCK(m_commandQueueprocessing); // Don't stop the thread in the middle of processing
        m_commandQueuerunning = false;
        m_commandQueuethread.join();
        mlock.unlock();
        return;
    }
}

bool GlobalLogger::parseNextCommand() {
    if(getCommandQueueSize() == 0){
        return false;
    }

    INSTANTIATE_MLOCK(m_commandQueueprocessing);  // Don't let other functions interfere with our message parsing

    m_commandQueueworking = true; // Notify our atomic boolean that we are in the middle of a process

    std::pair<std::string, std::string> message = CommandQueue.pop();  // Pull out our function to run

    logToFileCommand(message.first, message.second);

    mlock.unlock();
    m_commandQueueconditional.notify_one(); // Let other functions know that we're done and they can continue.
    // This is primarily for when a request comes in to shut down the queue
    // While an action is in progress. This will notify our stop handler that it is safe
    // To shut down the thread.

    m_commandQueueworking = false; // Notify our atomic boolean that we are done with our processing
    //m_logger->logToFile("Command Processed", 0);

    return true;
}

int GlobalLogger::getCommandQueueSize() {
    return CommandQueue.size();
}

void GlobalLogger::clearCommandQueue() {
    CommandQueue.clear();

}
