/*
 * 学习3.0版本的stl source code.
 * 使用stl时一定要注意C++ big three函数
 * */

#include "list"
#include "vector"
#include "deque"
#include "stack"
#include "queue"
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
	merge2list.push_back(Object(9));
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

namespace test_deque
{
void test_deque()
{
	cout << "--------------deque push_front----------------" << endl; 
	typedef deque<Object, alloc, 3> __deque;
	__deque objdeq;
	for (int i=0; i<5; ++i) {
		objdeq.push_front(Object(i));
	}
	__deque::iterator ibeg = objdeq.begin();
	for (; ibeg != objdeq.end(); ++ibeg) {
		cout << ibeg->mID << " " << objdeq.size() << " ";
	}
	cout << endl;
	cout << "--------------deque push_front----------------" << endl; 

	cout << "--------------deque push_back----------------" << endl; 
	__deque objdeq1;
	for (int i=0; i<5; ++i) {
		objdeq1.push_back(Object(i));
	}
	ibeg = objdeq1.begin();
	for (; ibeg != objdeq1.end(); ++ibeg) {
		cout << ibeg->mID << " ";
	}
	cout << endl;
	cout << "--------------deque push_back----------------" << endl; 

	cout << "--------------deque erase----------------" << endl; 
	cout << "size: " << objdeq1.size() << endl;
	__deque::iterator ipos = objdeq1.begin();
	advance(ipos, 3);
	cout << "object id: " << ipos->mID << endl;
	objdeq1.erase(ipos);

	ibeg = objdeq1.begin();
	for (; ibeg != objdeq1.end(); ++ibeg) {
		cout << ibeg->mID << " ";
	}
	cout << "--------------deque erase----------------" << endl; 

	cout << "---------deque<int, alloc, 3>------------" << endl; 
	typedef deque<int, alloc, 3> _int_deque;
	_int_deque deque_int_1;
	for (int i=0; i<10; ++i) {
		deque_int_1.push_back(i);
	}
	cout << "---------deque<int, alloc, 3>------------" << endl; 
}

}; // test_deque

namespace test_stack
{

void test_stack()
{
	cout << "---------------stack----------------" << endl; 
	stack<int> int_stack;		
	for (int i=0; i<10; ++i) {
		int_stack.push(i);
	}
	
	while (! int_stack.empty()) {
		cout << int_stack.top() << " ";
		int_stack.pop();
	}
	cout << endl;
	cout << "---------------stack----------------" << endl; 
	//result:
		//---------------stack----------------
		//9 8 7 6 5 4 3 2 1 0 
		//---------------stack----------------
}

}; // test_stack

namespace test_queue
{

void test_queue()
{
	cout << "---------------queue----------------" << endl; 
	queue<int> int_queue;		
	for (int i=0; i<10; ++i) {
		int_queue.push(i);
	}

	cout << "-------------queue fornt------------" << endl; 
	while (! int_queue.empty()) {
		cout << int_queue.front() << " ";
		int_queue.pop();
	}
	cout << endl;

	cout << "-------------queue back------------" << endl; 
	for (int i=0; i<10; ++i) {
		int_queue.push(i);
	}
	while (! int_queue.empty()) {
		cout << int_queue.back() << " ";
		int_queue.pop();
	}
	cout << endl;
	cout << "---------------queue----------------" << endl; 
	//result:
		//---------------queue----------------
		//-------------queue fornt------------
		//0 1 2 3 4 5 6 7 8 9 
		//-------------queue back------------
		//9 9 9 9 9 9 9 9 9 9 
		//---------------queue----------------
}

}; // test_queue

namespace test_priority_queue
{

void test_priority_queue()
{
	cout << "---------------priority_queue----------------" << endl; 
	srand(time(NULL));
	priority_queue<int> int_priority_queue;		
	// 会进行堆排序从小到大
	for (int i=0; i<10; ++i) {
		int_priority_queue.push(rand()%100);
	}

	cout << "-------------priority_queue fornt------------" << endl; 
	while (! int_priority_queue.empty()) {
		cout << int_priority_queue.top() << " ";
		int_priority_queue.pop();
	}
	cout << endl;
	//result:
		//---------------priority_queue----------------
		//-------------priority_queue back------------
		//96 94 76 72 46 42 28 26 24 10 
		//---------------priority_queue----------------
}
};

namespace test_reverse_iterator
{
void test_reverse_iterator()
{
	vector<int> vec;
	for (int i : {1,3,5,2,7,4} ) {
		vec.push_back(i);
	}

	vector<int>::_reverse_iterator ibeg = vec.rbegin();
	cout << "-------------reverse iterator-------------" << endl;
	for (; ibeg != vec.rend(); ++ibeg) {
		cout << *ibeg << " ";
	}		
	// 4 7 3 5 3 1
	cout << "\n-------------reverse iterator-------------" << endl;

	cout << "-------------forward iterator-------------" << endl;
	for (auto itr : vec) {
		cout << itr << " ";
	}
	// 1 3 5 2 7 4
	cout << "\n-------------forward iterator-------------" << endl;
}
};

// using namespace std::placeholders;

#include <functional>
#include <algorithm>

namespace test_bind
{
double my_divide(double x, double y)
{
	return x / y;
}

struct MyPair {
	double a;
	double b;
	double mulitiply() { return a*b; }
};

void test_bind()
{
	cout << "--------------test_bind--------------" << endl;
	int ia[7] = {27, 210, 12, 47, 109, 83, 40};
	vector<int> vi(ia, ia+7);
	cout << std::count_if(vi.begin(), vi.end(), std::bind1st(less<int>(), 40))
		 << endl; // 4
	cout << "--------------test_bind--------------" << endl;
}
};


int main(int argc, char *argv[])
{
	//test_vector();

	//test_list::test_list();	

	//test_deque::test_deque();

	//test_stack::test_stack();

	//test_queue::test_queue();
	
	//test_priority_queue::test_priority_queue();

	//test_reverse_iterator::test_reverse_iterator();

	test_bind::test_bind();

	return 0;
}
