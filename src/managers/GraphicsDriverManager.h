#pragma once
//
//  GraphicsDriverManager.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/7/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__GraphicsDriverManager__
#define __warpdriveoverloaded__GraphicsDriverManager__

#include "engine/shell.h"
#include "wintypes/window.h"
#include "tr1/tr1_wrapper.h"

#include <string>

class GraphicsDriverManager {
    
public:
    
    GraphicsDriverManager(){m_rawStarted = false;}
    
    virtual bool start(){return false;};
    
    virtual int getWidth(){return 0;};
    virtual int getHeight(){return 0;};
    bool getStarted(){return m_started;}
    
    virtual int getfps(){return 0;};
    virtual void setmaxfps(int fps){};
    
    virtual _SharedPtr<GenericWindow> getNewWindow(){return _SharedPtr<GenericWindow>(new GenericWindow(getHeight(), getWidth(), 0, 0));}
    
    virtual int getInput(){return -1;}
    
    virtual bool getRawStatus(){return m_rawStarted;};
    virtual void startRawInputFeed(){m_rawStarted = true;};
    virtual void stopRawInputFeed(){m_rawStarted = false;};

    
    virtual void shutdown(){};
    
protected:
    
    friend class Shell;
    
    bool m_started;
    bool m_inputInitialized;

    int m_rows, m_cols;
    int m_width, m_height;
    
    int m_maxfps;
    
    bool m_rawStarted;

};



#endif /* defined(__warpdriveoverloaded__GraphicsDriverManager__) */
