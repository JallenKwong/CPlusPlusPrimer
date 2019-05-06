# 开始 #

## 编写一个简单的C++程序 ##

操作系统通过main来运行C++程序。

	
	int/*return type*/ main/*function name*/()/*parameter list*/
	{
	    return 0;
	}//function body | block of statement

[code](C01_1/main.cpp)

int类型是一种内置类型built-in type。

句末需分号。

在大多数系统中，main的返回值被用来指示状态。返回值0表面成功，非0的返回值含义由系统定义，通常用来指出错误类型。


### 编译、运行程序 ###

IDE Integrated Developed Environment

>PS.我在Windows下使用CodeBlocks

#### 程序源文件命名约定 ####

- .cpp
- .cc
- .c
- ...

#### 从命令行运行编译器 ####

Unix下**运行**可执行文件

	./a.out

通过echo命令获得程序返回值

	$ echo $?

GNU编译器的命令`g++`编译程序

	g++ -o prog1 prog1.cc

## 初识输入输出 ##

standard library——iostream库包含两个基础类型istream和ostream。

一个流就是一个字符序列，是从IO设备读出或写入IO设备。

术语“**流stream**”要表达的是，随着时间的推移，字符是顺序生成或消耗的。

### 标准输入输出对象 ###

标准库定义了4个IO对象。

1. cin istream类型的对象，也称为strandard input
2. cout ostream类型的对象，也称为strandard output
3. cerr ostream类型的对象，也称为strandard error，输出警告和错误信息
4. clog ostream类型的对象，用来输出程序运行时的一般性信息

### 一个使用IO库的程序 ###


两数相加，输出和

	#include <iostream>//告诉编译器我们想使用iostream

	int main()
	{
		// prompt user to enter two numbers
		std::cout << "Enter two numbers:" << std::endl;
		int v1 = 0, v2 = 0;
		std::cin >> v1 >> v2;
		std::cout << "The sum of " << v1 << " and " << v2
		          << " is " << v1 + v2 << std::endl;
		return 0;
	}


[code](C01_2/main.cpp)

\#include 指令必须出现在所有函数之外，一般放置源文件的开始位置。

#### 写入到流 ####

	std::cout << "Enter two numbers:" << std::endl;

**输出运算符<<**，它接受两个运行对象：左侧必须是一个ostream对象，右侧是要打印的值。

此运算符将给定的值写到给定的ostream对象中。

输出运算符的计算结果（返回值）就是其左侧运算对象。即，计算结果就是写入给定值的那个ostream对象。

上句相当于

	std::cout << "Enter two numbers:";
	std::cout << std::endl;

"Enter two numbers:"是**字符串字面值常量string literal**

运算符打印endl，是一个被称为**操纵符manipulator**的特殊值。写入endl的效果是结束当前行，并**将与设备关联的缓冲区buffer中的内容刷到设备中**。缓冲刷新操作可以保证到目前为止程序所产生的所有输出都真正写入输出流中，而不是仅停留在内存中等待写入流。

#### 使用标准库中的名字 ####

前缀std指出名字`cout`和`endl`是定义在名为`std`的命名空间namespace中。

命名空间可助我们不经意的名字定义冲突，以及使用库中相同名字导致的冲突。标准库定义的所有名字都在命名空间std中。

通过命名空间使用标准库有一个副作用：当使用标准库中的一个名字时，必须显示说明我们使用来自命名空间std中的名字。例如：需要写出std::cout。::为作用域运算符，指出我们想使用定义在命名空间std的名字cout。

#### 从流读取数据 ####

	int v1 = 0, v2 = 0;//初始化initialize

	std::cin >> v1 >> v2;

**输入运算符>>**，与输出运算符类似。上一句相当于

	std::cin >> v1;
	std::cin >> v2;


#### 完成程序 ####

	std::cout << "The sum of " << v1 << " and " << v2
	          << " is " << v1 + v2 << std::endl;

## 注释简介 ##

comment

### C++中注释的种类 ###

C++中有两种注释：

1. 单行注释 //
2. 界定符对注释 /* */

### 注释界定符不能嵌套 ###


## 控制流 ##

### while语句 ###

	#include <iostream>

	int main()
	{
	    int sum = 0, val = 1;
	    // keep executing the while as long as val is less than or equal to 10
	    while (val <= 10) {
	        sum += val;  // assigns sum + val to sum
	        ++val;       // add 1 to val
	    }
	    std::cout << "Sum of 1 to 10 inclusive is " 
	              << sum << std::endl;
	
		return 0;
	}

[code](C01_3/main.cpp)

while语句形式

	while(condition)
		statement

**+=复合赋值运算符**

赋值assignment

**++前缀递增运算符**

### for语句 ###

	#include <iostream>
	
	int main()
	{
	    int sum = 0;
	
	    // sum values from 1 through 10 inclusive
	    for (int val = 1; val <= 10; ++val)
	        sum += val;  // equivalent to sum = sum + val
	    std::cout << "Sum of 1 to 10 inclusive is "
	              << sum << std::endl;
	    return 0;
	}

[code](C01_4/main.cpp)

	for(/*init-statement*/;/*condition*/;/*expression*/){
		statement
	}

### 读取数量不定的输入数据 ###

	#include <iostream> 
	
	int main() 
	{
		int sum = 0, value = 0;
	
		// read until end-of-file, calculating a running total of all values read
		while (std::cin >> value) 
			sum += value; // equivalent to sum = sum + value
	
		std::cout << "Sum is: " << sum << std::endl;
		return 0;
	}

[code](C01_5/main.cpp)

	while (std::cin >> value) 

当我们使用一个istream对象作为条件时，其效果是检测流的状态。如果流有效的，即流未遇到错误，那么检测成功。

当遇到文件结束符end-of-file，或遇到一个无效输入时（如读入值不是一个整数），istream对象的状态会变为无效。那么istream对象会使条件变为假。

---

**从键盘输入文件结束符**

1. Windows Ctrl + Z + Enter
2. Unix Ctrl + D

---

**常见编译器可查出的错误**

1. syntax error 语法错误
2. type error 类型错误
3. declararion error 声明错误

### if语句 ###

[code](C01_6/main.cpp)

**注意**，C++用=进行赋值，用==作为判等运算符。两个运算符都可以出现在条件中。一个常见的错误是想在条件中使用==（相等判断），却误用了=。

## 类的简介 ##

在C++中，通过定义一个**类Class**来定义自己的数据结构

实际上，C++最初的一个设计焦点就是能定义使用上限内置类型一样自然的**类类型class type**

### Sales_item类 ###

类定义了行为

[Sales_item.h](C01_7/Sales_item.h)

#### 读写Sales_item ####

>PS. CodeBlocks需设置支持C++11的新标准，才能编译以下程序
>
>在CodeBlocks16.01编译器菜单栏，点击Settings->Compiler,打开Global compiler settings界面，将"Have g++ follow the C++11 ISO C++ language"选项打上勾，最后点击OK。

	#include <iostream>
	#include "Sales_item.h"
	
	int main()
	{
	    Sales_item book;
	
	    // read ISBN, number of copies sold, and sales price
	    std::cin >> book;
	    // write ISBN, number of copies sold, total revenue, and average price
	    std::cout << book << std::endl;
	
	    return 0;
	}

[code](C01_7/main.cpp)

输入

	0-201-70353-X 4 24.99

输出

	0-201-70353-X 4 99.96 24.99

**标准库的头文件用尖括号< \>括起来，非标准的头文件用" "括起来。**

#### Sales_item对象的加法 ####

	#include <iostream>
	#include "Sales_item.h"
	
	int main()
	{
	    Sales_item item1, item2;
	
	    std::cin >> item1 >> item2;   //read a pair of transactions
	    std::cout << item1 + item2 << std::endl; //print their sum
	
	    return 0;
	}

[code](C01_8/main.cpp)

输入

	0-201-78345-X 3 20.00
	0-201-78345-X 2 25.00

输出

	0-201-78345-X 5 110 22

---

使用文件重定向

	addItem < infile > outfile

### 初始成员函数 ###

将两个Sales_item对象相加的程序首先应该检查两个对象是否具有相同的ISBN

	#include <iostream>
	#include "Sales_item.h"
	
	int main() 
	{
	    Sales_item item1, item2;
	
	    std::cin >> item1 >> item2;
		// first check that item1 and item2 represent the same book
		if (item1.isbn() == item2.isbn()) {
	    	std::cout << item1 + item2 << std::endl;
	    	return 0;   // indicate success
		} else {
	    	std::cerr << "Data must refer to same ISBN" 
			          << std::endl;
	    	return -1;  // indicate failure
		}
	}

[code](C01_9/main.cpp)

#### 什么是成员函数 ####

	item1.isbn() == item2.isbn()

1. isbn为成员函数member function，有时称为方法method
2. .点运算符 表达 “名为item1的对象的isbn成员”
3. （）调用运算符

## 书店程序 ##

从输入流读取销售记录，生成每本书的销售报告，显示售出册数、总销售额和平均售价。

	#include <iostream>
	#include "Sales_item.h"
	
	int main() 
	{
	    Sales_item total; // variable to hold data for the next transaction
	
	    // read the first transaction and ensure that there are data to process
	    if (std::cin >> total) {
			Sales_item trans; // variable to hold the running sum
	        // read and process the remaining transactions
	        while (std::cin >> trans) {
				// if we're still processing the same book
	            if (total.isbn() == trans.isbn()) 
	                total += trans; // update the running total 
	            else {              
			        // print results for the previous book 
	                std::cout << total << std::endl;  
	                total = trans;  // total now refers to the next book
	            }
			}
	        std::cout << total << std::endl; // print the last transaction
	    } else {
	        // no input! warn the user
	        std::cerr << "No data?!" << std::endl;
	        return -1;  // indicate failure
	    }
	
	    return 0;
	}

[code](C01_10/main.cpp)

## 小结 ##


