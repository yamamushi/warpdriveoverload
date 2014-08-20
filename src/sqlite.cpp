//
//  sqlite.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/19/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "sqlite.h"
#include <iostream>

sqliteDB* sqliteDB::m_pInstance = NULL;


sqliteDB* sqliteDB::instance(){
    
    if (!m_pInstance){
        m_pInstance = new sqliteDB;
    }
    
    return m_pInstance;
    
}


sqliteDB::sqliteDB(){
    
    m_dbOpen = false;
    m_emptyCheck = false;
    initDB();
    
}


int sqliteDB::dbcallback(void *NotUsed, int argc, char **argv, char **azColName){
    
    int i;
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
    
}



void sqliteDB::initDB(){
    
    if(!m_dbOpen){
        openDB("game.db");
    }
    std::cout << "initializing" << std::endl;
    if(!executeStatement("select * from global_users;")){
        std::cout << "Database is Empty!" << std::endl;
        std::cout << "Propagating User Tables" << std::endl;
        if(!executeStatement("CREATE TABLE \"main\".\"global_users\" (\"userid\" integer NOT NULL PRIMARY KEY AUTOINCREMENT, \"username\" TEXT, \"password\" blob, \"email\" TEXT)")){
            
        }
        
    }
    
}


bool sqliteDB::executeStatement(std::string statement){
    
    if(m_dbOpen){
        
        char *zErrMsg = 0;
        
        int status = sqlite3_exec(m_db, statement.c_str(), dbcallback, 0, &zErrMsg);
        
        if( status!=SQLITE_OK ){
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return false;
        }
        
        return true;
    }
    else{
        std::cerr << "Databse not Open" << std::endl;
        return false;
    }
    
}


bool sqliteDB::openDB(std::string pathname){
    
    int connectStatus = sqlite3_open(pathname.c_str(), &m_db);
    
    if( connectStatus ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(m_db));
        sqlite3_close(m_db);
        m_dbOpen = false;
        return(1);
    }
    
    m_dbOpen = true;
    
    return true;
    
}

