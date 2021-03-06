/*
 *set 内部的元素依据其值自动排序，相同的元素数值元素只能出现一次
 *multiset 内部的元素依据其值自动排序，相同的元素数值元素只能出现多次
 *其内部都是用二叉树实现的
 *基本操作
 *	insert count find erase
 *	insert操作会币vector慢一点
 *注意：
 * 不能通过find进行修改，因为set和multiset是自动排序的，如果修改了，就不是自动排序了
 * 要想修改的话，只能先删除了在插入操作
 **/

#include <iostream>
#include <string.h>
#include <algorithm>
#include <hash_set>
#include <set>
using namespace std;
struct strless
{
	bool operator()(const char *str1, const char *str2)
	{
		return strcmp(str1, str2) < 0;
	}
};


template <typename T>
void PrintContents(const T &pContainer)
{
	typename T::const_iterator begin =  pContainer.begin();
	for (; begin != pContainer.end(); ++begin) {
		cout << *begin << endl;
	}
}

int main(void)
{
	set<int> myset;
	myset.insert(1);
	myset.insert(1);
	myset.insert(2);
	myset.insert(3);
	PrintContents(myset);
	cout << endl;
	//始终都是一个
	cout << "1 count = " << myset.count(1) << endl;
	multiset<int> mymulset;
	mymulset.insert(1);
	mymulset.insert(1);
	mymulset.insert(1);
	mymulset.insert(2);
	mymulset.insert(3);
	PrintContents(mymulset);
	mymulset.erase(1);
	cout << "1 count = " << mymulset.count(1) << endl;
	cout << endl;
	PrintContents(mymulset);
	mymulset.clear();
	cout << endl;
	PrintContents(mymulset);
	return 0;
}

//set 
int main_set()
{
	const char *cmd[] = {"linux", "unix", "windows", "freeBSD"};
	set<const char *, strless> myset(cmd, cmd + 4, strless());
	myset.insert("1234");
	myset.insert("4567");


	//pair起到获取插入返回值，第一个是类型，第二个类型比大小的方式
	pair<set<const char *>::iterator, bool> setpair = myset.insert("0123");
	cout << *(setpair.first) << " " << setpair.second << "\n";
	set<const char *, strless>::iterator ibeg = myset.begin();
	set<const char *, strless>::iterator iend = myset.end();
	for (; ibeg != iend; ibeg++) {
		cout << *ibeg << "\n";
	}


	//find algorithm
	cout << "\n";
	set<const char *, strless>::iterator pfind = myset.find("solaris");
	if (pfind != myset.end()) {
		cout << *pfind << "\n";
	} else {
		cout << "Not find info.\n";
	}
	return 0;
}

//multiset 每一个节点都是一个链表，而set每个节点就是一个节点
struct student
{
	int id;
	char name[20];
};
//排序
struct stuless
{
	bool operator() (const student &s1,const student &s2)
	{
		return s1.id < s2.id;	
	}
};
void Print(const student &stu)
{
	cout << stu.id << " " << stu.name << "\n";
}
int main_multiset()
{
	student stuarr[3] = { {1, "windows"}, {2, "linux"}, {3, "unix"} };
	multiset<student, stuless> mymulset(stuarr, stuarr + 3, stuless());
	student stu1;
	stu1.id = 4;
	strcpy(stu1.name, "freeBSD");
	mymulset.insert(stu1);
	strcpy(stu1.name, "solaris");
	mymulset.insert(stu1);
	strcpy(stu1.name, "aixs");
	mymulset.insert(stu1);
	for_each(mymulset.begin(), mymulset.end(), Print);
	return 0;	
}

//hash_set 哈希是一种高效的检索方法，本身并不用排序,算法复杂度O(1)
//在g++编译不能通过，原因是hash_set已经过时，具体的还没有调查
int main_hash_set()
{
	const char *cmd[] = {"abc", "calc", "notepad", "const"};		
	//hash_set<const char *>hs;
	/*
	hs.insert("China");
	hs.insert("US");
	hs.insert("Germany");
	hs.insert("Japan");
	hash_set<const char *>::iterator pfind = hs.find("xxx");
	if (pfind != hs.end()) {
		cout << *pfind << "\n";
	} else {
		cout << "Not find info.\n";
	}
	*/
	return 0;
}

int main01()
{
	multiset<int> myset;
	myset.insert(100);
	myset.insert(101);
	myset.insert(101);
	myset.insert(102);
	myset.insert(103);
	auto pfind = myset.find(101);
	//默认只找到第一个
	cout << *pfind << endl;
	auto allfind = myset.equal_range(101);
	//find链表的头结点，second最后一个空节点，遍历所有的元素
	for (auto it = allfind.first; it != allfind.second; it++) {
		cout << *it << endl;
	}
	return 0;
}
