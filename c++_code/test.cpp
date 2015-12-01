#include <iostream>
class Base
{
public:
	virtual void showname() = 0;
};

class Father: public Base
{
public:
	virtual void showhi() {
		//TODO: todo nothing.
	}
	void showname() {
		std::cout << "father." << std::endl;
	}
};
int main() 
{
	Father father;
	return 0;
}
