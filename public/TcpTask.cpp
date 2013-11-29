#include "TcpTask.h"

bool TcpTask::sendCmd(const char *pstrcmd)
{
	if(-1 == sock)
		return false;
	int ret = ::send(sock,pstrcmd,strlen(pstrcmd),MSG_NOSIGNAL);
	if(ret < 0)
	{
		log.printLog("发送消息失败");
		return false;
	}
	return true;
}

int TcpTask::recvCmd()
{
	if(-1 == sock)
		return -1;
	char buff[128*1024];
	int ret = TEMP_FAILURE_RETRY(::recv(sock,buff,sizeof(buff),MSG_NOSIGNAL));
	if(-1 == ret && (errno == EAGAIN || errno == EWOULDBLOCK))
	{
		//shoud retry
		return 0;
	}
	if(ret > 0)
	{
		t_NullCmd *ptNullCmd = (t_NullCmd *)buff;
		if(0 == ptNullCmd->cmd && CLIENT_NULL_PARA == ptNullCmd->para)
		{
			log.printLog("recv test signal");	
			if(!sendCmd((char *)ptNullCmd))//心跳测试
			{
				return -1;//fd EOF
			}
		}
		else if(!msgParse((unsigned char*)buff,sizeof(buff)))
		{
			log.printLog("msgParse Error");
			return 0;
		}
	}
	return -1;//ret==0 表明对方socket已关闭
}

bool TcpTask::msgParse(const unsigned char* ptCmd,const unsigned int cmdLen)
{
	t_NullCmd *ptNullCmd = (t_NullCmd *)ptCmd;
	if(ptNullCmd)
	{
		switch(ptNullCmd->cmd)	
		{
			case LOGIN_CMD:
				{
					return loginMsgParse(ptNullCmd,cmdLen);	
				}
				break;
			case USER_CMD:
				{
					return userMsgParse(ptNullCmd,cmdLen);	
				}
				break;
			default:
				{
					log.printLog("error cmd (%u,%u)",ptNullCmd->cmd,ptNullCmd->para);
				}
		}
		return true;
	}
	return false;
}

bool TcpTask::loginMsgParse(const t_NullCmd* ptNullCmd,const unsigned int cmdLen)
{
	stLoginCmd *loginCmd = (stLoginCmd *)ptNullCmd;
	if(loginCmd)	
	{
		switch(loginCmd->para)
		{
			case CHECK_PSW_CMD:
				{
					stCheckPasswordCmd *rev = (stCheckPasswordCmd *)loginCmd;
					if(rev)
					{
						/*User* user = UserManager::getInstance().getUserByName(rev->name);		
						if(!user)
						{
							stRetCheckPasswordCmd send;
							send.error = ERROR_NOUSER;
							sendCmd(&send)
							return true;
						}
						else if(strncmp(user->psw,rev->psw,MAX_PSWSIZE))
						{
							stRetCheckPasswordCmd send;
							send.error = ERROR_PSWERR;
							sendCmd(&send)
							return true;
						}
						else
						{
							stRetSuccessLogCmd send;
							std::ostringstream oss;
							oss<<"Welcom "<<user->name<<"("<<ddr.sin_addr.s_addr<<")";
							bcopy(oss.str().c_str(),send.data);
							sendCmd(&send);	
							return true;
						}*/
						return true;
					}
					return true;
				}
				break;
			case REQ_REG_CMD:
				{
					stReqRegCmd *rev = (stReqRegCmd *)loginCmd;	
					if(rev)
					{
					/*	if( UserManager::getInstance().checkName(rev->name))
						{
							UserManager::getInstance().addUser(rev->name,rev->psw);	
							//register success
						}
						else
						{
							stRetCheckPasswordCmd send;
							send.error = ERROR_HASUSER;
							sendCmd(&send)
							return true;
						}*/
					}
					return true;
				}
				break;
			default:
				{
					log.printLog("loginCmd error(para->%u)",loginCmd->para);
				}
		}
		return true;
	}
	return false;
}
bool TcpTask::userMsgParse(const t_NullCmd* ptNullCmd,const unsigned int cmdLen)
{
	stUserPlayCmd *userCmd = (stUserPlayCmd*)ptNullCmd;
	if(userCmd)
	{
		switch(userCmd->para)	
		{
			
		}
		return true;
	}
	return false;
}
