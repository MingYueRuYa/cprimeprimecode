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
	newfolder.SetFolderName("Linxu Folder");
	newfolder.GetAllMessage();

	cout << "add new message ...." << endl;
	Message newmsg("news about linux");
	newmsg.Save(newfolder);
	
	newfolder.GetAllMessage();

	Swap(msg, newmsg);	

	cout << "old msg ....." << endl;
	msg.GetFolders();
	cout << msg.GetContent() << endl;
	
	cout << "new msg ....." << endl;
	newmsg.GetFolders();
	cout << newmsg.GetContent() << endl;
	return 0;
}
