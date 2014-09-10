//
//  sdlwindow.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/7/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__sdlwindow__
#define __warpdriveoverloaded__sdlwindow__

#include "managers/SDLManager.h"

#ifdef _WARPDRIVE_SDLCLIENT_



class SDLWindow : public GenericWindow{

public:

    SDLWindow(int height, int length, int ypos, int xpos);


    // Screen Drawing
    void render();
    void refresh();
    void clearScreen();
    void close();
    void open();
    bool getOpened(){return false;}

    void clearArea(int x1, int y1, int x2, int y2);
    void clearRowBetween(int x1, int x2, int row);
    void clearColumnBetween(int y1, int y2, int column);

    void clearRow(int row, int from=0);
    void clearColumn(int column, int from=0);

    void drawAt(int x, int y, std::string output);
    void drawAt(int x, int y, std::string output, int fg, int bg=0, int attr=0);
    void drawAt(int x, int y, char c);
    void drawAt(int x, int y, char c, int fg, int bg=0, int attr=0);

    void putPixel(_SharedPtr<Pixel> point);
    void move(int newX, int newY){m_xpos = newX; m_ypos = newY;}
    // Resize is Virtual because some drivers may handle this differently .
    void resize(int height, int length, int ypos=0, int xpos=0);
    void drawLine(int x1, int y1, int x2, int y2, std::string symbol, int fg=0, int bg=0, int attr=0);
    void drawBorder();


    // Other Needed Functions
    void handleKeys(int input);


    // Color Management

    void setNormalColor(int fg, int bg);
    void setSelectedColor(int fg, int bg=0);
    void setCursorColor(int fg, int bg=0);
    void setBorderColor(int fg, int bg=0);


protected:



};



#endif // #ifdef _WARPDRIVE_SDLCLIENT_

#endif /* defined(__warpdriveoverloaded__sdlwindow__) */
