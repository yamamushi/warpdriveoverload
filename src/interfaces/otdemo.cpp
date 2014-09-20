#include "otdemo.h"
#include "util/asciicodes.h"
#include "managers/ColorManager.h"


#include <iostream>
#include <sstream>
#include <streambuf>
#include <vector>
#include <string>

#include <stdio.h>

// Stuff for grabbing the home directory
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

void OpenTxsInterface::run(){

    m_mainWindow->clearArea(1, 1, m_width-1, m_height-3);
    m_mainWindow->refresh();
    m_mainWindow->drawAt(1, m_mainWindow->getY()-2, '>');

    //m_activeWidget = m_widgetManager->getActiveWidget();
    m_activeWidget = m_scrollBox;
    timeWidget->move(m_width - 28, 1);

    if(!m_activeWidget)
        return;


    // Grabbing our std::cerr output

    std::string message = m_strCout.str();

    if(message != "") {
        std::string::size_type pos = 0;
        std::string::size_type prev = 0;
        while ((pos = message.find('\n', prev)) != std::string::npos) {
            m_scrollBox->addMessage(message.substr(prev, pos - prev));
            prev = pos + 1;
        }
        m_scrollBox->addMessage("\n");
        m_scrollBox->addMessage("\n");
        //messageList.push_back(message.substr(prev));
        m_strCout.str("");
    }

    //std::flush(std::cerr);

    // End of std::cerr parse


/*
    int messX = 3;
    int messY = (m_height-4) - messageList.size();
    if(messageList.size() != 0 ){
        for (auto itr = messageList.begin(); itr != messageList.end(); itr++) {
            m_mainWindow->drawAt(messX, messY, *itr);
            ++messY;
        }
    } */

    m_widgetManager->render();
    draw();

};


void OpenTxsInterface::init(){


    // By the time we get here, we should have already have had a window created and ready for us.
    m_mainWindow->clearScreen();

    m_otStarted = false;

    // Redirect cerr.
    std::streambuf* oldCerrStreamBuf = std::cerr.rdbuf();

    std::cerr.rdbuf( m_strCout.rdbuf() );

    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf( m_strCout.rdbuf() );

    // Restore old cerr.
    //std::cerr.rdbuf( oldCoutStreamBuf );

    // Will output our Hello World! from above.
    //std::cout << strCout.str();

    //Opentxs::Instance()->start();


    m_widgetManager = _SharedPtr<WidgetManager>(new WidgetManager(this));

    // Set our Interface NAme
    setName("OpenTxs Demo");

    timeWidget = _SharedPtr<TimeWidget>(new TimeWidget(m_mainWindow, m_width - 28, 1));
    m_widgetManager->addWidget(timeWidget);

    m_scrollBox = _SharedPtr<ScrollTextWidget>(new ScrollTextWidget(m_mainWindow, 1, 4));
    m_scrollBox->resize(m_mainWindow->getX() - 2, m_mainWindow->getY() - 5);
    m_widgetManager->addWidget(m_scrollBox);


    // Needed by our shell controller
    m_initialized = true;

    run();
};


void OpenTxsInterface::handleKeys(int input){


    switch(input){

        case '[':
            m_activeWidget = m_widgetManager->getPrevWidget();
            break;
        case ']':
            m_activeWidget = m_widgetManager->getNextWidget();
            break;
        //case 'q':
        //    m_owner->quit();
        //   break;
        case '\n':
            getLineInput();
            if(m_lineInputString != ""){

                m_scrollBox->addMessage("-> " + m_lineInputString);
                m_mainWindow->clearLineFrom( m_mainWindow->getY()-2, 2);

                run();
                m_mainWindow->render();

                handleLineInput(m_lineInputString);
                m_lineInputString = "";

            }

            break;
        default:
            m_activeWidget->handleKeys(input);
            break;

    }
};


void OpenTxsInterface::handleLineInput(std::string input) {

    std::transform(input.begin(), input.end(), input.begin(), ::tolower);

    std::vector<std::string> words;
    std::string::size_type pos = 0;
    std::string::size_type prev = 0;

    words.push_back(" ");
    while ((pos = input.find(' ', prev)) != std::string::npos) {
        words.push_back(input.substr(prev, pos - prev));
        prev = pos + 1;
    }
    words.push_back(input.substr(prev));

    std::string command = words.at(1);

    if(command == "start"){

        if(words.size() > 1) {
            std::vector<std::string> options(words.begin() + 1, words.end());
            m_otStarted = Opentxs::Instance()->start(options);
        }
        else{
            std::vector<std::string> options;
            m_otStarted = Opentxs::Instance()->start(options);

        }
    }

    else if(command == "stop"){

        Opentxs::Instance()->stop();
        m_scrollBox->addMessage("\n");
        m_scrollBox->addMessage("\n");
        m_scrollBox->addMessage("You Have stopped OpenTxs, you must restart the application to start it again");
        m_scrollBox->addMessage("\n");
        m_scrollBox->addMessage("\n");
        m_otStarted = false;

    }

    else if(command == "quit"){

        m_owner->quit();

    }

    else {
        std::vector<std::string> arguments(words.begin(), words.end());
        Opentxs::Instance()->handleCommand(command, arguments);
    }


}


void OpenTxsInterface::draw(){

    // I prefer writing from top left to right, like you would on a piece of paper.
    if(m_otStarted)
        m_mainWindow->drawAt(2, 1, "OT Client Running");
    else
        m_mainWindow->drawAt(2, 1, "OT Client Stopped", COLOR_RED);

    m_mainWindow->drawAt( (m_width - (int)getName().size())/2, 1, getName(), COLOR_WHITE, COLOR_BLACK);
    m_mainWindow->drawLine(1, 3, m_width-1, 3, "-", m_mainWindow->getBorderColorfg(), m_mainWindow->getBorderColorbg());
    m_mainWindow->drawLine(1, m_height-3, m_width-1, m_height-3, "-", m_mainWindow->getBorderColorfg(), m_mainWindow->getBorderColorbg());

};


void OpenTxsInterface::resizeComponents(){



};



void OpenTxsInterface::getLineInput(){

    //m_mainWindow->drawAt(4, m_mainWindow->getY()-2, '|', m_mainWindow->getFGColor(), m_mainWindow->getBGColor(), A_BLINK);
    m_owner->enableRaw();
    bool firstrun = true;
    while(int input = getch() ){
        m_mainWindow->drawAt(1, m_mainWindow->getY()-2, '>');
        m_mainWindow->drawAt(3 + m_lineInputString.length(), m_mainWindow->getY()-2, '|', m_mainWindow->getFGColor(), m_mainWindow->getBGColor(), A_BLINK);


        if(input == '\n' || input == 27)
            break;

        if(input > 0){

            if(input == KEY_BACKSPACE || input == KEY_DC || input == 127) {
                m_lineInputString.pop_back();
                m_mainWindow->clearLineFrom(m_mainWindow->getY()-2, m_lineInputString.length());
            }
            else
                m_lineInputString += input;

            //m_mainWindow->drawAt((m_mainWindow->getX()/2), (m_mainWindow->getY()/2), "             ");
            //m_mainWindow->clearLineFrom( (m_mainWindow->getY()/2), (m_mainWindow->getX()/2));

            m_mainWindow->drawAt(3, m_mainWindow->getY()-2, m_lineInputString);

        }

        run();
        m_mainWindow->refresh();
        m_mainWindow->render();

        input = 0;
    }

    m_owner->disableRaw();

}