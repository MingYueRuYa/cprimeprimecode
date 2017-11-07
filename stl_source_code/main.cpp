/*
 * 学习3.0版本的stl source code.
 * */

#include "list"
#include "vector"
#include "algorithm"

#include <iostream>

using std::cout;
using std::endl;

class Object {
public:
	Object(int ID): mID(ID) { 
		cout << "object ctor... id: " << mID << endl; 
	}
	Object(const Object &pObj) { 
		mID = pObj.mID;
		cout << "object copy ctor... id : " << mID << endl; 
	}

	Object& operator=(const Object &pObj) {
		if (this == &pObj) {
			return *this;
		}

		mID = pObj.mID;
		cout << "operator= object... id : " << mID << endl; 
		return *this;
	}

	virtual ~Object() { 
		cout << "~object dtor... id: " << mID << endl; 
	}

	virtual void Show() { 
		cout << std::hex << this << std::dec << " id: " << mID; 
	}

	bool operator==(const Object &pObj)
	{
		if (this->mID != pObj.mID) {
			return false;
		} //if
		return true;
	}

	bool operator<(const Object &pObj)
	{
		if (this->mID < pObj.mID) {
			return true;
		} //if
		return false;
	}

public:
	int mID;
};

void test_vector()
{
//#define TEST_VECTOR_SWAP
//#define TEST_VECTOR_POP_ERASE
//#define TEST_VECTOR_INSERT

	vector<int> vec;
	for (size_t i=0; i<10; ++i) {
		vec.insert(vec.begin(), i);
	}

	//vec.insert(vec.begin()+5, 11);

	vec[0] = 111;

	for (size_t i=0; i<vec.size(); ++i) {
		cout << vec[i] << " ";
	}
	cout << endl;

	vector<int> vec2;
	for (size_t i=0; i<10; ++i) {
		vec2.push_back(i);
	}

	for (size_t i=0; i<vec2.size(); ++i) {
		cout << vec2[i] << " ";
	}
	cout << endl;

#	ifdef TEST_VECTOR_SWAP
	cout << "-----------------behind swap--------------------" << endl;
	vec.swap(vec2);	

	for (size_t i=0; i<vec.size(); ++i) {
		cout << vec[i] << " ";
	}
	cout << endl;

	for (size_t i=0; i<vec2.size(); ++i) {
		cout << vec2[i] << " ";
	}
	cout << endl;
	cout << "-----------------behind swap--------------------" << endl;
#	endif //TEST_VECTOR_SWAP	

#	ifdef TEST_VECTOR_POP_ERASE
	//自定义对象（no-trivial constructor）
	//如果每次capacity扩展时，都会调用copy constructor
	vector<Object> vec3;
	for (int i=0; i<10; ++i) {
		vec3.push_back(Object(i));	
		cout << "----------------- capacity --------------------" << endl;
		cout << "vector capacity: " << vec3.capacity() << endl;
		cout << "----------------- capacity --------------------" << endl;
	}

	cout << "-----------------before pop--------------------" << endl;
	//在pop_back时会调用object的析构函数
	vec3.pop_back();
	cout << "-----------------behind pop--------------------" << endl;

	cout << "-----------------before erase--------------------" << endl;
	//在erase时会调用object的析构函数
	vec3.erase(vec3.begin());
	cout << "-----------------behind erase--------------------" << endl;

	cout << "--------------before erase range------------------" << endl;
	//在erase时会调用object的析构函数
	vec3.erase(vec3.begin());
	cout << "--------------behind erase range------------------" << endl;

	{	//test operator=
			
		cout << "--------------before operator= ------------------" << endl;
		vector<Object> vec3;
		for (int i=0; i<8; ++i) {
			vec3.push_back(Object(i));	
		}
		vector<Object> vec4;
		for (int i=0; i<4; ++i) {
			vec4.push_back(Object(i));	
		}
		vec3 = vec4;
		cout << "--------------behind operator= -----------------" << endl;
	}
#	endif //TEST_VECTOR_POP_ERASE

#		ifdef TEST_VECTOR_INSERT
	{ //test insert_range
		cout << "------------before insert_range ----------------" << endl;
		vector<Object> objvec;
		//插入1-5，此时caption应该为8
		for (int i=0; i<5; i++) {
			cout << "-----objvec capacity " << objvec.capacity() 
			     << "-----" << endl;
			objvec.push_back(Object(i));
		}
		vector<Object> objvec2;
		for (int i=5; i<7; i++) {
			cout << "-----objvec2 capacity " << objvec2.capacity() 
			     << "-----" << endl;
			objvec2.push_back(Object(i));
		}

		cout << "------------- start insert range -------------" << endl;
		objvec.insert(objvec.end()-1, objvec2.begin(), objvec2.end());
		cout << "------------- end  insert  range -------------" << endl;

		for (int i=0; i<7; i++) {
			cout << objvec[i].mID << " ";
		}
		cout << endl;

		cout << "------------behind insert_range ----------------" << endl;
	}
#		endif //TEST_VECTOR_INSERT	
}

namespace test_list
{
void test_list()
{
	list<Object> objlist;
	cout << "-----------------list size--------------------" << endl;
	cout << "list object size:" << sizeof(objlist) << endl;
	cout << "list  size:" << objlist.size() << endl;
	cout << "-----------------list size--------------------" << endl;

	cout << "----------------list insert-------------------" << endl;
	for (int i=0; i<10; ++i) {
		objlist.insert(objlist.begin(), Object(i));
	}
	cout << "----------------list insert-------------------" << endl;

	cout << "----------------list erase-------------------" << endl;
	cout << "----------------erase position" << endl;
	list<Object>::iterator ibeg = objlist.erase(objlist.begin());
	for (; ibeg != objlist.end(); ++ibeg) {
		cout << ibeg->mID << " ";
	}
	cout << "----------------erase position" << endl;

	cout << "----------------erase first last" << endl;
	list<Object>::iterator lastitr = objlist.begin();
	// 步进迭代器5个
	advance(lastitr, 5);
	int step = 0;
	distance(objlist.begin(), lastitr, step);
	cout << "distance:" << step << endl;
	list<Object>::iterator startitr = objlist.erase(objlist.begin(), lastitr);
	
	for (; startitr != objlist.end(); ++startitr) {
		cout << startitr->mID << " ";
	}
	cout << "----------------erase first last" << endl;
	cout << "----------------list erase-------------------" << endl;


	cout << "----------------list unique-------------------" << endl;
	
	objlist.push_back(Object(6));
	objlist.push_back(Object(6));
	objlist.push_back(Object(6));
	objlist.insert(objlist.begin(), Object(6));

	objlist.unique();

	startitr = objlist.begin();
	for (; startitr != objlist.end(); ++startitr) {
		cout << startitr->mID << " ";
	}

	cout << "----------------list unique-------------------" << endl;


	cout << "----------------list merge-------------------" << endl;
	list<Object> merge1list;
	merge1list.push_back(Object(5));
	merge1list.push_back(Object(3));
	merge1list.push_back(Object(4));
	list<Object> merge2list;
	merge2list.push_back(Object(2));
	merge2list.push_back(Object(3));
	merge2list.push_back(Object(4));
	merge2list.push_back(Object(6));
	merge1list.merge(merge2list);

	startitr = merge1list.begin();
	for (; startitr != merge1list.end(); ++startitr) {
		cout << startitr->mID << " ";
	}
	cout << endl;
	merge1list.clear();	
	cout << "----------------list merge-------------------" << endl;

	cout << "----------------list splice------------------" << endl;
	merge1list.push_back(Object(5));
	merge1list.push_back(Object(3));
	merge1list.push_back(Object(4));

	merge2list.push_back(Object(2));
	merge2list.push_back(Object(3));
	merge2list.push_back(Object(4));
	merge2list.push_back(Object(6));

	startitr = merge1list.begin();
	advance(startitr, 1);
	// list参数其实没有用到，可能就是为了表示迭代器可以指向本身
	merge1list.splice(merge1list.begin(), merge1list, startitr); 
	startitr = merge1list.begin();
	for (; startitr != merge1list.end(); ++startitr) {
		cout << startitr->mID << " ";
	}
	cout << endl;

	merge1list.splice(merge1list.begin(), merge1list, 
						merge2list.begin(),
						merge2list.end()); 
	startitr = merge1list.begin();
	for (; startitr != merge1list.end(); ++startitr) {
		cout << startitr->mID << " ";
	}
	cout << endl;
	
	cout << "----------------list splice------------------" << endl; 

}
};


int main(int argc, char *argv[])
{
	//test_vector();

	test_list::test_list();	

	return 0;
}
