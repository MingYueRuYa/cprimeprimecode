/*
 * 抽象算法类
 * */

#ifndef strategy_h

#define strategy_h

class Strategy
{
public:
	Strategy();

	virtual ~Strategy();

	virtual void AlgorithmInterface() = 0;

};

#endif //strategy_h
