/**
 *\brief 连接类
 *
 */
#ifndef _TcpTask_H
#define _TcpTask_H

#include <netinet/in.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <fcntl.h> 
#include <iostream> 
#include <signal.h> 
#include <sys/epoll.h> 
#include <errno.h>
#include "command.h"

#include "Log.h"

class TcpTask
{
	public:
		TcpTask(const int _sock,const struct sockaddr_in *_addr):sock(_sock),log("tcpTask")
		{
			bzero(&addr,sizeof(addr));
			bcopy(_addr,&addr,sizeof(addr));
			reading = false;
			terminating = false;
		}
		bool sendCmd(const char *pstrcmd);
		int recvCmd(); //接收消息，上层epoll监听
		bool msgParse(const unsigned char* ptCmd,const unsigned int cmdLen);//解析消息
		bool loginMsgParse(const t_NullCmd* ptCmd,const unsigned int cmdLen);
		bool userMsgParse(const t_NullCmd* ptCmd,const unsigned int cmdLen);
		void setReading() 
		{
			reading = true;
		}
		bool isReading() const
		{
			return reading;
		}
		void terminate()
		{
			terminating = true;
		}
		bool isTerminate() const
		{
			return terminating;
		}
		bool Terminate()
		{
			if(isTerminate())		
			{
				TEMP_FAILURE_RETRY(::close(sock));	
				return true;
			}
			return false;
		}
		void delEpoll(int dpfd,unsigned int events)
		{
			epoll_event ev;
			ev.events = events;
			ev.data.ptr = NULL;
			if(-1 == epoll_ctl(dpfd,EPOLL_CTL_DEL,sock,&ev))
			{
				log.printLog("关闭套接口%u epoll失败",sock);
			}
		}
		void addEpoll(int dpfd,unsigned int events,void *ptr)
		{
			epoll_event ev;
			ev.events = events;
			ev.data.ptr = ptr;
			if(-1 == epoll_ctl(dpfd,EPOLL_CTL_ADD,sock,&ev))
			{
				log.printLog("添加套接口%u epoll失败",sock);
			}
		}
	private:
		int sock;  //套接口
		struct sockaddr_in addr;  //套接口地址
		bool reading;
		bool terminating;
		//Log log( "TcpTask" );//不能在类体内定义这样的对象？？？
		Log log;
};

#endif
