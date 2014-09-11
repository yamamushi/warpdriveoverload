//
//  sdlwindow.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/7/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "sdlwindow.h"

#ifdef _WARPDRIVE_SDLCLIENT_

#include "SDL_image.h"
#include <iostream> // Here for Testing

SDLWindow::SDLWindow(int height, int length, int ypos, int xpos, SDLManager *owner)  : GenericWindow(height, length, ypos, xpos) {

    m_owner = owner;

    m_sdlWidth = owner->getSDLWidth();
    m_sdlHeight = owner->getSDLHeight();

    m_renderer = m_owner->getRenderer();
    m_mainTexture = _SharedPtr<SDLTextureWrapper>(new SDLTextureWrapper(m_renderer));

    m_mainTexture->loadFromFile("data/fonts/terminal8x8_gs_ro.png");

    m_mainFontObject = m_mainTexture->getBitmapFont();
    m_mainFontObject->buildFont( m_mainTexture.get() );

    m_localTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, m_sdlWidth, m_sdlHeight);

    m_mainTexture->setDrawOn(m_localTexture);

    //m_mainTexture->setColor(128, 128, 0 );

    std::cout << "SDL Window Loaded" << std::endl;
    clearScreen();
}


void SDLWindow::render() {

    SDL_Color blackColor;
    blackColor.r = 0;
    blackColor.g = 0;
    blackColor.b = 0;

    SDL_Color greenColor;
    greenColor.r = 50;
    greenColor.g = 205;
    greenColor.b = 50;
    //SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    //m_mainFontObject->renderText( 10, 10,  "TEST");
    SDL_SetRenderTarget(m_renderer, NULL);

    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_NONE);
    //m_owner->render();
    //clearScreen();
    //clearScreen();
    //SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);

    m_owner->renderToMainScreen(m_localTexture);

    /*
    SDL_SetRenderTarget(m_renderer, m_localTexture);
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(m_renderer, NULL);
    SDL_SetRenderTarget(m_renderer, NULL);
    */

    SDL_DestroyTexture(m_localTexture);
    m_localTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, m_sdlWidth, m_sdlHeight);
    m_mainTexture->setDrawOn(m_localTexture);
}

void SDLWindow::refresh() {

    SDL_DestroyTexture(m_localTexture);
    m_localTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, m_sdlWidth, m_sdlHeight);
    m_mainTexture->setDrawOn(m_localTexture);


    SDL_SetRenderTarget(m_renderer, m_localTexture);
    //SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( m_renderer );
    SDL_SetRenderTarget(m_renderer, NULL);

}

void SDLWindow::clearScreen() {

    SDL_DestroyTexture(m_localTexture);
    m_localTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, m_sdlWidth, m_sdlHeight);
    m_mainTexture->setDrawOn(m_localTexture);

    SDL_SetRenderTarget(m_renderer, NULL);
    //SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( m_renderer );
    m_owner->render();
}

void SDLWindow::close() {
    //GenericWindow::close();
}

void SDLWindow::open() {
    //GenericWindow::open();
}

void SDLWindow::clearArea(int x1, int y1, int x2, int y2) {
    int beginx, beginy;
    int endx, endy;

    if(x1>x2){
        endx = x1;
        beginx = x2;
    }
    else{
        endx = x2;
        beginx = x1;
    }

    if(y1 > y2){
        endy = y1;
        beginy = y2;
    }
    else{
        endy = y2;
        beginy = y1;
    }

    for(int row = beginy; row < endy; row++){
        clearRowBetween(beginx, endx, row);
    }
}

void SDLWindow::clearRowBetween(int x1, int x2, int row) {
    if(x1 < 0){
        x1 = 0;
    }

    if(x2 > m_length){
        x2 = m_length;
    }

    for(int y = x1; y < x2; y++){
        drawAt(y, row, " ");
    }}

void SDLWindow::clearColumnBetween(int y1, int y2, int column) {
    if(y1 < 0){
        y1 = 0;
    }

    if(y2 > m_height){
        y1 = m_height;
    }

    for(int x = y1; x < y2; x++){
        drawAt(column, x, " ");
    }}

void SDLWindow::clearRow(int row, int from) {
    if(row < 0 || row > m_height)
        return;

    for(int x = from; x < m_length; x++){
        drawAt(x, row, " ");
    }
}

void SDLWindow::clearColumn(int column, int from) {

    if(column < 0 || column > m_length)
        return;

    for(int x = from; x < m_height; x++){
        drawAt(column, x, " ");
    }
}

void SDLWindow::drawAt(int x, int y, std::string output) {
    //GenericWindow::drawAt(x, y, output);
    m_mainFontObject->renderText( x*m_mainFontObject->getsizeX(), y*m_mainFontObject->getsizeY(), output );

}

void SDLWindow::drawAt(int x, int y, std::string output, int fg, int bg, int attr) {

    m_mainFontObject->renderText(x*m_mainFontObject->getsizeX(), y*m_mainFontObject->getsizeY(), output );

}

void SDLWindow::drawAt(int x, int y, char c) {

    std::string output(&c);

    //m_mainFontObject->renderText( x, y,  output);

}

void SDLWindow::drawAt(int x, int y, char c, int fg, int bg, int attr) {

    std::string output(&c);

  //  m_mainFontObject->renderText( x, y,  output);

}

void SDLWindow::putPixel(_SharedPtr<Pixel> point) {
    GenericWindow::putPixel(point);
}

void SDLWindow::resize(int height, int length, int ypos, int xpos) {
    GenericWindow::resize(height, length, ypos, xpos);
}

void SDLWindow::drawLine(int x1, int y1, int x2, int y2, std::string symbol, int fg, int bg, int attr) {
    bresenham2d(x1, y1, x2, y2, _STD_BIND(&SDLWindow::drawLineCallBack, this, std::placeholders::_1, std::placeholders::_2, symbol, fg, bg, attr)); //STD_BIND(&NcursesWindow::drawAt, this, x1, y1, fg, bg, attr));

}

void SDLWindow::drawLineCallBack(int x, int y, std::string output, int fg, int bg, int attr){

    m_mainFontObject->renderText( x*m_mainFontObject->getsizeX(), y*m_mainFontObject->getsizeY(),  output);

}


void SDLWindow::drawBorder() {
    GenericWindow::drawBorder();
}

void SDLWindow::handleKeys(int input) {
    //GenericWindow::handleKeys(input);
}

void SDLWindow::setNormalColor(int fg, int bg) {
    GenericWindow::setNormalColor(fg, bg);
}

void SDLWindow::setSelectedColor(int fg, int bg) {
    GenericWindow::setSelectedColor(fg, bg);
}

void SDLWindow::setCursorColor(int fg, int bg) {
    GenericWindow::setCursorColor(fg, bg);
}

void SDLWindow::setBorderColor(int fg, int bg) {
    GenericWindow::setBorderColor(fg, bg);
}





#endif