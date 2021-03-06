/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef message_h

#define message_h

#include <string>
#include <set>

//#include "folder.h"

using std::string;
using std::set;

class Folder;

class Message
{
	friend class Folder;

	void friend Swap(Message &pLeftMessage, Message &pRightMessage);

public:
	Message(string pContent = "new Message");

	~Message();

	Message(const Message &pMessage);

	Message& operator=(const Message &pMessage);

	void Save(Folder &pFolder);

	void Remove(Folder &pFolder);

	string GetContent() const;

	void GetFolders() const;

private:
	string content;	

	set<Folder *> mFolderSet;

	void AddToFolders(Message *pMessage);

	void RemoveFromFolder();
};

void  Swap(Message &pLeftMessage, Message &pRightMessage);

#endif //message_h
