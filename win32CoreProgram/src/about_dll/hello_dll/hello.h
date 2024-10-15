#pragma once

//#ifdef HELLODLL_EXPORTS
//#define PORT __declspec(dllexport)
//#else
//#define PORT __declspec(dllimport)
//#endif

//#ifdef __cplusplus
//extern "C"
//{
//#endif

//PORT int add(int a, int b);
//
//PORT void hello();
int add(int a, int b);

void hello();
void world();


//#ifdef __cplusplus
//}
//#endif

