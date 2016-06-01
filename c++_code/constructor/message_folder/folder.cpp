/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include "folder.h"

Folder::Folder(const Folder &pFolder)
{

}

Folder& Folder::operator=(const Folder &pFolder)
{
	return *this;
}

Folder::~Folder()
{
	RemoveToMessage();
}

void Folder::AddMessage(Message *pMessage)
{
	mMessageSet.insert(pMessage);
}

void Folder::RemoveMessage(Message &pMessage)
{
	mMessageSet.erase(&pMessage);
}

void Folder::AddToMessage(const Folder& pFolder)
{
	for (Message *message : pFolder.mMessageSet) {
		message->AddToFolders(this);
	}
}

void Folder::RemoveToMessage()
{
	 for (Message *message : mMessageSet) {
		message->RemoveFromFolder(this);
	 }
}
