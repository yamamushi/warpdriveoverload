#pragma once

/*

A thread-safe global logging utility function.

-Yamamushi


 */


#include <string>
#include <utility>

#include "util/messagequeue.h"
#include "tr1/tr1_threading.h"
#include "tr1/tr1_wrapper.h"

class GlobalLogger {

public:

    static GlobalLogger* Instance();
    void writeToLogFile(std::string logFile, std::string output);


private:

    void logToFileCommand(std::string logFile, std::string output);


    // Command Queue Thread Things
    void addToCommandQueue(std::pair<std::string, std::string> command);
    bool processingCommand();

    void runCommandQueue();

    void startCommandQueue();
    void stopCommandQueue();

    bool parseNextCommand();

    _ATOMIC(m_commandQueuerunning);

    int getCommandQueueSize();
    void clearCommandQueue();

    MsgQueue<std::pair<std::string, std::string>> CommandQueue;

    _THREAD m_commandQueuethread;
    _MUTEX(m_commandQueueprocessing);
    CONDITION_VARIABLE(m_commandQueueconditional);
    _ATOMIC(m_commandQueueworking);




    GlobalLogger(){};  // Private so that it can  not be called
    GlobalLogger(GlobalLogger const&){};             // copy constructor is private

    // Ignore the compiler warnings here, this is something we want
    // The copy operator should always be private in a singleton!
    GlobalLogger& operator=(GlobalLogger const&);  // Ignore the compiler! This Assignment operator is private!
    static GlobalLogger* m_pInstance;

};
