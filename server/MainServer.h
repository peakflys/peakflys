#ifndef _MAINSERVER_H
#define _MAINSERVER_H

#include "Service.h"
#include "Log.h"
#include "Type.h"

const WORD serverPort = 9999;

class MainService : public Service
{
	public:
		static MainService &getInstance()
		{
			if(!instance)
				instance = new MainService("主服务器程序");
			return *instance;
		}
		static void delInstance()
		{
			if(instance)
			{
				delete instance;
				instance = NULL;
			}
		}
		void genTCPTask(const int sock,const struct sockaddr_in *addr);
	private:
		static MainService *instance;
		MainService(const std::string &name):Service(name),log(name)
		{
		}
		bool init();
		Log log;
};
#endif
