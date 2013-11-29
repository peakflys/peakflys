/**
 *\brief 禁用掉拷贝构造和赋值操作符
 */
#ifndef _noCopyable_H
#define _noCopyable_H

class NoCopyable
{
	protected:
		NoCopyable(){}
		~NoCopyable(){}
	private:
		NoCopyable(const NoCopyable &);
		const NoCopyable & operator = (NoCopyable&); 
};

#endif
