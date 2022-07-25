#include "Shape.h"
using namespace std;

Shape::~Shape()
{
    cout << "Shape::~Shape() called!" << endl;
}

void Shape::fun2()
{
    cout << "Shape's test1()" << endl;
}

int Shape::testVr()
{
    cout << "shapevr" << endl;
    return 0;
}
