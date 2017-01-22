#include "context.h"
#include "strategysub.h"
#include "strategyadd.h"

int main(int argc, char *argv[])
{
	Context context;
	//注意内存释放，这里没有进行内存的释放
	context.CreateStrategy(new StrategySub());
	context.CreateStrategy(new StrategyAdd());
	return 0;
}
