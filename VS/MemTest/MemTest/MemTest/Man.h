#pragma once
#include <iostream>
#include <string>
using namespace std;
class Man
{
public:
    Man(const Man &man)
    {
        pName_ = new string;
        *pName_ = *man.pName_;
        age_ = man.age_;
    }
    Man &operator=(const Man &man)
    {
        *pName_ = *man.pName_;
        age_ = man.age_;
        return *this;
    }
    ~Man()
    {
        cout << "Man " << *pName_ << " age:" << age_ << " die. " << endl;
        delete pName_;
    }
    Man(const std::string &name = std::string())
        : pName_(new std::string(name)), age_(0)
    {
    }

private:
    std::string *pName_;
    int age_;
};
