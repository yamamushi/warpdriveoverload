#pragma once
//
//  panel.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//


#include "shell.h"
#include <panel.h>
#include <string>

class ncursesPanel {
    
public:
    
    ncursesPanel(_SharedPtr<ncursesWindow> child);
    
    void setName(std::string name){m_name = name;}
    std::string getName(){return m_name;}
    _SharedPtr<ncursesWindow> getChild(){return m_child;}

    PANEL * getPanel(){return m_panel;}
    _SharedPtr<ncursesPanel>  getNext(){return m_next;}
    _SharedPtr<ncursesPanel>  getPrevl(){return m_prev;}

    
    void addNext(_SharedPtr<ncursesPanel>  nextPanel){m_next = nextPanel;}
    void addPrev(_SharedPtr<ncursesPanel>  prevPanel){m_prev = prevPanel;}
    
private:
    
    _SharedPtr<ncursesWindow> m_child;
    PANEL *m_panel;
    _SharedPtr<ncursesPanel> m_prev;
    _SharedPtr<ncursesPanel> m_next;
    
    static int ID;
    int m_ID;
    std::string m_name;

};


