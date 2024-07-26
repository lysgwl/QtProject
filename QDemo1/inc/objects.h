#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "stheader.h"

class CObject : public QObject
{
public:
	CObject() {};
	virtual ~CObject() {};
};

/*
	如果基类中的默认构造函数、拷贝构造函数、拷贝赋值运算符或析构函数是被删除的函数或者不可访问，
	则派生类中对应的成员将是被删除的，原因是编译器不能使用基类成员来执行派生类对象基类部分的构造、赋值或销毁操作。
*/
class CNonCopyable
{
protected:
	CNonCopyable() {};
	virtual ~CNonCopyable() {};

private:
	CNonCopyable(const CNonCopyable &);
	const CNonCopyable &operator=(const CNonCopyable &);
};

template<typename T>
struct is_array_type
{
	static const bool value = false;
};

template<typename T>
struct is_array_type<T[]>
{
	static const bool value = true;
};

template<typename T, int is_array>
class uniqueptr_deleter
{
public:
	void operator()(T*& _ptr) const
	{
		if (_ptr)
		{
			if (is_array)
			{
				delete[] _ptr;
			}
			else
			{
				delete _ptr;
			}

			_ptr = NULL;
		}
	}
};

template <class T> inline const char * get_obj_iid() { return Q_NULLPTR; }

#endif
