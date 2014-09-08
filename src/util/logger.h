// logging utility class for warp drive overload. 
//
// By ian R. Clauser(fall3nsp0rk)
#ifndef __LOGGER_H
#define __LOGGER_H
#include <string>
#include <sys/types.h>
#include <sstream>

class logger {
	public:
		logger( const std::string lfile, const int llvl );
		std::stringstream logstream;
        void logToFile( const int msglvl );
        void logToFile( std::string output, const int msglvl );

		void logException( const int errornumber, const std::string ctext );
	private:
		pid_t L_pid;
		int L_loglevel;
		int L_threadID;
		std::string L_logfile;
		std::string tStamp();
		unsigned long getThreadID();
		void writeToFile( const std::string filetext );
};
#endif
