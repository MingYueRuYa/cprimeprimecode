#ifndef context_h

#define context_h

#include "strategy.h"

class Context
{
public:
	Context();

	~Context();

	void CreateStrategy(Strategy *pStrategy);
};


#endif //context_h
