//
//  ColorManager.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/5/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "ColorManager.h"

ColorManager* ColorManager::m_pInstance = NULL;



ColorManager* ColorManager::Instance()
{
    if (!m_pInstance)   // Only allow one instance of class to be generated.
        m_pInstance = new ColorManager;

    return m_pInstance;
}



short ColorManager::checkColorPair(short wanted_fore, int wanted_back){
    
    int i;
    short fore, back;
    if ( (wanted_fore > 16) || (wanted_back > 8) || (wanted_fore < 0) || (wanted_back < 0) ){
        
        return 0;
    }
    
    
    for (i = 0; i < m_colorPaircount; i++)
    {
        pair_content(i, &fore, &back);
        if ( (fore == wanted_fore) && (back == wanted_back) )
            return i;
    }
    
    init_pair( m_colorPaircount, wanted_fore, wanted_back);
    m_colorPaircount++;
    
    return m_colorPaircount - 1;
    
}