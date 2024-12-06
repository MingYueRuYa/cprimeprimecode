// memory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using std::cout;
using std::endl;

class Student {
public:
  Student() {
    cout << "ctor" << endl;
  }

  Student(int age) :_age(age) {
    cout << "ctor age:" << age << endl;
  }
  ~Student() {
    cout << "~dtor" << endl;
  }

  void* operator new(size_t size)
  {
    cout << "operator new..." << endl;
    return malloc(size);
  }

  void* operator new(size_t size, void* start)
  {
    cout << "operator new..." << endl;
    return start;
  }

  void operator delete(void* p, size_t size)
  {
    cout << "operator delete..." << endl;
    free(p);
  }

private:
  int _age = 0;

};


//void* operator new(size_t size)
//{
//  cout << "global op new" << endl;
//  return malloc(size);
//}
//
//void operator delete(void* p, size_t)
//{
//  cout << "global op delete" << endl;
//  return free(p);
//}

class Car
{
public:
  Car() { cout << "car ctor" << endl; }
  ~Car() { cout << "car ~dctor" << endl; }
};


#include <cstddef>
#include <iostream>
namespace jj04
{
  //ref. C++Primer 3/e, p.765
  //per-class allocator 

  class Screen {
  public:
    Screen(int x) : i(x) { };
    ~Screen() { cout << "~dctor screen" << endl; };
    int get() { return i; }

    void* operator new(size_t);
    void  operator delete(void*, size_t);	//(2)
//! void  operator delete(void*);			//(1) 二擇一. 若(1)(2)並存,會有很奇怪的報錯 (摸不著頭緒) 

  private:
    Screen* next;
    static Screen* freeStore;
    static const int screenChunk;
  private:
    int i;
  };
  Screen* Screen::freeStore = 0;
  const int Screen::screenChunk = 24;

  void* Screen::operator new(size_t size)
  {
    Screen* p;
    if (!freeStore) {
      //linked list 是空的，所以攫取一大塊 memory
      //以下呼叫的是 global operator new
      size_t chunk = screenChunk * size;
      freeStore = p =
        reinterpret_cast<Screen*>(new char[chunk]);
      //將分配得來的一大塊 memory 當做 linked list 般小塊小塊串接起來
      for (; p != &freeStore[screenChunk - 1]; ++p)
        p->next = p + 1;
      p->next = 0;
    }
    p = freeStore;
    freeStore = freeStore->next;
    return p;
  }


  //! void Screen::operator delete(void *p)		//(1)
  void Screen::operator delete(void* p, size_t)	//(2)二擇一 
  {
    //將 deleted object 收回插入 free list 前端

    static_cast<Screen*>(p)->~Screen();
    (static_cast<Screen*>(p))->next = freeStore;
    freeStore = static_cast<Screen*>(p);
  }

  //-------------
  void test_per_class_allocator_1()
  {
    cout << "\ntest_per_class_allocator_1().......... \n";

    cout << sizeof(Screen) << endl;		//8	

    size_t const N = 100;
    Screen* p[N];

    for (int i = 0; i < N; ++i)
      p[i] = new Screen(i);

    //輸出前 10 個 pointers, 用以比較其間隔 
    for (int i = 0; i < 10; ++i)
      cout << p[i] << endl;

    for (int i = 0; i < N; ++i)
      delete p[i];
  }
} //namespace


int main()
{
  jj04::test_per_class_allocator_1();
  //Student* stu = new Student();

  //// stu = new (stu)Student(1);

  //Student* st1 = (Student*)malloc(sizeof(Student));
  //new(st1)Student(1);

  //delete stu;

  //Car* car = new Car();
  //delete car;

  //std::string* str = new std::string("hello world");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
