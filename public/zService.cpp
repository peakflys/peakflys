#include "zService.h"
#include "Global.h"

static void ctrlcHandler(int signum)
{
	zService *instance = zService::getInstance();
	if(instance)
	{
		Global::glog->printLog("受到ctrl＋c信号，终止instance");
		instance->Terminate();
	}
}

static void hupHandler(int signum)
{
	zService *instance = zService::getInstance();
	if(instance)
	{
		Global::glog->printLog("收到HUP信号，重新加载数据");
		instance->reloadData();
	}
}

zService *zService::serviceInst = NULL;

/*
 *\brief 初始化，子类再实现
 */
bool zService::init()
{
	struct sigaction sig;
	sig.sa_handler = ctrlcHandler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT,&sig,NULL);
	sigaction(SIGQUIT,&sig,NULL);
	sigaction(SIGABRT,&sig,NULL);
	sigaction(SIGTERM,&sig,NULL);
	sig.sa_handler = hupHandler;
	sigaction(SIGHUP,&sig,NULL);

	//初始化随即数种子和时区信息
	//Time::getLocalTZ();
	return true;
}

void zService::main()
{
	if(init() && validate())
	{
		while(!isTerminate())
		{
			if(!serviceCallBack())
				break;
		}
	}
	final();
}
