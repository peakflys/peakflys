#ifndef _TCPSERVER_H
#define _TCPSERVER_H

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string>
#include "noCopyable.h"

class TCPServer : private NoCopyable
{
	public:
		TCPServer(const std::string &name);
		~TCPServer();
		bool bind(const std::string &name,const unsigned short port);
		int accept(struct sockaddr_in *addr);
	private:
		static const int TURN_MSE = 2100;//轮询超时，单位毫秒
		static const int MAX_WAITQUEUE = 2000; //最大等待队列
		std::string name; //服务器名称
		int sock;
		int kdpfd; //epool
};

#endif
