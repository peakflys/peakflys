#include "MainServer.h"
#include "TcpTask.h"
#include "MainLoop.h"
#include "Global.h"

MainService * MainService::instance = NULL;

bool MainService::init()
{
#ifdef _TZL_DEBUG
	log.printLog("主服务器初始化开始");
#endif
	//taskVec.clear();
	if(!Service::init(serverPort))
	{
		log.printLog("服务器启动失败");
		return false;
	}
	//UserManager::loadUser();
	if(!MainLoop::getMe().start())
	{
		log.printLog("主循环线程启动失败");
		return false;
	}
	log.printLog("服务器启动成功,%s",__PRETTY_FUNCTION__);
	return true;
}

void MainService::genTCPTask(const int sock,const struct sockaddr_in *addr)
{
	TcpTask *tcpTask = new TcpTask(sock,addr);	
	if(!tcpTask)
	{
		TEMP_FAILURE_RETRY(::close(sock));
		return;
	}
	MainLoop::getMe().putTask(tcpTask);
}

int main()
{
	Global::glog = new Log("全局");
	MainService::getInstance().main();
	MainService::delInstance();
	MainLoop::getMe().final();
	MainLoop::getMe().delMe();
	//UserManager::delAllUser();
	return 0;
}
