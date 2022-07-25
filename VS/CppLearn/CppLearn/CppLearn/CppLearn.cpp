#pragma once
#include "CppLearn.h"

using namespace std;

/*
第一题：
完成以下函数的功能实现， 目标是打印输出两个参数的和、差、积、商。
函数的目标是计算 a + b, a - b, a x b, a ÷ b 的结果。
当输入参数不满足指定的运算要求时, 结果用 “NUL” 字符串替代.
*/
void calculate(int a, int b)
{
    printf("a=%d,b=%d\n", a, b);
    cout << "a+b=" << a + b << " , ";
    cout << "a-b=" << a - b << " , ";
    cout << "a*b=" << a * b << " , ";
    cout << "a/b=" << a / b;
}

/*
第二题：
1E-3F //float
3.14159L //long double
100ULL // unsigned long long
u8"hello" //char
L'A'// wchar_t
*/

/*
第三题
使用 C++中两种不同的方式写类型别名， ’/’左边是目标结果类型符
号， 右边是实际的数据类型。 注意，答案要写成 C++语句形式。
*/
using SizeType = std::size_t;
using DBL = double;
using CPtr = char*;
/*using ValueType = std::priority_queue<int, std::vector<int>,
 * std::greater<int>>::value_type;*/
typedef std::size_t SizeType;
typedef double DBL;
typedef char* CPtr;
/*typedef std::priority_queue<int, std::vector<int>,
 * std::greater<int>>::value_type ValueType;*/

/*
第四题
给出一个雇员类型， 请构造一个雇员对象，
填写自己相关的信息，实现打印函数然后输出雇员信息。
*/
struct employee
{
    enum
    {
        SMALL = 32,
        MEDIUM = 128,
        LARGE = 1024,
        XLARGE = 2048
    };
    char name[SMALL];
    char title[MEDIUM];
    std::string company;
    char gender;
    int year;
    int month;
    int day;
};

void showEmployee()
{
    employee myself;
    strcpy_s(myself.name, "ShenXiaowei");
    strcpy_s(myself.title, "SoftwareEngineer_Windows");
    myself.company = "TP-LINK";
    myself.gender = 'M';
    myself.year = 2021;
    myself.month = 7;
    myself.day = 16;
    printf("start\n");
    printf(
        "Name:%s\nTitle:%s\nCompany:%s\nGender:%c\nYear:%d\nMonth:%d\nDay:%d\n",
        myself.name, myself.title, myself.company.c_str(), myself.gender,
        myself.year, myself.month, myself.day);
    printf("over\n");
}

/*
第五题：
数组中查找满足两数之和等于目标值的元素索引
给定整数数组 nums 和整数目标值 target，请在该数组中找出和为目标值 target
的那两个整数，返回它们的数组下标。假设每种输入只会对应一个答案,
数组中同一个元素在答案里不能重复出现。
*/
vector<int> findTwoSum(const vector<int>& nums, int target)
{
    int all = nums.size();
    vector<int> answer;
    for (int i = 0; i < all; i++)
    {
        for (int j = i; j < all; j++)
        {
            if ((nums[i] + nums[j] == target) && i != j)
            {
                cout << "[" << nums[i] << "," << nums[j] << "]" << endl;
                answer.push_back(nums[i]);
                answer.push_back(nums[j]);
                return answer;
            }
        }
    }
    return answer;
}

/*
第六题：
用两种方法求解整数的阶乘。
*/
long long factorial1(int n)
{
    if (n == 0)
        return 1;
    return factorial1(n - 1) * n;
}

long long factorial2(int n)
{
    long long answer = 1;
    while (n > 0)
    {
        answer = answer * n;
        n--;
    }
    return answer;
}

/*
第七题：
我有一个需求：需要一个函数指针类型，该函数指针类型对象所指涉的函数类型有两个参数，第一个参数是
string[相关]类型，并且 API 明确告诉用户我们不需要修改实参; 第二个参数是一个 int
值，函数的返回类型是int.
*/
int func(string str, int val)
{
    cout << "str:" << str << ",val:" << val << endl;
    return 0;
}

/*
第八题：
字符串反转
编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组char[]的形式给出。不要给另外的数组分配额外的空间，你必须原地修改输入数组、使用
O(1)的额外空间解决这一问题。数组中的所有字符都是 ASCII码表中的可打印字符。
*/
void reverseStr(vector<char>& vecOfChars)
{
    int all = vecOfChars.size() - 1;
    char temp;
    temp = vecOfChars[0];
    for (int i = 0; i < ceil(all / 2) + 1; i++)
    {
        temp = vecOfChars[i];
        vecOfChars[i] = vecOfChars[all - i];
        vecOfChars[all - i] = temp;
    }
    for (auto j : vecOfChars)
    {
        cout << j << " ";
    }
}
/*
第九题:
一道设计题
在我们的开发中, 常常需要用 Log 来调试 debug
或者检测、追踪一个软件系统的运行状态。现在需要设计一个简单的 TPLog
类，它需要有下面的一些属性状态： logId : 标识某条 TPLog 的身份; module: 产生该
log 的模块名称; level: log 的级别; datetime: 表示 log 生成的日期时间, “2021 - 07
- 15 14 : 09 : 33” “yyyy - mm - dd hh : mm:ss”
    注意这样的时间格式，中间的空格，数字的位数，使用 log
对象构造时的系统时间。还要注意的是，这里的 datetime
不表示具体实现，而是一种抽象概念。具体实现可以不出现 datetime
属性字段而采用其他多个变量的方式。或者, 也可以直接用该属性字段，设计上是灵活的。
content : 表示 log 内容;
*/
