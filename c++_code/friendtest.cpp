#include <iostream>


class A
{
public:
	friend void Print(A *a);
private:
	int a;
	int b;
};

void Print(A *a)
{
	std::cout << a->a << "  " << a->b;
}

int main()
{
	A a;
	Print(&a);
	return 0;
}
