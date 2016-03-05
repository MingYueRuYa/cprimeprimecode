/*
 * 计时代码段
 * */

#include <iostream>
#include <stdio.h>
#include <sys/time.h>

//using namespace std;

int main(void)
{
	struct timeval starttime, endtime;
	gettimeofday(&starttime, NULL);
	for (int i = 0; i < 100000; ++i) {
		//TODO
	}
	gettimeofday(&endtime, NULL);
	long usedtime = 1000000 * (endtime.tv_sec - starttime.tv_sec) + (endtime.tv_usec - starttime.tv_usec);
	std::cout << "time used:" << usedtime / 100000.0 << std::endl;
	//printf("time used: %f\n", usedtime / 100000.0);
	return 0;
}
