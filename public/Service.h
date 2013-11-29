#ifndef _SERVICE_H
#define _SERVICE_H

#include "zService.h"
#include "TCPServer.h"

class Service : public zService
{
	public:
		virtual ~Service() {instance = NULL;}
		//根据得到的TCP/IP连接获取一个连接任务
		virtual void genTCPTask(const int sock,const struct sockaddr_in *addr) = 0;
		//获取连接数
		virtual const int getPoolSize() const
		{
			return 0;
		}
		//获取连接池的状态
		virtual const int getPoolState() const
		{
			return 0;
		}
	protected:
		Service(const std::string &name) : zService(name)
		{
			instance = this;
			serviceName = name;
			tcpServer = NULL;
		}

		bool init(unsigned short port);
		bool serviceCallBack();
		void final();
	private:
		static Service *instance;
		std::string serviceName;
		TCPServer *tcpServer;//TCP服务器实例指针
};

#endif
