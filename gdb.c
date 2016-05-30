
#include <stdio.h>
#include <stdlib.h>

extern char ** environ;

class SampleParentClass {
public :
 virtual void PrintMe ( ) {
	p r intf("I am parent class.\n");
	}
	virtual void PrintMe ( const char *s ) {
	printf( " I am parent c l a s s . \ n%s \n" , s );
	}
	class SampleParentClass * next ;
	const char *name ;
};

class SampleChildClass : public SampleParentClass {
	virtual void PrintMe ( ) {
	printf( " I am c h i l d c l a s s . \nMy name i s %s \n" , name );
	} 
	virtual void PrintMe ( const char ∗ s ) {
	printf( " I am child class.\nMy name i s %s \n%s \n" , name , s );
	}
};

int foo ( int a , int b)
{
	int r = 0;
	printf( "a is %d , b is %d\n" , a , b ) ;
	r = a + b;
	return r;
}

int foo ( int a )
{
	printf( "a i s %d\n" ) ;
	return a + 1;
}

int main ( int argc , char ∗∗ argv )
{
	int a = 1;
	int b = 3;
	int i = 0;
	char *p;
	printf( " Hello GDB\n" ) ;
	printf("−−−−−−−−−−−−−command l i n e arguments−−−−−\n" ) ;
	for ( i = 0 , p = argv [ i ] ; p ! = NULL ; p = argv[++ i ] ) {
		printf("%d : \ t%s \n" , i , p ) ; // breakpoint
	}
	printf ("−−−−−−−−−−−−−enviroment−−−−−−−−−−−−−−−−−−\n" ) ;
	for ( i = 0 , p = environ [ i ] ; p ! = NULL ; p = environ[++ i ] ) {
		printf("%d : \ t%s \n" , i , p ) ;
	}
	// test overload function
	foo ( a , b ) ;
	foo ( a ) ;
	// testclass
	SampleParentClass ∗ obj ;
	obj = new SampleChildClass ( ) ;
	obj−>name = "head" ;
	obj−>next = new SampleChildClass ( ) ;
	obj−>next−>name = " Charles " ;
	obj−>next−>next = new SampleChildClass ( ) ;
	obj−>next−>next−>name = "Smith " ;
	obj−>next−>next−>next = new SampleChildClass ( ) ;
	obj−>next−>next−>next−>name = " t a i l " ;
	obj−>next−>next−>next−>next = NULL;
	SampleParentClass *obj2 ;
	for ( obj2 = obj ; obj2 ! = NULL ; obj2 = obj2−>next ) {
	obj2−>PrintMe ( ) ; // breakpoint
	obj2−>PrintMe ( " I wanna say something . \ n" ) ;
	}
	delete obj ;
	return 0 ;
}