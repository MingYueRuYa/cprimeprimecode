/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include "message.h"
#include "folder.h"

Message::Message()
{
	content = "";
}

Message::~Message()
{
	RemoveFromFolder();
}

Message::Message(const Message &pMessage)
	: content(pMessage.content), mFolderSet(pMessage.mFolderSet)
{
	AddToFolders(pMessage);
}

Message& Message::operator=(const Message &pMessage)
{
	RemoveFromFolder();
	content = pMessage.content;
	mFolderSet = pMessage.mFolderSet;
	AddToFolders(pMessage);
	return *this;
}

void Message::Save(const Folder &pFolder)
{
	mFolderSet.insert(pFolder);
	pFolder.AddMessage(this);
}

void Message::Remove(const Folder &pFolder)
{
	mFolderSet.erase(pFolder);
	pFolder.RemoveMessage(this);
}

void Message::AddToFolders(const Message &pMessage)
{
	for (Folder *folder : pMessage.mFolderSet) {
		folder->AddMessage(this);
	}
}

void Message::RemoveFromFolder()
{
	for (Folder *folder : mFolderSet) {
		folder->RemoveMessage(this);
	}
}
