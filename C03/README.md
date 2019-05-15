# 字符串、向量和数组 #

## 命名空间的using声明 ##

using declaration

	using namespace::name;

一旦声明了上述语句，就可以直接访问命名空间中的名字

	#include <iostream>
	// using declaration; when we use the name cin, we get the one from the namespace std
	using std::cin;
	int main()
	{
		int i;
		cin >> i; // ok: cin is a synonym for std::cin
		cout << i; // error: no using declaration; we must use the full name
		std::cout << i; // ok: explicitly use cout from namepsace std
		return 0;
	}

### 每个名字都需要独立的using声明 ###

每个声明引入命名空间中的一个成员

	#include <iostream>
	// using declarations for names from the standard library
	using std::cin;
	using std::cout; using std::endl;
	
	int main()
	{
		cout << "Enter two numbers:" << endl;
		int v1, v2;
		cin >> v1 >> v2;
		cout << "The sum of " << v1 << " and " << v2
		<< " is " << v1 + v2 << endl;
		return 0;
	}

一开始就有对`cin`、`cout`和`endl`的using声明，这意味着我们不再添加`std::`形式的前缀就能直接使用它们。

### 头文件不应该包含using声明 ###

有可能产生始料未及的名字冲突。

## 标准库类型string ##

标准库类型string表示可变长的字符序列，使用string类型必须首先包含string头文件

	#include <string>
	using std::string;

### 定义和初始化string对象 ###

初始化string对象常用方式

	string s1; // default initialization; s1 is the empty string
	string s2 = s1; // s2 is a copy of s1
	string s3 = "hiya"; // s3 is a copy of the string literal
	string s4(10, 'c'); // s4 is cccccccccc

![](image/01.png)

### 直接初始化和拷贝初始化 ###

若使用等号=初始化一个变量，实际上执行的是**拷贝初始化copy initialization**，编译器把等号右侧的初始值拷贝到新创建的对象中去。

与之相反，若不使用等号，则执行的是**直接初始化direct initialization**。

	string s5 = "hiya"; // copy initialization
	string s6("hiya"); // direct initialization
	string s7(10, 'c'); // direct initialization; s7 is cccccccccc

	string s8 = string(10, 'c'); // copy initialization; s8 is cccccccccc
	//本质等于
	string temp(10, 'c'); // temp is cccccccccc
	string s8 = temp; // copy temp into s8

>PS.两个初始化有何差别，书上没说。

### string对象上的操作 ###

![](image/02.png)

### 读写string对象 ###

	// Note: #include and using declarations must be added to compile this code
	int main()
	{
		string s; // empty string
		cin >> s; // read a whitespace-separated string into s
		cout << s << endl; // write s to the output
		return 0;
	}

在执行读取操作时，string对象会自动忽略开头的空白（即空格符、换行符、制表符）并从第一个真正的字符开始读起，直到遇见下一处空白为止。

So, if the input to this program is `Hello World!` (note leading and trailing spaces), then the output will be `Hello` with no extra spaces.

Like the input and output operations on the built-in types, the string operators return their left-hand operand as their result. Thus, we can chain together multiple reads or writes

	string s1, s2;
	cin >> s1 >> s2; // read first input into s1, second into s2
	cout << s1 << s2 << endl; // write both strings

If we give this version of the program the same input, `Hello World!`, our output would be “`HelloWorld!`”

### 读取未知数量的string对象 ###

	int main()
	{
		string word;

		//重复若干次后，一旦遇到文件结束标记或非法输入循环也就结束了
		while (cin >> word) // read until end-of-file
			cout << word << endl; // write each word followed by a new line
		return 0;
	}

### 使用getline读取一整行 ###

有时希望能最终得到的字符串中保留输入时的空白符，这时应该用`getline()`代替`>>`运算符。

getline()的参数是一个输入流和一个string对象，函数从给定的输入流中读入内容，直到遇到换行符为止（注意换行符也被读进来），然后把所读的内容存入到那个string对象中去（注意不存换行符）。

	int main()
	{
		string line;
		// read input a line at a time until end-of-file
		while (getline(cin, line))
		cout << line << endl;
		return 0;
	}

### string的empty和size操作 ###

empty()根据string对象是否为空返回一个对应的布尔值。

	// read input a line at a time and discard blank lines
	while (getline(cin, line))
	if (!line.empty())
		cout << line << endl;

size()返回string对象的长度。

	string line;
	// read input a line at a time and print lines that are longer than 80 characters
	while (getline(cin, line))
		if (line.size() > 80)
			cout << line << endl;

### string::size_type类型 ###

size()返回的是一个string::size_type类型的值。

可推断，它是无符号整型。

C++新标准中，允许编译器auto或者decltype来推断变量的类型

	auto len = line.size(); // len has type string::size_type

切记，若表达式中混用了带符号数和无符号数将可能产生意想不到结果。例如，假如n是一个具有负值的`int`，则表达式`s.size()<n`的判断结果几乎肯定是`true`。因为负值n自动地转换成一个比较大无符号值。

### 比较string对象 ###

The equality operators (== and !=) test whether two strings are **equal** or **unequal**, respectively.

The relational operators <, <=, >, >= test whether one string is **less than**, **less than or equal to**, **greater than**, or **greater than or equal to** another.

These operators use the same strategy as a (case-sensitive) **dictionary**:

1. If two strings have different lengths and if every character in the shorter string is equal to the corresponding character of the longer string, then the shorter string is **less than** the longer one.

2. If any characters at corresponding positions in the two strings differ, then the result of the string comparison is the result of comparing the first character at which the strings differ.

---

	string str = "Hello";
	string phrase = "Hello World";
	string slang = "Hiya";

Using rule 1, we see that `str` is less than `phrase`. By applying rule 2, we see that `slang` is greater than both `str` and `phrase`.

### 为string对象赋值 ###

	string st1(10, 'c'), st2; // st1 is cccccccccc; st2 is an empty string
	st1 = st2; // assignment: replace contents of st1 with a copy of st2
				// both st1 and st2 are now the empty string

### 两个string对象相加 ###

	string s1 = "hello, ", s2 = "world\n";
	string s3 = s1 + s2; // s3 is hello, world\n
	s1 += s2; // equivalent to s1 = s1 + s2

### 字面值和string对象相加 ###

因为某些历史原因，也为了与C兼容，所以**C++语言中的字符串字面量**不是**标准库类型string的对象**。**切记**，字符串字面值与string是不同的类型。

**字符串字面量不能直接相加**

	string s1 = "hello", s2 = "world"; // no punctuation in s1 or s2
	string s3 = s1 + ", " + s2 + '\n';

	string s4 = s1 + ", "; // ok: adding a string and a literal
	string s5 = "hello" + ", "; // error: no string operand
	string s6 = s1 + ", " + "world"; // ok: each + has a string operand
	string s7 = "hello" + ", " + s2; // error: can't add string literals

---

	string s6 = (s1 + ", ") + "world";

	//等价于

	string tmp = s1 + ", "; // ok: + has a string operand
	s6 = tmp + "world"; // ok: + has a string operand

	string s7 = ("hello" + ", ") + s2; // error: can't add string literals

## 标准库类型vector ##

## 迭代器介绍 ##

## 数组 ##

## 多维数组 ##


