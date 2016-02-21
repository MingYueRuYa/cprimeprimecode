/*
 * map 映射, 每个节点都是一个节点
 * multimap，每个节点都是一个链表结构，所以multimap一对多的映射 
 * */
#include <iostream>
#include <map>
#include <hash_map>

using namespace std;

struct student
{
	char *name;	
	int year;
};
struct stuinfo
{
	int id;
	student stu;
};
int main_map()
{
	map<const char *, int> mymap;
	mymap["unix"] = 1;
	mymap["linux"] = 2;
	mymap["freeBSD"] = 3;
	mymap["windows"] = 4;
	mymap.insert(pair<const char *, int>("orangeos", 5));
	mymap.insert(pair<const char *, int>("windows", 1));
	mymap.insert(multimap<const char *, int>::value_type("freeBSD", 6));
	mymap.insert(make_pair("solaris", 7));
	cout << mymap["unix"] << endl;
	cout << mymap["linux"] << endl;
	cout << mymap["orangeos"] << endl;

	//stuinfo stuinfo01 = {10, {"solaris", 20}};
	stuinfo stuinfoarr[] = {{1, {"linux", 30}}, {2, {"unix", 50}}, {3, "freeBSD", 15} };
	map<int, student> mapstudent;
	for (int i = 0; i < 3; i++) {
		mapstudent[stuinfoarr[i].id] = stuinfoarr[i].stu;
	}
	stuinfo stuinfo01 = {10, {"solaris", 20}};
	mapstudent[30] = stuinfo01.stu;
	map<int, student>::iterator beg = mapstudent.begin();
	map<int, student>::iterator end = mapstudent.end();
	for (; beg != end; beg++) {
		//cout << (*beg).first << "\n";
		cout << (*beg).second.name << (*beg).second.year << "\n";
	}
	return 0;
}

int main_multimap()
{
	multimap<const char *, int> mymap;
	mymap.insert(pair<const char *, int>("Yunos", 4));
	mymap.insert(pair<const char *, int>("Yunos", 4));
	mymap.insert(pair<const char *, int>("orangeos", 5));
	map<const char *, int>::iterator beg = mymap.begin();
	map<const char *, int>::iterator end = mymap.end();
	for (; beg != end; beg++) {
		cout << (*beg).first << " " << (*beg).second << endl;
	}
	return 0;
}

int main_hashmap()
{
	//hash_map 在g++中提示已经过时废弃
	return 0;
}

int main()
{
	multimap<const char *, int>mymap;
	mymap.insert(pair<const char *, int>("linux", 4));
	mymap.insert(pair<const char *, int>("linux", 4));
	mymap.insert(pair<const char *, int>("linux", 4));
	mymap.insert(pair<const char *, int>("unix", 5));
	mymap.insert(pair<const char *, int>("windows", 1));
	mymap.insert(multimap<const char *, int>::value_type("freeBSD", 6));
	mymap.insert(make_pair("solaris", 7));
	cout << mymap.size() << endl;
	cout << "liunx count = " << mymap.count("linux") << endl;

	multimap<const char *, int>::iterator pfind = mymap.find("linux");
	//cout << (*pfind).first << " " << pfind->second << endl;
	//从第一个迭代器位置删除到最后一个迭代器位置
	mymap.erase(mymap.lower_bound("linux"), mymap.upper_bound("linux"));
	mymap.erase("linux");
	if (mymap.find("linux") != mymap.end()) {
		mymap.erase(mymap.find("linux"));
	}
	auto it = mymap.equal_range("linux");
	for (auto i = it.first; i != it.second; i++) {
		cout << (*i).first << " " << i->second << endl;
	}
	return 0;
}
