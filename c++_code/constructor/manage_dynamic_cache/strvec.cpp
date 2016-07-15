/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <memory>
#include <iostream>
#include <algorithm>

#include "strvec.h"

using std::cout;
using std::endl;

StrVec::StrVec()
{
	mFirst = nullptr;	
	mEnd = nullptr;
	mCapacity = nullptr;	
}

StrVec::StrVec(std::initializer_list<string> pStringList)
{
	mFirst = mAllocator.allocate(pStringList.end() - pStringList.begin());
	mEnd = uninitialized_copy(pStringList.begin(), pStringList.end(), mFirst);
}

StrVec::~StrVec()
{
	Free();
}

StrVec::StrVec(const StrVec &pStrVec)
{
	
}

StrVec::StrVec(const StrVec &&pStrVec)
{

}

StrVec& StrVec::operator=(const StrVec &pStrVec)
{
	return *this;
}

StrVec& StrVec::operator=(const StrVec &&pStrVec)
{
	return *this;
}

void StrVec::PushBack(const string &pString)
{
	//check memory is enough	
	//CheckMemory()
	mAllocator.construct(mEnd++, pString);
}

void StrVec::Foreach()
{
	string *tempstring = mFirst;
	while (mEnd - tempstring) {
		cout << *tempstring++ << " ";
	}
	cout << endl;
}

size_t StrVec::Size()
{
	return mEnd - mFirst;
}

void StrVec::Free()
{
	if (nullptr != mFirst && nullptr != mEnd) {
		string *tempstring = mFirst;
		while (mEnd - tempstring) {
			mAllocator.destroy(tempstring++);	
		}
		mAllocator.deallocate(mFirst, mCapacity - mFirst);
	}
}

void StrVec::Reallocator()
{
	size_t size = mEnd - mFirst;	
	string *firstaddr = mAllocator.allocate(size * 2);
	string *endaddr = uninitialized_copy(mFirst, mEnd, firstaddr);
	Free();
	mFist = firstaddr;
	mEnd = endaddr;
	mCapacity = mFirst + size * 2;
}

bool StrVec::CheckMemory()
{
	size_t currentsize = mEnd - mFirst;
	size_t maxsize = mCapacity - mFirst;
	if (currentsize >= maxsize) {
		return true;
	}	
	return false;
}

