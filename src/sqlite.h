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
    
    static sqliteDB* instance();
    
    
    
private:
    
    sqliteDB();
    
    sqliteDB(sqliteDB const&);
    sqliteDB& operator=(sqliteDB const&);
    static sqliteDB* m_pInstance;

    
    bool openDB(std::string pathname);
    bool checkForDB(std::string dbName);
    
    sqlite3 *m_db;
    
};

#endif /* defined(__warpdriveoverloaded__sqlite__) */
