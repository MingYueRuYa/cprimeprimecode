/*
 * traits template
 * */
#include <iostream>

template<typename T> class TraitsTemplate{
};

//template specialize
template<>
class TraitsTemplate<char>{
public:	
	typedef int ReturnType;
};

template<>
class TraitsTemplate<short>{
public:	
	typedef int ReturnType;
};

template<>
class TraitsTemplate<int>{
public:	
	typedef long ReturnType;
};

template<>
class TraitsTemplate<unsigned int>{
public:	
	typedef unsigned long ReturnType;
};

template<>
class TraitsTemplate<float>{
public:	
	typedef double ReturnType;
};

template<typename T> 
typename TraitsTemplate<T>::ReturnType SigmaTraits(const T *pStart, const T *pEnd)
{
	typedef typename TraitsTemplate<T>::ReturnType ReturnType;
	ReturnType retvalue = ReturnType(); //init retvalue is zero.
	while (pStart != pEnd) {
		retvalue += *pStart++;
	}
	return retvalue;
}

int main()
{
	char *arr= "abc";
	int retvalue = SigmaTraits(arr, arr+3);
	std::cout << retvalue << std::endl;
	return 0;
}
