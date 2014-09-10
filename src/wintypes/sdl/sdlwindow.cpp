//
//  sdlwindow.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/7/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "sdlwindow.h"
#ifdef _WARPDRIVE_SDLCLIENT_



SDLWindow::SDLWindow(int height, int length, int ypos, int xpos)  : GenericWindow(height, length, ypos, xpos) {



}


void SDLWindow::render() {
    GenericWindow::render();
}

void SDLWindow::refresh() {
    GenericWindow::refresh();
}

void SDLWindow::clearScreen() {
    GenericWindow::clearScreen();
}

void SDLWindow::close() {
    GenericWindow::close();
}

void SDLWindow::open() {
    GenericWindow::open();
}

void SDLWindow::clearArea(int x1, int y1, int x2, int y2) {
    GenericWindow::clearArea(x1, y1, x2, y2);
}

void SDLWindow::clearRowBetween(int x1, int x2, int row) {
    GenericWindow::clearRowBetween(x1, x2, row);
}

void SDLWindow::clearColumnBetween(int y1, int y2, int column) {
    GenericWindow::clearColumnBetween(y1, y2, column);
}

void SDLWindow::clearRow(int row, int from) {
    GenericWindow::clearRow(row, from);
}

void SDLWindow::clearColumn(int column, int from) {
    GenericWindow::clearColumn(column, from);
}

void SDLWindow::drawAt(int x, int y, std::string output) {
    GenericWindow::drawAt(x, y, output);
}

void SDLWindow::drawAt(int x, int y, std::string output, int fg, int bg, int attr) {
    GenericWindow::drawAt(x, y, output, fg, bg, attr);
}

void SDLWindow::drawAt(int x, int y, char c) {
    GenericWindow::drawAt(x, y, c);
}

void SDLWindow::drawAt(int x, int y, char c, int fg, int bg, int attr) {
    GenericWindow::drawAt(x, y, c, fg, bg, attr);
}

void SDLWindow::putPixel(_SharedPtr<Pixel> point) {
    GenericWindow::putPixel(point);
}

void SDLWindow::resize(int height, int length, int ypos, int xpos) {
    GenericWindow::resize(height, length, ypos, xpos);
}

void SDLWindow::drawLine(int x1, int y1, int x2, int y2, std::string symbol, int fg, int bg, int attr) {
    GenericWindow::drawLine(x1, y1, x2, y2, symbol, fg, bg, attr);
}

void SDLWindow::drawBorder() {
    GenericWindow::drawBorder();
}

void SDLWindow::handleKeys(int input) {
    GenericWindow::handleKeys(input);
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







#endif // #ifdef _WARPDRIVE_SDLCLIENT_
