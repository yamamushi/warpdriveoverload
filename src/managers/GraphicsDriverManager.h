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

class GraphicsDriverManager {
    
public:
    
    virtual bool start(){return false;};
    
    virtual int getWidth(){return 0;};
    virtual int getHeight(){return 0;};
    bool getStarted(){return m_started;}
    
    virtual int getfps(){return 0;};
    virtual void setmaxfps(int fps){};
    
protected:
    
    friend class Shell;
    
    bool m_started;
    int m_rows, m_cols;
    int m_width, m_height;
    
    int m_maxfps;
};



#endif /* defined(__warpdriveoverloaded__GraphicsDriverManager__) */
