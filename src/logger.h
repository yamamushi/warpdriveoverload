// logging utility class for warp drive overload. 
//
// By ian R. Clauser(fall3nsp0rk)

#include <string>
#include <sys/types.h>


class logger {
	public:
		logger( const std::string lfile, const int llvl );
		void logToFile( const std::string text, const int msglvl );
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
