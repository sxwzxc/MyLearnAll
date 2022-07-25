#include "challenge.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/************************************
������: compare_dispersion
���ܣ������ά�ռ��е����ɢ�ȱȽ�
���������scatter_ax:ɢ�������,scatter_ay:ɢ��������,scatter_bx:ɢ�������,scatter_by:ɢ��������
�����������
����ֵ����ɢ�ȶԱȽ��
************************************/

int compare_dispersion(int* scatter_ax, int* scatter_ay, int* scatter_bx,
                       int* scatter_by)
{
    int i = 0;
    int j = 0;
    int num_hblocks = 15; /* ����ֿ���Ŀ */
    int num_vblocks = 15; /* ����ֿ���Ŀ */
    int block_width = TPAWB_MAP_WIDTH / num_hblocks;
    int block_height = TPAWB_MAP_HEIGHT / num_vblocks;
    int sub_block_x = 0;
    int sub_block_y = 0;
    long long sum_dispersion_a = 0, sum_dispersion_b = 0;
    int num_block_point_a[BLOCK_NUMBER] = {0};
    int num_block_point_b[BLOCK_NUMBER] = {0};
    float norm_distance_a = 0, norm_distance_b = 0;
    double diff = 0;

    /* ͳ�Ƹ����ֿ�������Ŀ */
    for (i = 0; i < POINT_NUMBER; i++)
    {
        /* ����ͼ��a */
        sub_block_x = scatter_ax[i] / block_width;
        sub_block_y = scatter_ay[i] / block_height;

        if (sub_block_x > 0 && sub_block_x < num_hblocks && sub_block_y > 0
            && sub_block_y < num_vblocks)
        {
            num_block_point_a[sub_block_x + num_hblocks * sub_block_y]++;
        }

        /* ����ͼ��b */
        sub_block_x = scatter_bx[i] / block_width;
        sub_block_y = scatter_by[i] / block_height;

        if (sub_block_x > 0 && sub_block_x < num_hblocks && sub_block_y > 0
            && sub_block_y < num_vblocks)
        {
            num_block_point_b[sub_block_x + num_hblocks * sub_block_y]++;
        }
    }

    /* ����ɢ�����ɢ�� */
    for (i = 0; i < num_hblocks * num_vblocks - 1; i++)
    {
        for (j = i + 1; j < num_hblocks * num_vblocks; j++)
        {
            /* ����ͼ��a */
            sum_dispersion_a +=
                (num_block_point_a[i] * num_block_point_a[j]
                 * sqrt((j % num_hblocks - i % num_hblocks)
                            * (j % num_hblocks - i % num_hblocks)
                        + (j / num_hblocks - i / num_hblocks)
                              * (j / num_hblocks - i / num_hblocks)));
            /* ����ͼ��b */
            sum_dispersion_b +=
                (num_block_point_b[i] * num_block_point_b[j]
                 * sqrt((j % num_hblocks - i % num_hblocks)
                            * (j % num_hblocks - i % num_hblocks)
                        + (j / num_hblocks - i / num_hblocks)
                              * (j / num_hblocks - i / num_hblocks)));
        }
    }
    norm_distance_a =
        1.0 * sum_dispersion_a / MAX_COMPLEXITY; /* ��һ�������ɢ��ֵ */
    norm_distance_b =
        1.0 * sum_dispersion_b / MAX_COMPLEXITY; /* ��һ�������ɢ��ֵ */

    diff = norm_distance_a - norm_distance_b;

    // printf("norm_distance_a %f,norm_distance_b %f,sum_dispersion_a
    // %llu,sum_dispersion_b %llu, diff %f,abs_diff
    // %f\n",norm_distance_a,norm_distance_b,
    // sum_dispersion_a,sum_dispersion_b,diff,diff_abs);
    if (ABS(diff) < 0.05)
    {
        return 0;
    }
    else if (diff > 0)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}
