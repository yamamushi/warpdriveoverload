#pragma once
//
//  term_control.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/19/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef warpdriveoverloaded_term_control_h
#define warpdriveoverloaded_term_control_h

#include <string>


const std::string ansi_escape = "\033[";
const std::string term_reset = "\033[0m";


const std::string cursor_up = "A";
const std::string cursor_down = "B";
const std::string cursor_forward = "C";
const std::string cursor_back = "D";
const std::string cursor_nextline = "E";
const std::string cursor_previousline = "F";;
const std::string cursor_horizontalabs = "G";
const std::string cursor_position = "H";
const std::string erase_display = "J";
const std::string erase_inline = "K";
const std::string scroll_up = "S";
const std::string scroll_down = "T";
const std::string horizontal_vertpos = "f";



const std::string select_graphicrendition = "m";
const std::string ansi_bold =  ansi_escape + "1m";
const std::string ansi_faint = ansi_escape + "2m";
const std::string ansi_italic = ansi_escape + "3m";
const std::string ansi_underline = ansi_escape + "4m";
const std::string ansi_normal = ansi_escape + "22m";

const std::string ansi_fore_black = ansi_escape + "30m";
const std::string ansi_fore_red =   ansi_escape + "31m";
const std::string ansi_fore_green = ansi_escape + "32m";
const std::string ansi_fore_yellow = ansi_escape + "33m";
const std::string ansi_fore_blue = ansi_escape + "34m";
const std::string ansi_fore_magenta = ansi_escape + "35m";
const std::string ansi_fore_cyan = ansi_escape + "36m";
const std::string ansi_fore_white = ansi_escape + "37m";

const std::string ansi_back_black = ansi_escape + "40m";
const std::string ansi_back_red =   ansi_escape + "41m";
const std::string ansi_back_green = ansi_escape + "42m";
const std::string ansi_back_yellow = ansi_escape + "43m";
const std::string ansi_back_blue = ansi_escape + "44m";
const std::string ansi_back_magenta = ansi_escape + "45m";
const std::string ansi_back_cyan = ansi_escape + "46m";
const std::string ansi_back_white = ansi_escape + "47m";





#endif
