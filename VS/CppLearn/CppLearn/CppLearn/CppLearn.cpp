#pragma once
#include "CppLearn.h"

using namespace std;

/*
��һ�⣺
������º����Ĺ���ʵ�֣� Ŀ���Ǵ�ӡ������������ĺ͡�������̡�
������Ŀ���Ǽ��� a + b, a - b, a x b, a �� b �Ľ����
���������������ָ��������Ҫ��ʱ, ����� ��NUL�� �ַ������.
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
�ڶ��⣺
1E-3F //float
3.14159L //long double
100ULL // unsigned long long
u8"hello" //char
L'A'// wchar_t
*/

/*
������
ʹ�� C++�����ֲ�ͬ�ķ�ʽд���ͱ����� ��/�������Ŀ�������ͷ�
�ţ� �ұ���ʵ�ʵ��������͡� ע�⣬��Ҫд�� C++�����ʽ��
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
������
����һ����Ա���ͣ� �빹��һ����Ա����
��д�Լ���ص���Ϣ��ʵ�ִ�ӡ����Ȼ�������Ա��Ϣ��
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
�����⣺
�����в�����������֮�͵���Ŀ��ֵ��Ԫ������
������������ nums ������Ŀ��ֵ target�����ڸ��������ҳ���ΪĿ��ֵ target
���������������������ǵ������±ꡣ����ÿ������ֻ���Ӧһ����,
������ͬһ��Ԫ���ڴ��ﲻ���ظ����֡�
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
�����⣺
�����ַ�����������Ľ׳ˡ�
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
�����⣺
����һ��������Ҫһ������ָ�����ͣ��ú���ָ�����Ͷ�����ָ��ĺ���������������������һ��������
string[���]���ͣ����� API ��ȷ�����û����ǲ���Ҫ�޸�ʵ��; �ڶ���������һ�� int
ֵ�������ķ���������int.
*/
int func(string str, int val)
{
    cout << "str:" << str << ",val:" << val << endl;
    return 0;
}

/*
�ڰ��⣺
�ַ�����ת
��дһ���������������ǽ�������ַ�����ת�����������ַ������ַ�����char[]����ʽ��������Ҫ�����������������Ŀռ䣬�����ԭ���޸��������顢ʹ��
O(1)�Ķ���ռ�����һ���⡣�����е������ַ����� ASCII����еĿɴ�ӡ�ַ���
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
�ھ���:
һ�������
�����ǵĿ�����, ������Ҫ�� Log ������ debug
���߼�⡢׷��һ�����ϵͳ������״̬��������Ҫ���һ���򵥵� TPLog
�࣬����Ҫ�������һЩ����״̬�� logId : ��ʶĳ�� TPLog �����; module: ������
log ��ģ������; level: log �ļ���; datetime: ��ʾ log ���ɵ�����ʱ��, ��2021 - 07
- 15 14 : 09 : 33�� ��yyyy - mm - dd hh : mm:ss��
    ע��������ʱ���ʽ���м�Ŀո����ֵ�λ����ʹ�� log
������ʱ��ϵͳʱ�䡣��Ҫע����ǣ������ datetime
����ʾ����ʵ�֣�����һ�ֳ���������ʵ�ֿ��Բ����� datetime
�����ֶζ�����������������ķ�ʽ������, Ҳ����ֱ���ø������ֶΣ�����������ġ�
content : ��ʾ log ����;
*/
