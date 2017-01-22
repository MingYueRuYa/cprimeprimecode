
#include "context.h"

Context::Context()
{
}

Context::~Context()
{
}

void Context::CreateStrategy(Strategy *pStrategy)
{
	//pStrategy.AlgorithmInterface();
	pStrategy->AlgorithmInterface();
}
