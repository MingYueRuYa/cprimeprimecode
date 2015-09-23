/*
 *	友元关键字
 *	友元函数，友元类
 * */
#include <iostream>

class friendclass
{
	public:
		friendclass(int num = 20)
		{
			this->num = num;
		}
	private:
		int num;
		friend void  printnum(friendclass *fc); //友元函数
		void privatefunc()
		{
			std::cout << "this is friendclass privatefunc" << std::endl;
		}
		friend class friendclassA;
};

void printnum(friendclass *fc)
{
	std::cout << fc->num << std::endl;
	fc->privatefunc();
}

/*	测试在结构体中是否有这种特性
 *	经过测试发现结构体同样适用
 * */
struct friendstrcut{
	private:
		int age = 10;
		char name[10];
		friend void  friendfun(friendstrcut *fs);
		void printstrnum();

		//测试结构体friend class 同样是可以适用的
		friend class friendclassA;
};

//结构体就是类的原型
void friendstrcut::printstrnum()
{
	std::cout << "this is struct func." << std::endl;
}


//结构体中的友元函数,访问私有成员
void friendfun(friendstrcut *fs)
{
	std::cout << fs->age << std::endl;
	fs->printstrnum();
}

//友元类
class friendclassA
{
public:
	friendclassA(friendclass &fc)
	{
		num = fc.num;
	}

	friendclassA(friendstrcut &fs)
	{
		num = fs.age;
	}
	int num = 0;
};

int main()
{
	friendclass fc(5);
	printnum(&fc);

	friendstrcut fs;
	friendfun(&fs);
	
	friendclassA fca(fc);
	std::cout << fca.num << std::endl;
	
	friendclassA fca01(fs);
	std::cout << fca01.num << std::endl;
	return 0;
}
