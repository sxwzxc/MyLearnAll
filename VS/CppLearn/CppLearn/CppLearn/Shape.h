#pragma once
#include <math.h>

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Shape
{
public:
    Shape(const string &strname = "Unknow", int shapeLevel = 1)
        : nameOfShape(strname), levelOfShape(shapeLevel)
    {
    }
    virtual ~Shape();
    void fun2();
    string test2 = "test11111";
    virtual int testVr();

    int level() const { return this->levelOfShape; }

    void setLevel(int level) { this->levelOfShape = level; }

    virtual void draw()
    {
        cout << "draw Shape basics..." << endl;
        Shape::paintingContent += "    +draw Shape basics...\n";
    }
    virtual string name()
    {
        cout << Shape::nameOfShape << endl;
        return Shape::nameOfShape;
    }
    virtual void setName(string name) { Shape::nameOfShape = name; }
    virtual void whoIAm() { cout << "I am a simple shape." << endl; }

protected:
    string ProtectData = "TP";

private:
    string nameOfShape;
    int levelOfShape;
    string paintingContent;
};
