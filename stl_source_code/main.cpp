/*
 * 学习3.0版本的stl source code.
 * */

#include <iostream>
#include "vector"
#include "list"

using std::cout;
using std::endl;

class Object {
public:
	Object(int ID): mID(ID) { cout << "object ctor... id: " << mID << endl; }
	Object(const Object &pObj) { 
		mID = pObj.mID;
		cout << "object copy ctor... id : " << mID << endl; 
	}

	Object& operator=(const Object &pObj) {
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
	list<Object *> objlist;
	objlist.push_back(new Object(0));
}
};


int main(int argc, char *argv[])
{
	//test_vector();

	test_list::test_list();	

	return 0;
}
