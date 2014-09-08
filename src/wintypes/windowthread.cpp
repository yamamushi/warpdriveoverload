//
//  windowthread.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/6/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "windowthread.h"


MainWindowThread* MainWindowThread::m_pInstance = NULL;


MainWindowThread* MainWindowThread::Instance()
{
    if (!m_pInstance)   // Only allow one instance of class to be generated.
        m_pInstance = new MainWindowThread;
    
    return m_pInstance;
}



MainWindowThread::MainWindowThread(){
    
    m_started = false;
    
}




void MainWindowThread::start(){
    
    
    m_started = true;
    
}