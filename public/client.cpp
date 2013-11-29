
/* 
*\ ¿Í»§¶ËÔ´´úÂë 
*/ 
#include <iostream> 
#include <unistd.h>//TEMP_FAILURE_RETRY
#include <errno.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <sys/types.h> 
#include <sys/socket.h> 

#define PORT 8888 

int main(int argc, char* argv[], char* evp[]) 
{ 
    int fd; 
    int on = 1; 
    char buffer[512]; 

    struct sockaddr_in seraddr; 
    memset(&seraddr, 0, sizeof(seraddr)); 

    if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        std::cout << "¿Í»§¶Ë´´½¨Ì×½Ó×Ö³ö´íÁË" << std::endl; 
        return -1; 
    } 

    //Èç¹ûÓÃÓÚ¶à´Î²âÊÔ£¬ÄÇÃ´´ò¿ªÏÂÃædebugÑ¡Ïî 

#ifdef _Debug_ming 
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)); 
#endif 

    seraddr.sin_port = htons((short)(PORT)); 
    seraddr.sin_family = AF_INET; 
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");//ÉèÖÃ×Ô¼ºµÄip°É 

    //ÄãÒ²¿ÉÒÔ²ÉÓÃÎÞ×èÈûÁ¬½Ó£¬²»¹ýÐèÒª¶ÔÁ¬½ÓµÄ´íÎó½á¹û½øÐÐ·ÖÎö´¦Àí 

    if(TEMP_FAILURE_RETRY(connect(fd, (struct sockaddr*)&seraddr, sizeof(seraddr)) < 0)) 
    { 
        std::cout << "Á¬½Ó´íÎóÁË" << std::endl; 
        return -1; 
    } 
    //ÏÂÃæ¾Í½øÐÐÊÕ·¢ÐÅÏ¢ 

    bcopy("this is client",buffer,sizeof("this is client")); 
    send(fd, buffer, strlen(buffer), 0); 
    bzero(buffer, sizeof(buffer)); 
    recv(fd, buffer, sizeof(buffer), 0); 
	std::cout<<"Server:"<<std::endl;
	std::cout<<"\t"<<buffer<<std::endl;
    exit(0); 
} 
