//
//  bresenham2d.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/5/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "bresenham2d.h"

#include "tr1/tr1_threading.h"
#include <algorithm>
#include <cmath>
#include <utility>

void bresenham2d(int x0, int y0, int x1, int y1, _STD_FUNCTION(void(int, int)) passCommand) {
    
    int dx = (int) fabs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = (int) fabs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;
    
    for(;;){
        passCommand(x0,y0);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

/*
void bresenham2d(int x0, int y0, int x1, int y1, std::string symbol, int fg, int bg, int attr, _STD_FUNCTION(void(int, int, std::string, int, int, int)) passCommand) {
    
    int dx = fabs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = fabs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;
    
    for(;;){
        passCommand(x0,y0, symbol, fg, bg, attr);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}
*/