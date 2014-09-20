#include "ScrollTextWidget.h"
#include "widget.h"
#include "util/asciicodes.h"

ScrollTextWidget::ScrollTextWidget(_SharedPtr<GenericWindow> parent, int xpos, int ypos) : Widget(parent, xpos, ypos){

    int m_sizeLimit = parent->getY();

    m_sizeY = m_parent->getY();
    m_sizeX = m_parent->getX();

    m_beginPoint = m_sizeY-5;
    m_endPoint = 0;

}



void ScrollTextWidget::render() {

    std::vector<std::string> renderList;
    int border = m_messageList.size();
    int lineCount = 0;

    if(m_messageList.size() != 0 ){

        for (auto itr = m_messageList.begin(); itr != m_messageList.end(); itr++) {

            if(itr->length() > m_sizeX){

                for(int y = 0; y < itr->length() / m_sizeX ; y++){

                    if(y ==  (itr->length() / m_sizeX) - 1 ){
                        renderList.push_back(itr->substr(y * m_sizeX));
                    }
                    else {
                        renderList.push_back(itr->substr(y * m_sizeX, (y * m_sizeX) + m_sizeX));
                    }
                }
            }
            else{
                renderList.push_back(*itr);
            }
        }

        if(renderList.size() > m_sizeY){
            for (auto itr = renderList.end() - (m_beginPoint); itr != renderList.end(); itr++){

                if(lineCount > m_sizeY-2){
                    return;
                }

                m_parent->drawAt(m_xpos, m_ypos+lineCount, *itr);

                lineCount++;
            }
        }
        else {
            for (auto itr = renderList.begin(); itr != renderList.end(); itr++) {
                if(lineCount > m_sizeY){
                    return;
                }
                m_parent->drawAt(m_xpos, m_ypos + lineCount, *itr);

                lineCount++;

            }
        }
    }
}

void ScrollTextWidget::refresh() {

}

void ScrollTextWidget::resize(int newx, int newy) {

    if(newx > 0 && newx < m_parent->getX())
        m_sizeX = newx;
    else
        m_sizeX = m_parent->getX();

    if(newy > 0 && newy < m_parent->getY())
        m_sizeY = newy;
    else
        m_sizeY = m_parent->getY();


}

void ScrollTextWidget::handleKeys(int input) {

    switch(input){

        case 'u':
            if(m_beginPoint < m_messageList.size())
                ++m_beginPoint;
            break;

        case 'j':
            if(m_beginPoint > m_sizeY)
                --m_beginPoint;
            break;

    }
}

void ScrollTextWidget::setSizeLimit(int lines) {

    m_sizeLimit = lines;

}

int ScrollTextWidget::getSizeLimit() {

    return m_sizeLimit;

}

void ScrollTextWidget::prune(){

    if(m_messageList.size() > m_sizeLimit){

        m_messageList.resize(m_sizeLimit);

    }

}

void ScrollTextWidget::addMessage(std::string message) {

    m_messageList.push_back(message);

}
