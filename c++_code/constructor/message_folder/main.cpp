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

int main(int argc, char *argv[])
{
	Folder folder("new Folder");
	Message msg("new Message");
	msg.Save(folder);	
	msg.GetFolders();
	folder.GetAllMessage();

	Folder newfolder = folder;
	cout << newfolder.GetFolderName() << endl;

	newfolder.GetAllMessage();
	
	return 0;
}
