/*!
 * 计时器函数
 * 毫秒级别
 * */
#include <sys/time.h>

int main(int argc, char *argv[])
{
	struct timeval starttime, endtime;
	gettimeofday(&starttime, 0);
	int i = 0;
	for (i = 0; i < 100000; ++i) {
		//TODO someting
	}
	gettimeofday(&endtime, 0);
	double consumetime = 1000000 * (endtime.tv_sec - starttime.tv_sec)  + (endtime.tv_usec - starttime.tv_usec);
	printf("%f", consumetime / 1000);
	return 0;
}
