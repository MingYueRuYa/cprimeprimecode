/**
 *高级数据 + lambda表达式
 */
#include <iostream>
#include <vector>
#include <algorithm>  //算法 加入头文件 lambda表达式

int main()
{
	//动态无规则数组管理	
	std::vector<int> myvector01 ={1, 2, 3};
	std::vector<int> myvector02 ={4, 5, 6};
	std::vector<int> myvector03 ={7, 8, 9, 10, 11};
	std::vector<std::vector<int>>	myvecvec = {myvector01, myvector02, myvector03};
	for(int i = 0; i < myvecvec.size(); i++) {
		for(int j = 0; j < myvecvec[i].size(); j++) {
			std::cout << myvecvec[i][j] << " ";	
		}
		std::cout << "\n";
	}
	return 0;
}

int main02()
{
	std::vector<int> myvector(5); //分配5个空间，默认为0
	myvector.push_back(1); //在尾部插入
	myvector.push_back(2); //在尾部插入
	myvector.push_back(3); //在尾部插入
	myvector.pop_back(); //弹出一个元素
	myvector.insert(myvector.begin() + 1, 999);
	myvector.erase(myvector.begin() + 7);
	for(int i = 0; i < myvector.size(); i++) {
		std::cout << myvector.at(i) << std::endl;
	}
	return 0;
}



int main01()
{
	std::vector<int> myvector;
	myvector.push_back(11);
	myvector.push_back(22);
	myvector.push_back(33);
	int res = 0; //结果
	//lambda []表示要外部传进去的参数,()表示内部参数,{}操作逻辑，代码
	std::for_each(myvector.begin(), myvector.end(), [&res](int num){res += num;});
	std::cout << res << std::endl;
	return 0;
}


