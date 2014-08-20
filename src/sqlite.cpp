//
//  sqlite.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/19/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "sqlite.h"

sqliteDB* sqliteDB::m_pInstance = NULL;


sqliteDB* sqliteDB::instance(){
    
    if (!m_pInstance){
        m_pInstance = new sqliteDB;
    }
    
    return m_pInstance;

}


sqliteDB::sqliteDB(){
    
    //checkForDB("server");
    
}




bool sqliteDB::openDB(std::string pathname){
    
    int connectStatus = sqlite3_open(pathname.c_str(), &m_db);
    
    if( connectStatus ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(m_db));
        sqlite3_close(m_db);
        return(1);
    }
    
    
    return false;
    
}
