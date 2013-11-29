/**
 *\brief 服务器框架
 */
#ifndef _zService_H
#define _zService_H

//#include <iostream>
#include <string>
//#include <vector>
//#include <sstream>
//#include <unistd.h>
//#include <assert.h>
#include <signal.h>

#include "noCopyable.h"

class zService : private NoCopyable
{
	public:
		virtual ~zService() {serviceInst = NULL;}
		virtual void reloadData()
		{
			//logger->debug("%s",__PRETTY_FUNCTION__);
		}
		bool isTerminate() const
		{
			return terminate;
		}
		void Terminate()
		{
			terminate = true;
		}
		void main();
		static zService *getInstance()
		{
			return serviceInst;
		}
	protected:
		zService(const std::string &_name):name(_name)
		{
			serviceInst = this;
			terminate = false;
		}
		virtual bool init();
		virtual bool validate() //是否初始化成功
		{
			return true;
		}
		virtual bool serviceCallBack() = 0;//监听服服务器端口
		virtual void final() = 0;
	private:
		static zService *serviceInst;
		std::string name;
		bool terminate;
};
#endif
