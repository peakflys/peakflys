#ifndef _COMMAND_H
#define _COMMAND_H

#include "Type.h"

const BYTE LOGIN_CMD = 1;
const BYTE USER_CMD = 2;
/**********************************************/
/*
 *\brief 消息基本结构
 */
struct t_NullCmd
{
	BYTE cmd;
	BYTE para;
	t_NullCmd()
	{
		cmd = para = 0;
	}
};
const BYTE CLIENT_NULL_PARA = 1;
/*********************登录消息开始**********************/
struct stLoginCmd : public t_NullCmd
{
	stLoginCmd()
	{
		cmd = LOGIN_CMD;
	}
};

const BYTE CHECK_PSW_CMD = 1;
struct stCheckPasswordCmd : public stLoginCmd
{
	stCheckPasswordCmd()
	{
		para = CHECK_PSW_CMD;
		bzero(name,sizeof(name));
		bzero(psw,sizeof(psw));
	}
	char name[MAX_NAMESIZE+1];
	char psw[MAX_PSWSIZE+1];
};

enum
{
	ERROR_COMMON = 0,//正常状态
	ERROR_NOUSER = 1,//无帐号
	ERROR_PSWERR = 2,//密码错误
	ERROR_HASUSER = 3,//帐号重复
};
const BYTE RET_CHECK_PSW_CMD = 2;
struct stRetCheckPasswordCmd :  public stLoginCmd
{
	stRetCheckPasswordCmd()
	{
		para = RET_CHECK_PSW_CMD;
		error = ERROR_PSWERR;
	}
	BYTE error;
};

const BYTE RET_SUCCESS_LOG_CMD = 3;
struct stRetSuccessLogCmd :  public stLoginCmd
{
	stRetSuccessLogCmd()
	{
		para = RET_SUCCESS_LOG_CMD;
		bzero(data,sizeof(data));
	}
	char data[MAX_USERDATA+1];
};

const BYTE REQ_REG_CMD = 4;
struct stReqRegCmd : stLoginCmd
{
	stReqRegCmd()
	{
		para = REQ_REG_CMD;
		bzero(name,sizeof(name));
		bzero(psw,sizeof(psw));
	}
	char name[MAX_NAMESIZE+1];
	char psw[MAX_PSWSIZE+1];
};

/*********************登录消息结束**********************/

/*********************玩家游戏消息开始**********************/
struct stUserPlayCmd : public t_NullCmd
{
	stUserPlayCmd()
	{
		cmd = USER_CMD;
	}
};
/*********************玩家游戏消息结束**********************/
#endif
