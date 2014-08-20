//
//  sqlite.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/19/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "sqlite.h"

sqliteDB* sqliteDB::m_pInstance = NULL;


sqliteDB* sqliteDB::db(){
    
    if (!m_pInstance){
        m_pInstance = new sqliteDB;
    }
    
    return m_pInstance;

}
