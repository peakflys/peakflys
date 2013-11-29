#include "Global.h"
namespace Global
{
	Log *glog = NULL;
	static void initGlobal() __attribute__((constructor));
	void initGlobal()
	{
		//init global data
	}
	static void finalGlobal() __attribute__((destructor));
	void finalGlobal()
	{
		delete glog;//释放全局log内存
	}
};
