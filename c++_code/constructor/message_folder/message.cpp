/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <iostream>

#include "message.h"
#include "folder.h"

using std::cout;
using std::endl;

Message::Message(string pContent)
	: content(pContent)
{
}

Message::~Message()
{
	RemoveFromFolder();
}

Message::Message(const Message &pMessage)
	: content(pMessage.content), mFolderSet(pMessage.mFolderSet)
{
	RemoveFromFolder();
	AddToFolders(this);
}

Message& Message::operator=(const Message &pMessage)
{
	RemoveFromFolder();
	content = pMessage.content;
	mFolderSet = pMessage.mFolderSet;
	AddToFolders(this);
	return *this;
}

void Message::Save(Folder &pFolder)
{
	mFolderSet.insert(&pFolder);
	pFolder.AddMessage(this);
}

void Message::Remove(Folder &pFolder)
{
	mFolderSet.erase(&pFolder);
	pFolder.RemoveMessage(this);
}

string Message::GetContent() const
{
	return content;
}

void Message::GetFolders() const
{
	for (Folder *folder : mFolderSet) {
		cout << folder->GetFolderName() << endl;
	}
}

void Message::AddToFolders(Message *pMessage)
{
	for (Folder *folder : mFolderSet) {
		folder->AddMessage(pMessage);
	}
}

void Message::RemoveFromFolder()
{
	for (Folder *folder : mFolderSet) {
		folder->RemoveMessage(this);
	}
}
