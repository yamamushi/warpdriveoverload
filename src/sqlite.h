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
    void resultcontainer(std::vector<std::pair<std::string, std::string> > output);

    std::vector<std::pair<std::string, std::string> > m_dataContainer;
    
};

#endif /* defined(__warpdriveoverloaded__sqlite__) */


/*
 sqlite3 *db;
 char *zErrMsg = 0;
 int rc;
 
 if( argc!=3 ){
 fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
 return(1);
 }
 rc = sqlite3_open(argv[1], &db);
 if( rc ){
 fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
 sqlite3_close(db);
 return(1);
 }
 rc = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);
 if( rc!=SQLITE_OK ){
 fprintf(stderr, "SQL error: %s\n", zErrMsg);
 sqlite3_free(zErrMsg);
 }
 sqlite3_close(db);
 */