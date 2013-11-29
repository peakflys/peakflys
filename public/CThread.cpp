#include "CThread.h"

CThread::CThread()
{
//	hThread = 0; 	
	over = false;
}

void *CThread::threadFunc(void *arg)
{
	CThread *thread = (CThread*)arg;
	//添加初始化操作
	thread->run();
	//添加收尾操作
	pthread_exit(NULL);
}

bool CThread::start()
{
	pthread_mutexattr_t attr;
	pthread_mutexattr_init (&attr);
	if(0 != pthread_create(&hThread,NULL,CThread::threadFunc,this))
	{
		//failure
		return false;
	}
	pthread_mutexattr_destroy (&attr);//
	return true;
}
