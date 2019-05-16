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

### 处理string对象中的字符 ###

![](image/03.png)

**建议**：使用C++版本的C标准库头文件

#### 处理每个字符？使用基于范围的for语句 ####

使用C++11新标准提供的一种语句：**范围for（range for）**

	for (declaration : expression)
		statement

---

	//使用示例
	string str("some string");

	// print the characters in str one character to a line
	for (auto c : str) // for every char in str
		cout << c << endl; // print the current character followed by a newline

---

	string s("Hello World!!!");

	// punct_cnt has the same type that s.size returns; 
	decltype(s.size()) punct_cnt = 0;

	// count the number of punctuation characters in s
	for (auto c : s) // for every char in s
		if (ispunct(c)) // if the character is punctuation
			++punct_cnt; // increment the punctuation counter

	cout << punct_cnt << " punctuation characters in " << s << endl;

输出结果

	3 punctuation characters in Hello World!!!

#### 使用范围for语句改变字符串中的字符 ####

若想改变string对象中的字符的值，必须把循环变量定义成引用类型。

	string s("Hello World!!!");
	// convert s to uppercase
	for (auto &c : s) // for every char in s (note: c is a reference)
		c = toupper(c); // c is a reference, so the assignment changes the char in s

	cout << s << endl;

输出结果为

	HELLO WORLD!!!

#### 只处理一部分字符？ ####

使用**下标运算符[]**，它接收的输入参数是string::size_type类型的值，这个参数表示要访问的字符的位置；返回值是该位置上的字符的引用

string对象的下标必须大于等于0而小于s.size()，超出范围引发不可预知的结果。

---

输出对象中的第一个字符：

	if (!s.empty()) // make sure there's a character to print
		cout << s[0] << endl; // print the first character in s

字符串头字母改成大写

	string s("some string");
	if (!s.empty()) // make sure there's a character in s[0]
		s[0] = toupper(s[0]); // assign a new value to the first character in s

#### 使用下标执行迭代 ####

	// process characters in s until we run out of characters or we hit a whitespace
	for (decltype(s.size()) index = 0;
		index != s.size() && !isspace(s[index]); ++index)
			s[index] = toupper(s[index]); // capitalize the current character

**提示：注意检查下标的合法性**

#### 使用下标执行随机访问 ####

	const string hexdigits = "0123456789ABCDEF"; // possible hex digits
	cout << "Enter a series of numbers between 0 and 15"
		<< " separated by spaces. Hit ENTER when finished: "
		<< endl;

	string result; // will hold the resulting hexify'd string
	string::size_type n; // hold numbers from the input
	while (cin >> n)
		if (n < hexdigits.size()) // ignore invalid input
			result += hexdigits[n]; // fetch the indicated hex digit
	cout << "Your hex number is: " << result << endl;

输入：

	12 0 5 15 8 15

输出：

	Your hex number is: C05F8F

## 标准库类型vector ##

vector表示对象的集合，其中所有对象的类型都相同。集合中的每个对象都有一个与之对应的索引，索引用于访问对象。

因为vector容纳着其他对象，所以也被称为**容器container**

要想使用vector，必须包含适当的头文件。

	#include <vector>
	using std::vector;

C++既有**类模板class template**，也有函数模板，其中vector是一个类模板。

**模板**本身不是类或函数，相反可将模板看作为编译器生成类或函数编写的一份说明。编译器根据模板创建类或函数的过程称为**实例化instantiation**，当使用模板时，需要指出编译器应把类或函数实例化成何种类型。

对于类模板来说，我们通过**提供一些额外信息**来指定模板到底实例化成什么样的类，需要提供哪些信息由模板决定。提供信息的方式即在模板名字后面跟一对尖括号，在括号内放上信息。

以vector为例，提供额外信息是vector内所存放对象的类型：

	vector<int> ivec; // ivec holds objects of type int
	vector<Sales_item> Sales_vec; // holds Sales_items
	vector<vector<string>> file; // vector whose elements are vectors

vector 能容纳绝大多数类型的对象称为**其元素**，但是因为引用不是对象，所以不存在包含引用的vector。除此之外，其他大多数（非引用）内置类型和类类型都可以构成vector对象，甚至组成vector的元素也可以是vector。

老式编译器需要有**一个空格**在声明vector的vector

	vector<vector<int> >

### 定义和初始化vector对象 ###

![](image/04.png)

	vector<string> svec; // default initialization; svec has no elements

	vector<int> ivec; // initially empty
	// give ivec some values
	vector<int> ivec2(ivec); // copy elements of ivec into ivec2
	vector<int> ivec3 = ivec; // copy elements of ivec into ivec3
	vector<string> svec(ivec2); // error: svec holds strings, not ints

#### 列表初始化vector对象 ####

C++11新标准

	vector<string> articles = {"a", "an", "the"};

	vector<string> v1{"a", "an", "the"}; // list initialization
	vector<string> v2("a", "an", "the"); // error

#### 创建指定数量的元素 ####

	vector<int> ivec(10, -1); // ten int elements, each initialized to -1
	vector<string> svec(10, "hi!"); // ten strings; each element is "hi!"

#### 值初始化 ####

通常情况下，可以只提供vector对象容纳的元素数组而不用略去初始值。此时库会创建一个**值初始化的value-initialized**元素初值，并把它赋给容器中所有元素。这个初值有vector对象中元素的类型决定

	vector<int> ivec(10); // ten elements, each initialized to 0
	vector<string> svec(10); // ten elements, each an empty string

#### 列表初始值还是元素数量？ ####

在某些情况下，初始化的真实含义依赖于传递初始值时用的是花括号还是圆括号。

	vector<int> v1(10); // v1 has ten elements with value 0
	vector<int> v2{10}; // v2 has one element with value 10
	vector<int> v3(10, 1); // v3 has ten elements with value 1
	vector<int> v4{10, 1}; // v4 has two elements with values 10 and 1

	vector<string> v5{"hi"}; // list initialization: v5 has one element
	vector<string> v6("hi"); // error: can't construct a vector from a string
	literal
	vector<string> v7{10}; // v7 has ten default-initialized elements
	vector<string> v8{10, "hi"}; // v8 has ten elements with value "hi"

### 向vector对象中添加元素 ###

## 迭代器介绍 ##

## 数组 ##

## 多维数组 ##


