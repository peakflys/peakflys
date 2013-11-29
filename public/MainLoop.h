#ifndef _MAINLOOP_H
#define _MAINLOOP_H

#include "noCopyable.h"
#include "Log.h"
#include "CThread.h"
#include "TcpTask.h"
#include <vector>
#include <assert.h>

class MainLoop : private NoCopyable , public CThread
{
	public:
		static const std::vector<TcpTask*>::size_type maxTask = 256;
		MainLoop():log("mainLoop")
		{
			taskNum = 0;
			epfd = epoll_create(maxTask);
			assert(-1 != epfd);
			epfdVec.resize(maxTask);
		}
		~MainLoop()
		{
			TerminateAll();	
		}
		void run();
		static MainLoop &getMe()
		{
			if(!instance)
				instance = new MainLoop();
			return *instance;
		}
		static void delMe()
		{
			if(instance)
				delete instance;
		}
		void putTask(TcpTask* tcpTask)
		{
			if(tcpTask)
			{
				tcpTask->addEpoll(epfd,EPOLLIN | EPOLLERR | EPOLLPRI,(void *)tcpTask);//EPOLLOUT 不监听
				taskVec.push_back(tcpTask);	
				taskNum = taskVec.size();
				if(taskNum > epfdVec.size())
				{
					epfdVec.resize(taskNum + 16);
				}
				tcpTask->recvCmd();
			}
		}
		void TerminateAll();
	private:
	//	Log log("时间循环");//不能在类体内初始化变量
		Log log;
		static MainLoop * instance;
		std::vector<TcpTask*> taskVec;
		std::vector<epoll_event> epfdVec;
		std::vector<epoll_event>::size_type taskNum;
		int epfd;
};
#endif
