//模板函数的重载
#include <iostream>
#include <array>
using std::array;

template<typename T>
void showarray(array<T,10> myarray, int n)
{
	using namespace std;	
	cout << "TTT" << endl;
	for (int i = 0; i<n; i++) {
		cout << myarray[i] << " ";
	}
	cout<< endl;
}

template<typename T>
void showarray(array<T *,10> myarray, int n)
{
	using namespace std;	
	cout << "T*T*T*" <<endl;
	for(int i = 0; i < n; i++) {
		cout << *myarray[i] << " ";
	}
	cout << endl;
}



int main(int argc, char *argv[])
{
	array<int, 10> intarray = {1,2,3,4,5,6,7,8,9,10};
	array<int *, 10> pintarray;
	for(int i = 0; i < 10; i++) {
		pintarray[i] = &intarray[i];
	}
	array<int **, 10> ppintarray;
	for(int i = 0; i < 10; i++) {
		ppintarray[i] = &pintarray[i];
	}
	showarray(intarray, 10);
	showarray(pintarray, 10);
	showarray(ppintarray, 10);
	return 0;
}
