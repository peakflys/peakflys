#ifndef _LOG_H
#define _LOG_H
#include <string>
const unsigned int MAX_LOGBUFF  = 4*1024;
class Log
{
	public:
		Log(const std::string& _name):name(_name){}
		bool printLog(const char *pattern, ...)__attribute__((format(printf,2,3)));
	private:
		char message[MAX_LOGBUFF];
		std::string name;
};
#endif
