#pragma once
#include "interface.h"
#include "widgets/TimeWidget.h"
#include "widgets/ScrollTextWidget.h"
#include "opentxs/opentxs.hpp"


#include <vector>
#include <string>

class Interface;


class OpenTxsInterface : public Interface {

public:

    OpenTxsInterface(_SharedPtr<Shell> owner) : Interface(owner) {};
    ~OpenTxsInterface(){};


    void run();
    void init();
    void handleKeys(int input);
    void draw();

protected:


    void resizeComponents();



private:

    _SharedPtr<TimeWidget> timeWidget;
    _SharedPtr<ScrollTextWidget> m_scrollBox;

    std::ostringstream m_strCout;

    void getLineInput();
    std::string m_lineInputString;
    std::vector<std::string> messageList;

    void handleLineInput(std::string input);

    bool m_otStarted;

};