#include "Rectangle1.h"

Rectangle1::Rectangle1() {}

Rectangle1::~Rectangle1() {}

int Rectangle1::sonTest()
{
    cout << "sontest" << endl;
    return 0;
}

int Rectangle1::testVr()
{
    Shape::testVr();
    cout << "sontestvr" << endl;

    return 0;
}

void Rectangle1::whoIAm()
{
    Shape::whoIAm();
    cout << "Besides, I am a Rectangle." << endl;
}

void Rectangle1::edgeLength(int len)
{
    cout << "I am a " << len << "x" << len << " square. " << endl;
}

void Rectangle1::edgeLength(int length, int width)
{
    cout << "I am a " << length << "x" << width << " rectangle. " << endl;
}

void Rectangle1::showName()
{
    cout << Shape::ProtectData << endl;
}

void Rectangle1::draw()
{
    Shape::draw();
    cout << "Rectangle1" << endl;
}
