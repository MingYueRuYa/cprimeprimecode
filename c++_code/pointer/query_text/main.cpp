/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <iostream>
#include <string>
#include <stdio.h>

#include "querytext.h"

using namespace std;

int main(int argc, char *argv[])
{
	QueryText querytext(string("storyDataFile.txt"));
	while (true) {
		cout << "enter word to look for, or enter q to quit:" << endl;
		string content;
		if (! (cin >> content) || "q" == content) {
			break;
		}
		print(cout, querytext.Query(content));
	}
	return 0;
}


