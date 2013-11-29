
/* 
*\ ·þÎñÆ÷¶ËµÄÔ´´úÂë 
*/ 
#include <netinet/in.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <fcntl.h> 
#include <iostream> 
#include <signal.h> 
#include <sys/epoll.h> 

#define MAXFDS 256 
#define EVENTS 100 
#define PORT 8888 

static bool setNonBlock(int fd) 
{ 
    int flags = fcntl(fd, F_GETFL, 0); 
    flags |= O_NONBLOCK; 
    if(-1 == fcntl(fd, F_SETFL, flags)) 
        return false; 
    return true; 
} 

int main(int argc, char* argv[], char* evp[]) 
{ 
	int epfd; 
    int fd, nfds, confd; 
    int on = 1; 
    char buffer[512]; 
    struct sockaddr_in saddr, caddr; 
    struct epoll_event ev, events[EVENTS]; 

    if((fd = socket(AF_INET, SOCK_STREAM,0)) < 0) 
    { 
        std::cout << "´´½¨Ì×½Ó×Ö³ö´íÀ²" << std::endl; 
        return -1; 
    } 


    struct sigaction sig; 
    sigemptyset(&sig.sa_mask); 
    sig.sa_handler = SIG_IGN; 
    sigaction(SIGPIPE, &sig, NULL); 

    epfd = epoll_create(MAXFDS); 

    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)); 
     
    memset(&saddr, 0, sizeof(saddr)); 
    saddr.sin_family = AF_INET; 
    saddr.sin_port = htons((short)(PORT)); 
    saddr.sin_addr.s_addr = INADDR_ANY; 
    if(-1 == bind(fd, (struct sockaddr*)&saddr, sizeof(saddr))) 
    { 
        std::cout << "Ì×½Ó×Ö²»ÄÜ°ó¶¨µ½·þÎñÆ÷ÉÏ" << std::endl; 
        return -1; 
    } 

    if(-1 == listen(fd, 32)) 
    { 
        std::cout << "¼àÌýÌ×½Ó×ÖµÄÊ±ºò³ö´íÁË" << std::endl; 
        return -1; 
    } 
	ev.data.fd = fd; 
    ev.events = EPOLLIN; 
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev); 

    while(true) 
    { 
        nfds = epoll_wait(epfd, &events[0], MAXFDS, 0); 

        for(int i=0; i < nfds; ++ i) 
        { 
            if(fd == events[i].data.fd) 
            { 
                bzero(&caddr, sizeof(caddr)); 
				socklen_t clientlen = sizeof(caddr);
                int cfd = accept(fd, (struct sockaddr*)&caddr, &clientlen); 
                if(-1 == cfd) 
                { 
                    std::cout << "·þÎñÆ÷½ÓÊÕÌ×½Ó×ÖµÄÊ±ºò³öÎÊÌâÁË" << std::endl; 
                    break; 
                } 

                setNonBlock(cfd); 

                ev.data.fd = cfd; 
                ev.events = EPOLLIN; 
                epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);  
            } 
            else if(events[i].events & EPOLLIN) 
            { 
                bzero(&buffer, sizeof(buffer)); 
               // std::cout << "·þÎñÆ÷¶ËÒª¶ÁÈ¡¿Í»§¶Ë·¢¹ýÀ´µÄÏûÏ¢" << std::endl; 
			   	std::cout<<"Client:"<<std::endl;
                int ret = recv(events[i].data.fd, buffer, sizeof(buffer), 0); 
                if(ret < 0) 
                { 
                    //std::cout << "·þÎñÆ÷ÊÕµ½µÄÏûÏ¢³ö´íÁË" << std::endl; 
					std::cout<<"recv error"<<std::endl;
                    return -1; 
                } 
                //std::cout << "½ÓÊÕµ½µÄÏûÏ¢Îª£º" << (char*) buffer << std::endl; 
				std::cout<<"\t"<<buffer<<std::endl;
                ev.data.fd = events[i].data.fd; 
                ev.events = EPOLLOUT; 
                epoll_ctl(epfd, EPOLL_CTL_MOD, events[i].data.fd, &ev); 
            } 
            else if(events[i].events & EPOLLOUT) 
            { 
                bzero(buffer, sizeof(buffer)); 
                //bcopy("The Author@: magicminglee@Hotmail.com", buffer, sizeof("The Author@: magicminglee@Hotmail.com")); 
				bcopy("this is server",buffer,sizeof("this is server"));
                int ret = send(events[i].data.fd, buffer, strlen(buffer),0); 
                if(ret < 0) 
                { 
                    //std::cout << "·þÎñÆ÷·¢ËÍÏûÏ¢¸ø¿Í»§¶ËµÄÊ±ºò³ö´íÀ²" << std::endl; 
					std::cout<<"send error"<<std::endl;
                    return -1; 
                } 
                ev.data.fd = events[i].data.fd; 
                epoll_ctl(epfd, EPOLL_CTL_DEL, ev.data.fd, &ev); 
            } 
        } 
    } 
    if(fd > 0) 
    { 
        shutdown(fd, SHUT_RDWR); 
        close(fd); 
    } 
} 

