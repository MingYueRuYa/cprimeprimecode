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
	Folder(string pFolderName = "defualt");

	Folder(const Folder &pFolder);

	Folder& operator=(const Folder &pFolder);

	~Folder();

	void AddMessage(Message *pMessage);

	void RemoveMessage(Message *pMessage);

	string GetFolderName() const;

	void SetFolderName(const string &pFolderName);

	void GetAllMessage() const;

private:
	void AddToFolder(const Folder &pFolder);

	void RemoveFromFolder();

private:
	string mFolderName;

	set<Message *> mMessageSet;

};

#endif //folder_h
