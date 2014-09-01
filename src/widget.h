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

#include "window.h"

class ncursesWindow;

class Widget {
    
public:
    
    Widget(_SharedPtr<ncursesWindow> parent = nullptr) : m_parent(parent){};
    
    void setParent(_SharedPtr<ncursesWindow> parent){m_parent = parent;}
    _SharedPtr<ncursesWindow> getParent(){return m_parent;}
    
    virtual void render(){};
    virtual void refresh(){};
    virtual void resize(int newx, int newy){};
    virtual void handleKeys(int input){};
    
protected:
    
    _SharedPtr<ncursesWindow> m_parent;

};


#endif
