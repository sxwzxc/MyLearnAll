#pragma once
#include <iostream>
#include <vector>

using namespace std;
class A
{
public:
    A(int num) : num_(num) {}
    inline int GetNum() { return num_; }

private:
    int num_;
};
A* GetClass(int num)
{
    A a(num);
    return &a;
}

class B
{
public:
    B(int num) : num_(num) {}
    inline int GetNum() { return num_; }

private:
    int num_;
};
void push(int num, vector<B*>& list)
{
    list.push_back(new B(num));
}
void testFunc()
{
    std::vector<B*> listB;
    for (int i = 0; i < 10; ++i) { push(i, listB); }
    listB.clear();
}

class C
{
public:
    C(int num) : num_(num) {}
    inline int GetNum() { return num_; }
    ~C() { cout << "*" << endl; }

private:
    int num_;
};
bool compare(const C* pData1, C data)
{
    cout << "start" << endl;
    C a1(*pData1);
    C a2(data);
    return a1.GetNum() > a2.GetNum();
}
