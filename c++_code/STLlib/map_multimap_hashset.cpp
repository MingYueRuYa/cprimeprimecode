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

int main()
{
	//hash_map 在g++中提示已经过时废弃
	return 0;
}
