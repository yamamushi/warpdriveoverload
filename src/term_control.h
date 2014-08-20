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


const std::string ascii_escape = "\033[";
const std::string term_reset = "\033[0m";

const std::string ascii_bold =  ascii_escape + "1m";

const std::string ascii_red =   ascii_escape + "31m";



#endif
