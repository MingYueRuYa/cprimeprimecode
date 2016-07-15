/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef strvec_h

#define strvec_h

#include <iostream>
#include <initializer_list>

using std::string;
using std::initializer_list;
using std::allocator;

class StrVec
{
public:
	explicit StrVec();

	StrVec(initializer_list<string> pStringList);

	~StrVec();

	StrVec(const StrVec &pStrVec);

	StrVec(const StrVec &&pStrVec);

	StrVec& operator=(const StrVec &pStrVec);
	
	StrVec& operator=(const StrVec &&pStrVec);

	void PushBack(const string &pString);
	
	void Foreach();

	size_t Size();

private:
	void Free();

	/*!
	 * reallocator memory
	 * */
	void Reallocator();

	void CheckMemory();

private:
	string *mFirst;	

	string *mEnd;

	string *mCapacity;

	allocator<string> mAllocator;

};

#endif //strvec_h
