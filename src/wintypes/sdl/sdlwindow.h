#pragma once
//
//  sdlwindow.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/7/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__sdlwindow__
#define __warpdriveoverloaded__sdlwindow__

#include "SDLManager.h"

#ifdef _WARPDRIVE_SDLCLIENT_

#include "SDL.h"
#include "BitmapFont.h"
#include "sdlwindow.h"
#include "SDLTextureWrapper.h"

class SDLBitmapFont;
class SDLManager;
class SDLTextureWrapper;

class SDLWindow : public GenericWindow{

public:

    SDLWindow(int height, int length, int ypos, int xpos, SDLManager *owner);


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


private:

    void drawLineCallBack(int x, int y, std::string output, int fg=0, int bg=0, int attr=0);
    // Note: this is NOT the same as SDLManager.h's m_window member
    // This is the surface we draw to, which we then pass to
    // SDL Manager to finally draw on the "Window"
    // Screen/Window, trying to emphasize that this class is a
    // Container for finally rendering to the screen

    SDL_Surface* m_window;

    SDLManager *m_owner;

    SDL_Renderer *m_renderer;

    _SharedPtr<SDLBitmapFont> m_mainFontObject;

    _SharedPtr<SDLTextureWrapper> m_mainTexture;
    SDL_Texture* m_localTexture;

    int m_sdlWidth;
    int m_sdlHeight;

};



#endif // _WARPDRIVE_SDLCLIENT_

#endif /* defined(__warpdriveoverloaded__sdlwindow__) */
