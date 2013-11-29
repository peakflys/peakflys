#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>

#include "TCPServer.h"

TCPServer::TCPServer(const std::string &_name) :
	name(_name),
	sock(-1)
{
	kdpfd = epoll_create(1);
	assert(-1 != kdpfd);
}

TCPServer::~TCPServer()
{
	TEMP_FAILURE_RETRY(::close(kdpfd));
	if(-1 != sock)
	{
		::shutdown(sock,SHUT_RD);
		TEMP_FAILURE_RETRY(::close(sock));
		sock = -1;
	}
}

/*
 *\brief 绑定监听服务到指定端口
 *\para name绑定端口名称，port端口
 */
bool TCPServer::bind(const std::string &name,const unsigned short port)
{
	struct sockaddr_in addr;
	if(-1 != sock)
	{
		// 已经初始化
		return false;
	}
	sock = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(-1 == sock)
	{
		//sock fail
		return false;
	}
	//设置套接口为可用状态
	int reuse = 1;
	if(-1 == ::setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse)))
	{
		//不能设置可重用状态
		TEMP_FAILURE_RETRY(::close(sock));
		sock = -1;
		return false;
	}
	//设置套接口发送接收缓冲，并且服务器的必须在accept之前设置
	socklen_t window_size = 128*1024;
	if(-1 == setsockopt(sock,SOL_SOCKET,SO_RCVBUF,&window_size,sizeof(window_size)))
	{
		TEMP_FAILURE_RETRY(::close(sock));
		return false;
	}
	if(-1 == setsockopt(sock,SOL_SOCKET,SO_SNDBUF,&window_size,sizeof(window_size)))
	{
		TEMP_FAILURE_RETRY(::close(sock));
		return false;
	}
	
	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	int retcode = ::bind(sock,(struct sockaddr *)&addr,sizeof(addr));
	if(-1 == retcode)
	{
		//不能帮定服务器端口
		TEMP_FAILURE_RETRY(::close(sock));
		sock = -1;
		return false;
	}

	retcode = ::listen(sock,MAX_WAITQUEUE);
	if(-1 == retcode)
	{
		//listen服务器端口fail
		TEMP_FAILURE_RETRY(::close(sock));
		sock = -1;
		return false;
	}

	//epoll
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.ptr= NULL;
	assert(0 == epoll_ctl(kdpfd,EPOLL_CTL_ADD,sock,&ev));

	//init success
	return true;
}

int TCPServer::accept(struct sockaddr_in *addr)
{
	socklen_t len = sizeof(struct sockaddr_in);
	bzero(addr,len);

	struct epoll_event ev;
	int rc = epoll_wait(kdpfd,&ev,1,TURN_MSE);
	if(1 == rc && (ev.events & EPOLLIN))
		//okay
		return TEMP_FAILURE_RETRY(::accept(sock,(struct sockaddr *)addr,&len));
	return -1;
}
