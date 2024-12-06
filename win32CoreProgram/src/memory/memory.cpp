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

  static void* operator new(size_t size)
  {
    cout << "operator new..." << endl;
    return malloc(size);
  }

  static void* operator new(size_t size, void* start)
  {
    cout << "operator new..." << endl;
    return start;
  }

  static void operator delete(void* p, size_t size)
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


int main()
{
  Student* stu = new Student();

  // stu = new (stu)Student(1);

  Student* st1 = (Student*)malloc(sizeof(Student));
  new(st1)Student(1);

  delete stu;

  Car* car = new Car();
  delete car;

  std::string* str = new std::string("hello world");
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
