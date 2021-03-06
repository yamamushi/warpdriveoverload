#pragma once
//
//  widget.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/29/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef warpdriveoverloaded_widget_h
#define warpdriveoverloaded_widget_h

#include "wintypes/window.h"


class GenericWindow;

class Widget {
    
public:
    
    Widget(_SharedPtr<GenericWindow> parent = nullptr, int xpos=0, int ypos=0) : m_parent(parent), m_xpos(xpos), m_ypos(ypos){};
    
    void setParent(_SharedPtr<GenericWindow> parent){m_parent = parent;}
    _SharedPtr<GenericWindow> getParent(){return m_parent;}
    
    virtual void render(){}
    virtual void refresh(){}
    virtual void resize(int newx, int newy){}
    virtual void handleKeys(int input){}
    virtual void move(int x, int y){m_xpos = x; m_ypos = y;}
    virtual int getXpos(){return m_xpos;}
    virtual int getYpos(){return m_ypos;}
    
protected:
    
    _SharedPtr<GenericWindow> m_parent;
    
    int m_xpos;
    int m_ypos;

};


#endif
