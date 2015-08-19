/*
 *	运算符重载 << >> ++ -- 
 * */
#include <iostream>
using namespace std;


class Complex
{
public:
	Complex(int realnum, int virtualnum):realnum(realnum), virtualnum(virtualnum)
	{
		
	}
	Complex()
	{
		this->realnum = 0;
		this->virtualnum = 0;
	}
	Complex(const Complex &com)
	{
		this->realnum = com.realnum;
		this->virtualnum = com.virtualnum;
		std::cout << "copy constructor" << std::endl;
	}
	friend ostream & operator<<(ostream &out, const Complex &com);
	friend istream & operator>>(istream &in, Complex &com);
	Complex operator+(Complex &com02);
	void operator=(Complex &com02);
	//前置++
	Complex operator++();
	//后置++ int占位参数
	Complex operator++(int);
	//前置--
	Complex operator--();
	//后置--
	Complex operator--(int);
private:
	int realnum;//实数
	int virtualnum;//虚数

};

ostream & operator<<(ostream &out, const Complex &com)
{
	out << com.realnum << " + " << com.virtualnum << "i" <<"\n";
	return out;
}

istream & operator>>(istream &in, Complex &com)
{
	std::cin >> com.realnum;
	std::cin >> com.virtualnum;
	return in;
}

Complex Complex::operator+(Complex &com02)
{
	return Complex(this->realnum + com02.realnum, this->virtualnum + com02.virtualnum);
}

void Complex::operator=(Complex &com02)
{	
	std::cout << "assign =" << std::endl;
	this->realnum = com02.realnum;
	this->virtualnum = com02.virtualnum;
}

Complex Complex::operator++()
{
	++this->realnum;
	++this->virtualnum;
	return *this;
}

Complex Complex::operator++(int)
{
	Complex tempComplex;
	tempComplex.realnum = this->realnum++;
	tempComplex.virtualnum = this->virtualnum++;
	return tempComplex;	
}

Complex Complex::operator--()
{
	--this->realnum;
	--this->virtualnum;
	return *this;
}

Complex Complex::operator--(int)
{
	Complex com;
	com.realnum = this->realnum--;
	com.virtualnum = this->virtualnum--;
	return com;
}
class ComplexArray
{
public:
	ComplexArray()
	{
		for (int i = 0; i < 5; i++) {
			mComplexList[i] = new Complex;
		}	
	}
	Complex *mComplexList[5];
	//重载[]
	Complex * operator[](int index);
};

Complex * ComplexArray::operator[](int index)
{
	return this->mComplexList[index];
}

int main()
{
	Complex com(1, 2);
	std::cout << com ;
	
	//std::cin >> com;
	//std::cout << com ;

	Complex com01(2, 3);	
	Complex com02 = com + com01;
	std::cout << com02;
	Complex com03(com02);
	std::cout << com03;
	com = com01;
	std::cout << com;

	//前置++
	++com;
	std::cout << com;
	
	//后置++
	com++;
	std::cout << com;

	//前置--
	--com;
	std::cout << com;
	//后置--
	com--;
	std::cout << com;

	ComplexArray array;
	std::cout << *array[1];

	return 0;
}
