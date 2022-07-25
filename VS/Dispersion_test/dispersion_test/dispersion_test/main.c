#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <time.h>
#include <windows.h>

#include "MyAns.h"
#include "challenge.h"
#include "stdio.h"
#include "stdlib.h"

static double timeDiff(struct timeval *pStart, struct timeval *pEnd)
{
    return (pEnd->tv_usec - pStart->tv_usec) * 0.001
           + (double)(pEnd->tv_sec - pStart->tv_sec) * 1000.0;
}

/************************************
函数名: read_scatter_data_for_performance
功能：读取样本/测试用例中的散点数据，计算每组散点的归一化离散度值，并将结果输出到txt文件中
输入参数：order_number：散点文件起始标号，file_name：存储离散度值的文件名
输出参数：无
返回值：平均计算时间
************************************/
double read_scatter_data_for_performance_and_efficiency(int order_number,
                                                        char *file_name,
                                                        int sample_number)
{
    int i = 0;
    int j = 0;
    char drop_point_file[200] = {0};
    int scatter_ax[POINT_NUMBER] = {0};
    int scatter_ay[POINT_NUMBER] = {0};
    int scatter_bx[POINT_NUMBER] = {0};
    int scatter_by[POINT_NUMBER] = {0};
    int dispersion_result = 0;
    FILE *fpRead = NULL;
    FILE *fpWrite = NULL;
    struct timeval start_time, end_time;
    double elapsed_time = 0.0;
    fpWrite = fopen(file_name, "w");
    if (NULL == fpWrite)
    {
        printf("read_scatter_data_for_performance， cannot open file\n");
        return 0;
    }

    for (i = 0; i < sample_number; i++)
    {
        order_number++;
        sprintf(drop_point_file, "./data/%d.txt", order_number);

        fpRead = fopen(drop_point_file, "r");
        if (NULL == fpRead)
        {
            printf("cannot open drop_point_file.txt\n");
            return 0;
        }

        for (j = 0; j < POINT_NUMBER; j++)
        {
            fscanf(fpRead, "%d %d  %d %d\n", &scatter_ax[j], &scatter_ay[j],
                   &scatter_bx[j], &scatter_by[j]);
        }

        /* 记录提交者的时间 */
        gettimeofday(&start_time, NULL);
        AddMathVector(scatter_ax, scatter_ay, scatter_bx, scatter_by);
        dispersion_result =
            compare_dispersion(scatter_ax, scatter_ay, scatter_bx, scatter_by);
        gettimeofday(&end_time, NULL);
        elapsed_time += timeDiff(&start_time, &end_time);
        /* 把结果写到文件中，稍后进行对比 */
        fprintf(fpWrite, "%d  %d \n", order_number, dispersion_result);
        fclose(fpRead);
    }

    fclose(fpWrite);

    elapsed_time /= TEST_SAMPLE_NUMBER;

    return elapsed_time;
}

int gettimeofday(struct timeval *tp, void *tzp)
{
    time_t clock;
    struct tm tm;
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    tm.tm_year = wtm.wYear - 1900;
    tm.tm_mon = wtm.wMonth - 1;
    tm.tm_mday = wtm.wDay;
    tm.tm_hour = wtm.wHour;
    tm.tm_min = wtm.wMinute;
    tm.tm_sec = wtm.wSecond;
    tm.tm_isdst = -1;
    clock = mktime(&tm);
    tp->tv_sec = clock;
    tp->tv_usec = wtm.wMilliseconds * 1000;
    return (0);
}

int algorithm_perfomance_test()
{
    /* 返回这部分的分数 */
    int i = 0;
    int order = 0;
    int calculated_disperation = 0;
    int train_disperation = 0;
    int error_number = 0;
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;

    char *test_data_dispersion = "dispersion_result.txt";

    /* 示例代码：求计算得到的离散度值与标准结果的平均偏差 */
    fp1 = fopen(test_data_dispersion, "r");
    if (NULL == fp1)
    {
        printf("test_data_dispersion, cannot open file\n");
        return 0;
    }

    fp2 = fopen("./data_label.txt", "r");
    if (NULL == fp2)
    {
        printf("data_label, cannot open file\n");
        return 0;
    }

    for (i = 0; i < TEST_SAMPLE_NUMBER; i++)
    {
        fscanf(fp1, "%d  %d \n", &order, &calculated_disperation);
        fscanf(fp2, "%d  %d \n", &order, &train_disperation);
        if (calculated_disperation != train_disperation)
        {
            error_number += 1;
        }
    }

    fclose(fp1);
    fclose(fp2);

    /* 返回这部分的分数 */
    return error_number;
}

int main(void)
{
    int error_number = 0;
    double eff = 0; /* 提交者的时间 */
    int score_efficiency = 0;
    int score_performance = 0;
    struct timeval start_time, end_time;
    double elapsed_time = 0.0;
    int total_score = 0;
    char *test_data_dispersion = "dispersion_result.txt";

    gettimeofday(&start_time, NULL);

    eff = read_scatter_data_for_performance_and_efficiency(
        0, test_data_dispersion, TEST_SAMPLE_NUMBER);

    /* 本地时间是1.47ms，限制在2ms */
    if (eff > 2)
    {
        printf("Over time \n");
        return 0;
    }
    score_efficiency = 5 * (log(2 / eff) / log(2));

    error_number = algorithm_perfomance_test();

    /* 错误率大于20%，直接0分 */
    if (error_number > TEST_SAMPLE_NUMBER * 0.2)
    {
        printf("Too much error samples\n");
        return 0;
    }
    score_performance = 50 - error_number * 0.05;
    if (score_performance < 0)
    {
        score_performance = 0;
    }

    gettimeofday(&end_time, NULL);
    elapsed_time += timeDiff(&start_time, &end_time);

    total_score = score_efficiency + score_performance;
    if (total_score > 100)
    {
        total_score = 100;
    }

    printf("The efficiency time of submitter is %f ms\n", eff);
    printf("The score of efficiency is %d\n", score_efficiency);
    printf("score_performance %d\n", score_performance);
    printf("total_score %d\n", total_score);
    printf("total time %f\n", elapsed_time);

    getchar();
    /* 返回值需要是分数(0-100) */
    return total_score;
}
