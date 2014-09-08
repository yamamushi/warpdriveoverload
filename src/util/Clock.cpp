//
//  Clock.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/6/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "Clock.h"


FpsCounter* FpsCounter::m_pInstance = NULL;


FpsCounter* FpsCounter::Instance()
{
    if (!m_pInstance)   // Only allow one instance of class to be generated.
        m_pInstance = new FpsCounter;
    
    return m_pInstance;
}

