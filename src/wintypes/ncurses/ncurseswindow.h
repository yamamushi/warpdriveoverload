//
//  ncurseswindow.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/7/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//



#ifndef __warpdriveoverloaded__ncurseswindow__
#define __warpdriveoverloaded__ncurseswindow__


#include "NcursesManager.h"

#ifdef _WARPDRIVE_NCURSESCLIENT_


#include <vector>
#include <string>

#include "tr1/tr1_wrapper.h"
#include "managers/ColorManager.h"
#include "wintypes/window.h"



class Widget;


class NcursesWindow : public GenericWindow {
    
public:
    
    NcursesWindow(int height, int length, int ypos, int xpos);
    
    void render();
    void refresh();
    void close();
    void open();
    void clearScreen();
    bool getOpened();
    
    void clearArea(int x1, int y1, int x2, int y2);
    void clearRowBetween(int x1, int x2, int row);
    void clearColumnBetween(int y1, int y2, int column);
    
    void clearRow(int row, int from=0);
    void clearColumn(int column, int from=0);
    
    void drawBorder();
    
    void handleKeys(int input);
    
    void drawAt(int x, int y, std::string output);
    void drawAt(int x, int y, std::string output, int fg, int bg=0, int attr=0);
    void drawAt(int x, int y, char c);
    void drawAt(int x, int y, char c, int fg, int bg=0, int attr=0);
    void drawLine(int x1, int y1, int x2, int y2, std::string symbol, int fg=0, int bg=0, int attr=0);

    void putPixel(_SharedPtr<Pixel> point);
    
    void resize(int height, int length, int ypos, int xpos);
    
    void setNormalColor(int fg, int bg);
    void setSelectedColor(int fg, int bg=0);
    void setCursorColor(int fg, int bg=0);
    void setBorderColor(int fg, int bg=0);
    
    short checkColorPair(short wanted_fore, int wanted_back);
    int colored_chtype(char ch, int attr, int colorPair);

private:
    
    WINDOW *m_window;
        
    int m_colorPaircount;
    void drawLineCallBack(int x, int y, std::string output, int fg=0, int bg=0, int attr=0);
    
};


#endif // #ifdef _WARPDRIVE_NCURSESCLIENT_




#endif /* defined(__warpdriveoverloaded__ncurseswindow__) */
