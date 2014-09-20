#pragma once
/*

A scrolling text widget with the ability to scroll up and down and text rendered within a specified area

 */

#include "widget.h"

#include <string>

class ScrollTextWidget : public Widget {

public:

    ScrollTextWidget(_SharedPtr<GenericWindow> parent, int xpos, int ypos);

    void render();
    void refresh();
    void resize(int newx, int newy);
    void handleKeys(int input);

    void setSizeLimit(int lines);
    int getSizeLimit();
    void prune();

    void addMessage(std::string message);

protected:


private:

    int m_sizeLimit;

    std::vector<std::string> m_messageList;

    int m_sizeX, m_sizeY;

    int m_beginPoint;
    int m_endPoint;


};