//
//  window.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/7/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//
//  A generic display template for rendering.
//
//
#include "Window.h"


GenericWindow::GenericWindow(int height, int length, int ypos, int xpos) : m_height(height), m_length(length), m_ypos(ypos), m_xpos(xpos){
    
    m_border = _SharedPtr<winBorder>(new winBorder);

}


void GenericWindow::addWidget(_SharedPtr<Widget> target){
    
    removeWidget(target);
    target->setParent(shared_from_this());
    m_widgetList.push_back(target);
    
}


void GenericWindow::removeWidget(_SharedPtr<Widget> target){
    
    std::vector<_SharedPtr<Widget> >::iterator it = std::find(m_widgetList.begin(), m_widgetList.end(), target);
    if (it != m_widgetList.end()){
        m_widgetList.erase(std::remove(m_widgetList.begin(), m_widgetList.end(), target), m_widgetList.end());
    }
    
}



void GenericWindow::setborder(char ls, char rs, char ts, char bs, char tl, char tr, char bl, char br){
    
    m_border->m_ls = ls;
    m_border->m_rs = rs;
    m_border->m_ts = ts;
    m_border->m_bs = bs;
    m_border->m_tl = tl;
    m_border->m_tr = tr;
    m_border->m_bl = bl;
    m_border->m_br = br;
    
}


