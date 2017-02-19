/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <iostream>

#include "blob.h"
#include "blobptr.h"

int main01(int argc, char *argv[])
{
	Blob<int> blobs = {1, 2, 3, 4, 5};
	
//	for (int i=0; i<blobs.Size(); ++i) {
//		std::cout << blobs[i] << " ";
//	}
//

//	while (! blobs.Empty()) {
//		std::cout << blobs.Back() << " ";
//		blobs.Pop_Back();
//	}

	//std::cout << std::endl;

	//BlobPtr<int> blobptr;

	return 0;
}


int main(int argc, char *argv[])
{
//	BlobPtr<int> bptr1;	
//	BlobPtr<int> bptr2;	
//	bptr1 == bptr2;

	Blob<int> blob1;
	BlobPtr<int> bptr3(blob1, 5);
	return 0;
}
