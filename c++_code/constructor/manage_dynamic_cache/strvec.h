/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef strvec_h

#define strvec_h

#include <iostream>

using std::string;

class StrVec
{
public:
	StrVec();

	~StrVec();

	StrVec(const StrVec &pStrVec);

	StrVec& operator=(const StrVec &pStrVec);

private:
	string *mFirst;	

	string *mEnd;

	string *mCapacity;

};

#endif //strvec_h
