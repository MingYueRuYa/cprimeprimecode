/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef folder_h 

#define folder_h

#include <set>

#include "message.h"

using std::set;

class Folder 
{
	friend class Message;
public:
	Folder() = default;

	Folder(const Folder &pFolder);

	Folder& operator=(const Folder &pFolder);

	~Folder();

	void AddMessage(Message *pMessage);

	void RemoveMessage(Message *pMessage);

private:
	set<Message *> mMessageSet;

	void AddToMessage(Folder&);

	void RemoveToMessage(Message &pMessage);

};

#endif //folder_h
