#include <iostream>

class Father
{
public:
	int num;
	void PrintName() {
		std::cout << "this is father." << " num = " << num <<std::endl;
	}
};

class Son : public Father
{
public:
	int num;
	void PrintName() {
		std::cout << "this is father." << " num = " << num <<std::endl;
	}

};


int main()
{
	//指针没有初始化，就使用，这是危险的事
	Father *father;
	Son *son = reinterpret_cast<Son *> (father);
	son->PrintName();
	return 0;
}
int main03(int argc, char *argv[])
{
	//指针类型转换
	int num = 5;
	char *p = reinterpret_cast<char *>(&num);
	for(int i = 0; i < 4; i++) {
		std::cout << static_cast<int>(*(p + i)) << " ";
	}
	std::cout <<"\n";
	return 0;
}

int main02(int argc, char *argv[])
{
	const int num = 10;
	int numarr[3] = {1,2,3};
	const int *p = numarr;
	std::cout << *p << " " << *(p+1) << " "<< *(p+2) <<std::endl;
	//*p = 10;
	//*(p+1) = 10; //报错，p为const类指针
	int *pnew = const_cast<int *>(p);
	*pnew = 10;
	*(pnew+1) = 11;
	*(pnew+2) = 12;
	//去掉指针的const属性是成功的，但是对变量来说是不行的
	//const变量是放在符号表中的，在编译的时候就确定了值，虽然在内存中修改
	//变量的值，但是在运行的时候不是在内存中拿得，而是在寄存器取得
	for(int i=0 ; i<3; i++)	{
		std::cout <<numarr[i] << std::endl;
	}


	//static_cast<type>相当与c语言的中强制类转换
	//std::cout << static_cast<int>(100.0) << std::endl;
	//去掉const属性	
	//int num01 = const_cast<int>	(num) ; //报错
	return 0;
}

int main01(int argc, char *argv[])
{
	//static_cast<type>相当与c语言的中强制类转换
	std::cout << static_cast<int>(100.0) << std::endl;
	
	return 0;
}
