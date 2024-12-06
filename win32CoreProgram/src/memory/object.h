#pragma once

#include <iostream>

using std::cout;
using std::endl;

namespace Object
{
  class People {
  public:
    People() {}
    ~People() {}
  private:
    int _height = 0;
  };

  class Teacher : public People {
  public:
    Teacher() {}
    ~Teacher() {}

    void* operator new(size_t size)
    {
      if (size != sizeof(Teacher))
        return ::operator new(size);
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
      if (size != sizeof(Teacher))
        return ::operator delete(p, size);
      cout << "operator delete..." << endl;
      free(p);
    }

  private:
    int _age = 32;
  };

  void test_inherit_obj()
  {

  }

}

