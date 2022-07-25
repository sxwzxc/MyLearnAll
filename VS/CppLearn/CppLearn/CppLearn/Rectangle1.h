#pragma once
#include <math.h>

#include <iostream>
#include <string>
#include <vector>

#include "Shape.h"

using namespace std;

class Rectangle1 : public Shape
{
public:
    Rectangle1();
    ~Rectangle1();
    int sonTest();
    int testVr();
    void whoIAm();
    void edgeLength(int len);
    void edgeLength(int length, int width);
    void showName();
    void draw();
};
