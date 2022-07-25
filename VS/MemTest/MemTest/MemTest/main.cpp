#include "main.h"

#include <iostream>
#include <memory>
#include <string>

#include "Man.h"

using namespace std;

void getMemory(char **p, int iBytesNum)
{
    *p = (char *)malloc(sizeof(char) * iBytesNum);
}
void func()
{
    char *p = NULL;
    getMemory(&p, 4);
    p[0] = 'a';
    cout << p[0] << endl;
}
void func2()
{
    auto pShared = make_shared<int>();
    auto pi = pShared.get();
    *pi = 2;
    delete pi;
}
void func3()
{
    int *pI = nullptr;
    {
        auto pShared = std::make_shared<int>();
        pI = pShared.get();
    }
    if (pI != nullptr)
    {
        *pI = 2;
    }
}

int callTime()
{
    static int count = 0;
    return count++;
}

char *strConnect(char *strA, char *strB)
{
    int len1 = strlen(strA) + 1;
    int len2 = strlen(strB) + 1;
    int len3 = len1 + len2 + 1;
    char *strC = new char[len3];
    strcpy_s(strC, len3, strA);
    strcat_s(strC, len3, strB);
    cout << strC;
    return strC;
}

int main()
{
    strConnect("aasdasd", "Bzxczxc");
    cout << endl << "================================" << endl;
    Man *man1 = new Man("aaaa");
    Man *man2 = new Man("bbbb");
    Man *man3 = new Man(*man2);
    *man2 = *man3;
    delete man1;
    delete man2;
    delete man3;

    cout << endl << "================================" << endl;
    string a = "aaaaaa";
    string *b;
    string c = "cccccc";
    string *d = new string;
    c = a;
    a = "a2a2a2a2";
    string &e = string("asdzxc");

    // strcpy_s(a.c_str(), 200, c.c_str());
    b = new string("ASD");
    d = b;
    cout << &a << "==" << a << endl;
    cout << b << "==" << *b << endl;
    cout << &c << "==" << c << endl;
    cout << d << "==" << *d << endl;
    cout << &e << "==" << e << endl;
    delete d;
    // func();
    // func2();
    // func3();
    // testFunc();
    //     C data(6);
    //     C *cp = new C(5);
    //     compare(cp, data);
    //     cout << "over";
    //     int ix = 1024, *pi = &ix, *pi2 = new int(2048);
    //     typedef unique_ptr<int> IntP;
    //     //IntP p0(ix);
    //     IntP p1(pi);
    //     IntP p2(pi2);
    //     IntP p3(&ix);
    //     IntP p4(new int(2048));
    //     IntP p5(p2.get());
    //  A *aa = new A(12);
    // delete aa;
    getchar();
    return 0;
}
