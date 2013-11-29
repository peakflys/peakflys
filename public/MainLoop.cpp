#include "MainLoop.h"

MainLoop * MainLoop::instance = NULL;

void MainLoop::run()
{
	std::vector<epoll_event> epfrVec;
	int kepfd_r = epoll_create(256); 
	assert(-1 != kepfd_r);
	epfdVec.resize(256);
	unsigned int fdCount = 0;
	bool check = false;
	unsigned long long elapse_2 = 0;
	unsigned long long elapse_50 = 0;
	while(!isFinal())	
	{
		++elapse_2;
		++elapse_50;
		if(check)
		{
			if(!taskVec.empty())
			{
				for(std::vector<TcpTask*>::iterator it=taskVec.begin();it!=taskVec.end();)	
				{
					TcpTask *task = *it;
					if(task->isTerminate())	
					{
						if(task->isReading())
						{
							task->delEpoll(kepfd_r,EPOLLIN | EPOLLERR | EPOLLPRI);	
							--fdCount;
						}
						task->Terminate();
						it = taskVec.erase(it);
						delete task;
						continue;
					}
					if(!task->isReading())
					{
						task->addEpoll(kepfd_r,EPOLLIN | EPOLLERR | EPOLLPRI,(void *)task);
						task->setReading();
						++fdCount;
						if(fdCount > epfrVec.size())
						{
							epfrVec.resize(fdCount + 16);
						}
					}
					++it;
				}
				check = false;
			}
		}
		if(elapse_2/2000)
		{
			int num = epoll_wait(kepfd_r,&epfrVec[0],fdCount,0);	
			if(num > 0)
			{
				for(int i=0;i<num;++i)
				{
					TcpTask *task = (TcpTask*)epfrVec[i].data.ptr;
					if(epfrVec[i].events & (EPOLLERR | EPOLLPRI))
					{
						task->terminate();
					}
					else
					{
						if(epfrVec[i].events & EPOLLIN)
						{
							if(-1 == task->recvCmd())
							{
								log.printLog("msgParse Error");		
								task->terminate();
							}
						}
					}
					epfrVec[i].events = 0;
				}
			}
			check = true;
			elapse_2 = 0;
		}
		if(check)
			continue;
		if(elapse_50/50000)
		{
			int num = epoll_wait(epfd,&epfdVec[0],taskNum,0);	
			if(num > 0)
			{
				for(int i=0;i<num;++i)
				{
					TcpTask *task = (TcpTask*)epfdVec[i].data.ptr;
					if(epfrVec[i].events & (EPOLLERR | EPOLLPRI))
					{
						task->terminate();
					}
					else
					{
						if(epfrVec[i].events & EPOLLIN)
						{
							if(-1 == task->recvCmd())
							{
								log.printLog("msgParse Error");		
								task->terminate();
							}
						}
						//可以扩充OUT等
					}
					epfrVec[i].events = 0;
				}
			}
			check = true;
			elapse_50 = 0;
		}
	}

	//关闭所有连接
	TerminateAll();
}

void MainLoop::TerminateAll()
{
	for(std::vector<TcpTask*>::iterator it=taskVec.begin();it!=taskVec.end();++it)
	{
		(*it)->Terminate();
		delete *it;
	}
	taskVec.clear();
}

