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

void Message::AddToFolders(Message *pMessage)
{
	for (Folder *folder : pMessage->mFolderSet) {
		folder->AddMessage(pMessage);
	}
}

void Message::RemoveFromFolder()
{
	for (Folder *folder : mFolderSet) {
		folder->RemoveMessage(this);
	}
}
