#include <string.h>
#include <time.h>
#include <windows.h>

#include "challenge.h"
#include "stdio.h"
#include "stdlib.h"

int XCen(int x1[], int x2[])
{
    int x;
    x = 0;
    for (int i = 0; i < POINT_NUMBER; i++) { x = x + (x1[i] + x2[i]) / 2; }
    printf("%d", x);
    x = x / POINT_NUMBER;
    return x;
}

int AddMathVector(int x1[], int y1[], int x2[], int y2[])
{
    int x;
    int y;
    x = 0;
    y = 0;
    for (int i = 0; i < POINT_NUMBER; i++)
    {
        x = x + (x1[i] + x2[i]) / 2;
        y = y + (y1[i] + y2[i]) / 2;
        // x = x / POINT_NUMBER;
        // y = y / POINT_NUMBER;
        // Sleep(200);
    }
    printf("%d---%d\n", x, y);
    x = x / POINT_NUMBER;
    y = y / POINT_NUMBER;
    printf("%d---%d\n", x, y);
    return 0;
}
