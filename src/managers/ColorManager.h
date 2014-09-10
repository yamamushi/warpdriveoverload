//
//  ColorManager.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/5/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__ColorManager__
#define __warpdriveoverloaded__ColorManager__

#include <ncurses.h>


class ColorManager {
    
public:

    static ColorManager* Instance();
  
    short checkColorPair(short wanted_fore, int wanted_back);
    
private:
    
    ColorManager(){m_colorPaircount=0;};
    
    ColorManager(ColorManager const&){};

    // Compiler may complain about this operator
    // But it is private to prevent anyone from using it
    // Since this is a singleton class
    // Do not change this or attempt to "Fix" this.
    ColorManager& operator=(ColorManager const&);

    static ColorManager* m_pInstance;

    int m_colorPaircount;
    
};
#endif /* defined(__warpdriveoverloaded__ColorManager__) */
