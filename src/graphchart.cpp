//
//  graphchart.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "graphchart.h"



void GraphChart::fill(){
    
    int height, width;
    getmaxyx(m_parent->get(), height, width);
    
    wclear(m_parent->get());
    
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            if(!(x % 4)){
                mvwprintw(m_parent->get(), y, x,"%c", '|');
                m_parent->setborder('|', '|', '=', '=', '+', '+', '+', '+');
                wrefresh(m_parent->get());

            }
            else if(!(y% 2) && y != height-2){
                mvwprintw(m_parent->get(), y, x,"%c", '_');
                m_parent->setborder('|', '|', '=', '=', '+', '+', '+', '+');
                wrefresh(m_parent->get());

            }
        }
    }
    
    wrefresh(m_parent->get());

    
}