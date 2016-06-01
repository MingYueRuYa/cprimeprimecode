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

public:
	Message();

	~Message();

	Message(const Message &pMessage);

	Message& operator=(const Message &pMessage);

	void Save(const Folder &pFolder);

	void Remove(const Folder &pFolder);

private:
	string content;	

	set<Folder *> mFolderSet;

	void AddToFolders(const Message &pMessage);

	void RemoveFromFolder();
};

#endif //message_h
