/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef glogencapsulation_h

#define glogencapsulation_h

#include <string>

#include <glog/logging.h>

using std::string;

class glogEncapsulation
{
public:
	static bool Initialize();
	
	static bool Finalize();

	static void Info(const string &pInfoMsg);

	static void Warning(const string &pWarningMsg);
	
	static void Error(const string &pErrorMsg);

	static void Fatal(const string &pFatalMsg);	

private:
	glogEncapsulation();

	~glogEncapsulation();

private:
	static glogEncapsulation* mThis;

};

#endif //glogencapsulation_h
