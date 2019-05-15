#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <iostream>

//指针、引用的基本用法
void compounddecls(){
	// i is an int; p is a pointer to int; r is a reference to int
	int i = 1024, *p = &i, &r = i;

	// three ways to print the value of i
	std::cout << i << " " <<  *p <<  " " << r << std::endl;

	int j = 42, *p2 = &j;
	int *&pref = p2;  // pref is a reference to the pointer p2

	// prints the value of j, which is the int to which p2 points
	std::cout << *pref << std::endl;

	// pref refers to a pointer; assigning &i to pref makes p point to i
	pref = &i;
	std::cout << *pref << std::endl; // prints the value of i

	// dereferencing pref yields i, the int to which p2 points;
	*pref = 0;  // changes i to 0

	std::cout << i << " " << *pref << std::endl;

}

//基本类型间的转换
void convs(){
	int i = 42;
	std::cout << i << std::endl; // prints 42
	if (i) // condition will evaluate as true
		i = 0;
	std::cout << i << std::endl; // prints 0

	bool b = 42;            // b is true
	std::cout << b << std::endl; // prints 1

	int j = b;              // j has value 1
	std::cout << j << std::endl; // prints 1

	double pi = 3.14;       // pi has value 3.14
	std::cout << pi << std::endl; // prints 3.14

	j = pi;                 // j has value 3
	std::cout << j << std::endl; // prints 3

	unsigned char c = -1;   // assuming 8-bit chars, c has value 255
	i = c;  // the character with value 255 is an unprintable character
	        // assigns value of c (i.e., 255) to an int
	std::cout << i << std::endl; // prints 255
}

//---

using std::cout;
using std::endl;

//指针的指针
void dbl_ptr(){

    int ival = 1024;
    int *pi = &ival;   // pi points to an int
    int **ppi = &pi;   // ppi points to a pointer to an int
    cout << "The value of ival\n"
         << "direct value: " << ival << "\n"
         << "indirect value: " << *pi << "\n"
         << "doubly indirect value: " << **ppi
         << endl;

	int i = 2;
	int *p1 = &i;     // p1 points to i
	*p1 = *p1 * *p1;  // equivalent to i = i * i
	cout << "i  = " << i << endl;

	*p1 *= *p1;       // equivalent to i *= i
	cout << "i  = " << i << endl;
}

//decltype关键字使用示例
void decl_ex(){
	int a = 0;
	decltype(a) c = a;   // c is an int
	decltype((a)) d = a; // d is a reference to a
	++c;                 // increments c, a (and d) unchanged
	cout << "a: " << a << " c: " << c << " d: " << d << endl;
	++d;                 // increments a through the reference d
	cout << "a: " << a << " c: " << c << " d: " << d << endl;

	int A = 0, B = 0;
	decltype((A)) C = A;   // C is a reference to A
	decltype(A = B) D = A; // D is also a reference to A
	++C;
	cout << "A: " << A << " C: " << C << " D: " << D << endl;
	++D;
	cout << "A: " << A << " C: " << C << " D: " << D << endl;
}


//转义
void escape(){
	std::cout << '\n';       // prints a newline
	std::cout << "\tHi!\n";  // prints a tab followd by "Hi!" and a newline
	std::cout << "Hi \x4dO\115!\n"; // prints Hi MOM! followed by a newline
	std::cout << '\115' << '\n';    // prints M followed by a newline
}

#include <string>

//变量的初始化
void inits(){
	int v1(1024);    // direct-initialization, functional form
	int v2{1024};    // direct-initialization, list initializer form
	int v3 = 1024;   // copy-initialization
	int v4 = {1024}; // copy-initialization, list initializer form

	// alternative ways to initialize string from a character string literal
	std::string titleA = "C++ Primer, 5th Ed.";
	std::string titleB("C++ Primer, 5th Ed.");
	std::string all_nines(10, '9');  // all_nines = "9999999999"

	cout<<v1<<endl;
	cout<<v2<<endl;
	cout<<v3<<endl;
	cout<<v4<<endl;

	cout<<titleA<<endl;
    cout<<titleB<<endl;
    cout<<all_nines<<endl;

}

//字面量
void literals(){

	std::cout << "Hello World!";  // simple character string literal
	std::cout << "";              // empty character string literal
	// literal using newlines and tabs
	std::cout << "\nCC\toptions\tfile.[cC]\n";

    // multiline string literal
    std::cout << "a really, really long string literal "
	             "that spans two lines" << std::endl;

	// three ways to print a capital M
	std::cout << 'M' << " " << '\115' << " " << '\x4d' << std::endl;

    unsigned long long bigVal = -1ULL;
    std::cout << bigVal << std::endl;

}

//引用的基本用法
void ref_ex(){

	int i = 0, &ri = i;  // ri is a reference to i
	// ri is just another name for i;
	// this statement prints the value of i twice
	std::cout << i << " " << ri << std::endl;

	i = 5; // changing i is reflected through ri as well
	std::cout << i << " " << ri << std::endl;

	ri = 10; // assigning to ri actually assigns to i
	std::cout << i << " " << ri << std::endl;

}

//作用域
int reused = 42;  // reused has global scope

void scope_levels(){
	int unique = 0; // unique has block scope

	// output #1: uses global reused; prints 42 0
	std::cout << reused << " " << unique << std::endl;

	int reused = 0; // new, local object named reused hides global reused

	// output #2: uses local reused; prints 0 0
	std::cout << reused << " " <<  unique << std::endl;

	// output #3: explicitly requests the global reused; prints 42 0
	std::cout << ::reused << " " <<  unique << std::endl;
}

//无符号类型使用例程
void unsigned_(){
	unsigned u = 10, u2 = 42;
	std::cout << u2 - u << std::endl;
	std::cout << u - u2 << std::endl;

	int i = 10, i2 = 42;
	std::cout << i2 - i << std::endl;
	std::cout << i - i2 << std::endl;

	u = 42;
	i = 10;
	std::cout << i - u << std::endl;
	std::cout << u - i << std::endl;

	u = 10;
	i = -42;
	std::cout << i + i << std::endl;  // prints -84
	std::cout << u + i << std::endl;  // if 32-bit ints, prints 4294967264

	i = 10;
	std::cout << "good" << std::endl;
	while (i >= 0) {
		std::cout << i << std::endl;
		--i;
	}

	for (int i = 10; i >= 0; --i)
		std::cout << i << std::endl;

	for (unsigned u = 0; u <= 10; ++u)
		std::cout << u << std::endl;  // prints 0 . . . 10

/* NOTE: the condition in the following loop
         will run indefinitely
	// WRONG: u can never be less than 0; the condition will always succeed
	for (unsigned u = 10; u >= 0; --u)
    	std::cout << u << std::endl;
*/
	u = 11; // start the loop one past the first element we want to print
	while (u > 0) {
		 --u;        // decrement first, so that the last iteration will print 0
		std::cout << u << std::endl;
	}

	// be wary of comparing ints and unsigned
	u = 10;
	i = -42;
	if (i < u)               // false: i is converted to unsigned
		std::cout << i << std::endl;
	else
		std::cout << u << std::endl;   // prints 10

	u = 42; u2 = 10;
	std::cout << u - u2 << std::endl; // ok: result is 32
	std::cout << u2 - u << std::endl; // ok: but the result will wrap around
}

#endif // FUNCTIONS_H_INCLUDED
