//#define _CRT_SECURE_NO_WARNINGS
#ifndef __DISPERSION_CALCULATION_H__
#define __DISPERSION_CALCULATION_H__

#include <math.h>

#define POINT_NUMBER (11520)
#define TEST_SAMPLE_NUMBER (20)
#define BLOCK_NUMBER (225)
#define TPAWB_MAP_WIDTH (180)
#define TPAWB_MAP_HEIGHT (180)
#define MAX_COMPLEXITY (520000000)
#define CLK_TCK (1000)

#define ABS(x) ((x) > 0 ? (x) : -(x))

int compare_dispersion(int* scatter_ax, int* scatter_ay, int* scatter_bx,
                       int* scatter_by);

#endif
