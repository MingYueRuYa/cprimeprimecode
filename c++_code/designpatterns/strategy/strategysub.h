#ifndef strategysub_h
#define strategysub_h

#include "strategy.h"

class StrategySub:public Strategy
{
public:
	StrategySub();

	~StrategySub();

	void AlgorithmInterface();
};

#endif //strategysub_h
