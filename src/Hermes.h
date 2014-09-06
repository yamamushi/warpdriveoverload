//
//  Hermes.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/6/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__Hermes__
#define __warpdriveoverloaded__Hermes__

#include "tr1_threading.h"
#include "messagequeue.h"

class Hermes
{
    
public:
    
    static Hermes* Instance();
    
    void start();
    void stop();
    
    void addToCommandQueue(_STD_FUNCTION(void()) command);
    bool processingCommand();

    
protected:
    
    void run();
    _ATOMIC(m_running);

    int getCommandQueueSize();
    void clearCommandQueueQueue();
    
    
private:
    
    // Constructor
    Hermes();
    
    Hermes(Hermes const&){};
    Hermes& operator=(Hermes const&);
    
    static Hermes* m_pInstance;

    bool m_started;
    
    
    bool parseNextCommand();
    
    MsgQueue<_STD_FUNCTION(void())> CommandQueue;

    
    _THREAD m_thread;
    _MUTEX(m_commandQueueprocessing);
    CONDITION_VARIABLE(m_commandQueueconditional);
    
    _ATOMIC(m_commandQueueworking);
    
};



#endif /* defined(__warpdriveoverloaded__Hermes__) */
