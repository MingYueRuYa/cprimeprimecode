// test_dll.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include "../hello_dll/hello.h"
#include "../testdll2/hello2.h"

#pragma comment(lib, "hello_dll")
#pragma comment(lib, "testdll2")

//extern int add(int a, int b);

//extern void hello();
//extern void world();

int main()
{
  std::cout << "Hello World!\n";
  std::cout << add(1, 2) << std::endl;
  hello();
  std::thread thr([]() {
    std::cout << "create new thread" << std::endl;
    });
  hello2();
  thr.join();
  getchar();
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
