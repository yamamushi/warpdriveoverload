//
//  sqlite.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/19/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__sqlite__
#define __warpdriveoverloaded__sqlite__

#include <sqlite3.h>
#include <string>


class sqliteDB {
    
public:
    
    static sqliteDB* db();
    
    
    
private:
    
    sqliteDB(){};
    
    sqliteDB(sqliteDB const&);
    sqliteDB& operator=(sqliteDB const&);
    static sqliteDB* m_pInstance;

    
    bool checkForDB(std::string pathname);
    
    
    
};

#endif /* defined(__warpdriveoverloaded__sqlite__) */
