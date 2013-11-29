#ifndef _CTHREAD_H
#define _CTHREAD_H

#include <pthread.h>
#include <unistd.h>

class CCriticalSection
{
	public:
		CCriticalSection()
		{
			pthread_mutexattr_t attr;
			pthread_mutexattr_init (&attr);
			pthread_mutexattr_settype (&attr, PTHREAD_MUTEX_RECURSIVE);
			pthread_mutex_init (&m_pLock, &attr);
			pthread_mutexattr_destroy (&attr);//
		}
		virtual ~CCriticalSection()
		{
			pthread_mutex_destroy (&m_pLock);
		}
		void Lock(){pthread_mutex_lock (&m_pLock);}
		void Unlock(){pthread_mutex_unlock (&m_pLock);}

	protected:
		pthread_mutex_t m_pLock;
};

// 线程基类，实现线程的创建及删除
class CThread
{
	public:
		CThread();
		~CThread(){};

		static void* threadFunc(void *arg);//线程执行函数
		bool start(); //创建线程处
		virtual void run() = 0;//逻辑处理处
		void final()
		{
			over = true;
		}
		bool isFinal() const 
		{
			return over;
		}
	protected:
		pthread_t hThread;       // this thread's HANDLE
		volatile bool over;
};

#endif
