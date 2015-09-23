/*
 *	关于复杂对象指针数组和数组指针
 * */
class MyClass
{
public:
	int num;
	char name[10];
};


int main()
{
	//指针数组
	MyClass *parr = new MyClass[5];
		
	//二级指针
	MyClass **pparr = new MyClass*[5]; //数组的每个元素都是一个指向MyClass的指针

	//二维数组,数组每个元素都是MyClass
	MyClass p2arr[5][5];
	//指向数组的指针
	MyClass (*pp2arr)[5] = p2arr;
	//强制转换将二级指针转换为指向数组指针
	pp2arr = (MyClass (*)[5])pparr;

	//二位数主，每个数组的元素都是一个MyClass指针
	MyClass *p_p2arr[5][5]; 
	//声明指向数组的指针
	MyClass *(*p_pp2arr)[5] = p_p2arr;
	MyClass ***p_pparr = (MyClass ***)p_p2arr;
	return 0;
}
