#include "Log.h"
#include <stdarg.h>
#include <iostream>
#include <sstream>

bool Log::printLog(const char *pattern, ...)
{
	va_list ap;
	bzero(message,MAX_LOGBUFF);
	va_start(ap,pattern);
	vsnprintf(message,MAX_LOGBUFF-1,pattern,ap);
	va_end(ap);
	time_t t = time(0);
	tm *nowTm = localtime(&t);
	std::ostringstream log;
	log<<"["<<name<<"]"<<nowTm->tm_hour<<":"<<nowTm->tm_min<<":"<<nowTm->tm_sec<<"\t"<<message;
	std::cout<<log.str()<<std::endl;;
}
