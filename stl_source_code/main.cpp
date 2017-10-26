/*
 * 学习3.0版本的stl source code.
 * */

#include <iostream>
#include "vector"

using std::cout;
using std::endl;

class Object {
public:
	Object(int ID): mID(ID) { cout << "object ctor... id: " << mID << endl; }
	Object(const Object &pObj) { 
		mID = pObj.mID;
		cout << "object copy ctor... id : " << mID << endl; 
	}
	virtual ~Object() { cout << "~object dtor... id: " << mID << endl; }

	virtual void Show() { 
		cout << std::hex << this << std::dec << " id: " << mID; 
	}

private:
	int mID;
};

void test_vector()
{
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

	
}

int main(int argc, char *argv[])
{
	test_vector();

	return 0;
}
