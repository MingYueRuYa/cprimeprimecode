/*
 * 简单工厂的实现
 * */
#include <iostream>
class Operation
{
public:
	int num1, num2;
	virtual int getResult() = 0;
};

class AddOperatoin : public Operation
{
	int getResult()
	{
		return num1 + num2;
	}
};

class SubOperatoin : public Operation
{
	int getResult()
	{
		return num1 - num2;
	}
};

class DivOperatoin : public Operation
{
	int getResult()
	{
		return num1 / num2;
	}
};

class MulOperatoin : public Operation
{
	int getResult()
	{
		return num1 * num2;
	}
};


class Factory
{
public:
	static Operation *createOperation(char c)
	{
		switch(c)
		{
			case '+':
				return new AddOperatoin();
				break;
			case '-':
				return new SubOperatoin();
				break;
			case '*':
				return new MulOperatoin();
				break;
			case '/':
				return new DivOperatoin();
				break;
			default:
				break;
		}
	}
};

int main(int argc, char ** argv)
{
	Operation *operation = Factory::createOperation('-');	
	operation->num1 = 9;
	operation->num2 = 19;
	std::cout << operation->getResult() << std::endl;
	return 0;
}



