/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <iostream>

#include "folder.h"

using std::string;
using std::cout;
using std::endl;

Folder::Folder(string pFolderName)
	: mFolderName(pFolderName)
{
}

Folder::Folder(const Folder &pFolder)
{
	mFolderName = pFolder.GetFolderName();
	RemoveFromFolder();
	AddToFolder(pFolder);
}

Folder& Folder::operator=(const Folder &pFolder)
{
	mFolderName = pFolder.GetFolderName();
	RemoveFromFolder();
	AddToFolder(pFolder);
	return *this;
}

Folder::~Folder()
{
}

string Folder::GetFolderName() const
{
	return mFolderName;
}
	
void Folder::GetAllMessage() const
{
	for (Message *message : mMessageSet) {
		cout << message->content << endl;
	}
}

void Folder::AddMessage(Message *pMessage = nullptr)
{
	mMessageSet.insert(pMessage);
}

void Folder::RemoveMessage(Message *pMessage)
{
	mMessageSet.erase(pMessage);
}

void Folder::AddToFolder(const Folder &pFolder)
{
	for (Message *message : pFolder.mMessageSet) {
		mMessageSet.insert(message);
	}
}

void Folder::RemoveFromFolder()
{
	for (Message *message : mMessageSet) {
		this->RemoveMessage(message);
	}
}

