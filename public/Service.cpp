#include "Service.h"
#include "Global.h"
#include <netinet/in.h> //sockaddr_in的定义

Service * Service::instance = NULL;

bool Service::init(unsigned short port)
{
	if(!zService::init())
		return false;

	tcpServer = new TCPServer(serviceName);
	if(tcpServer && tcpServer->bind(serviceName,port))
		return true;
	Global::glog->printLog("Service init失败");
	return false;
}

bool Service::serviceCallBack()
{
	struct sockaddr_in addr;
	int retcode = tcpServer->accept(&addr);
	if(retcode > 0)
	{
		genTCPTask(retcode,&addr);
	}
	return true;
}

void Service::final()
{
	Global::glog->printLog("Service final()");
	delete tcpServer;
}
