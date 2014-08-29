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
    getmaxyx(getParent()->get(), height, width);
    
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            if(!(x % 4)){
                mvwprintw(getParent()->get(), y, x,"%c", '|');
                getParent()->setborder('|', '|', '=', '=', '+', '+', '+', '+');
                wrefresh(getParent()->get());

            }
            else if(!(y% 2) && y != height-2){
                mvwprintw(getParent()->get(), y, x,"%c", '_');
                getParent()->setborder('|', '|', '=', '=', '+', '+', '+', '+');
                wrefresh(getParent()->get());

            }
        }
    }
    
    wrefresh(getParent()->get());
    
}


void GraphChart::render(){

    fill();

}