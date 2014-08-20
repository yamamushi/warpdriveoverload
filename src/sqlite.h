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
#include <tuple>
#include <vector>


class sqliteDB {
    
public:
    
    static sqliteDB* instance();
    
    bool openDB(std::string pathname);
    bool checkForDB(std::string dbName);
    
    
    void run(){};
    
private:
    
    sqliteDB();
    
    void initDB();
    bool executeStatement(std::string statement);

    
    sqliteDB(sqliteDB const&);
    sqliteDB& operator=(sqliteDB const&);
    static sqliteDB* m_pInstance;

    bool m_dbOpen;
    

    
    sqlite3 *m_db;
    
    
protected:
    
    // Callback

    static int dbcallback(void *NotUsed, int argc, char **argv, char **azColName);
    void resultcontainer(std::vector<std::pair<std::string, std::string> > output){m_dataContainer = output;}

    std::vector<std::pair<std::string, std::string> > m_dataContainer;
    
};

#endif /* defined(__warpdriveoverloaded__sqlite__) */
