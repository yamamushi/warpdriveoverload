// Mysql database class header
// Written by Ian R Clauser (Fall3nSp0rk
// WarpDriveOverloaded by Jonathan Rumion (Yamamushi)

class db {
	public:
		db( const std::string &dbname, const std::string &dbuser, const std::string &dbpass, const std::string &initfile ); //constructor for database class.
		bool dQuery( const int &type, const std::string &table, const std::vector<std::string> &wcolumns, const std::vector<std::string> &wvals, const std::vector<std::string> &dcolumns, const std::vector<std::string> &dvals );
		//dQuery is the handler for all queries to the database
	private:
		
		std::string updateQuery( const std::vector<std::string> &whereClauses, const std::vector<std::string> &setClauses, const std::string &utable );
		std::string insertQuery( const std::string &itable, const std::vector<std::string> &vals );
		std::string selectQuery( const std::string &stable, const std::vector<std::string> &scolumns, const std::vector<std::string> &whereClauses );
		std::string execQuery( const std::string &query, mysqlpp::Result &res, bool &success );
		bool dbConnect(); // 
		bool checkDBExists(); // checks to see if the database given by the 
		bool createDB( const std::string& fdbname, const std::string &finitfile, const std::string &fdbuser, const std::string &fdbpass ); // 
		extern mysqlpp::Connection db_conn; // declare the mysqlpp connection object here, gets defined in db.cpp
		bool db_lockedForEditing; // this flag is the indicator as to whether there is currently a lock existing on the database
		bool db_isOpen; // flag for whether there is an active database connectionl
		std::string db_name; // \/
		std::string db_user; //  > these get passed to 
		std::string db_pass; // /
};
