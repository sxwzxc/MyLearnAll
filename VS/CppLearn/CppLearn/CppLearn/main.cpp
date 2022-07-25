#include "CppLearn.h"
#include "Rectangle1.h"
#include "Rectangle2.h"
#include "Shape.h"
#include "TPLog.h"

using namespace std;

int main()
{
    srand(time(0));

    long long long1 = 1234567891011;
    long1 = 123456789;
    char deviceID[20]="";
    if (long1>999999999)
    {
        char deviceIDHigh[10];
        char deviceIDLow[10];
        _ltoa_s(long1/1000000000, deviceID, 10);
        cout << long1 / 1000000000 << endl;
        _ltoa_s(long1%1000000000, deviceIDLow, 10);
        cout << long1 % 1000000000 << endl;
        strcat_s(deviceID, deviceIDLow);
    }
    else {
        _ltoa_s(long1, deviceID, 10);
    }
    char deviceIDHigh[10];
    char deviceIDLow[10];
    cout << long1 << endl;
    cout << deviceID<<endl;



    // calculate(5, 6);
    // ShowEmployee();
    //     vector<int> nums2 = { 0,5,6,7,8,9,10 };
    //     findTwoSum(nums2, 15);
    //     vector<char> char1 = {'a', 's', 'd', 'z', 'x', 'c', 'q'};
    //     reverseStr(char1);
    //     func("hello", 456);
    //     for (int i = 1; i <= 16; i++)
    //     {
    //         cout << factorial1(i) << endl;
    //         cout << factorial2(i) << endl;
    //     } /*第六题*/

    //     TPLog *tplog1=new TPLog;
    //     tplog1->CreateLog(123, "Player", "ERROR", "player has error!");
    //     tplog1->ShowLog();
    //    delete tplog1;
    /*
    第九题
    TPLog *tplogptr = new TPLog[20];
    for (int i = 0; i < 20; i++)
    {
        tplogptr[i].createLog(rand() % 10000 + 1, to_string(rand() % 5),
                              to_string(rand() % 5), "rand");
        tplogptr[i].ShowLog();
    }
    // cout << "=====sort=====" << endl;
    //     tplogptr[0].logSort(tplogptr);
    //     for (int i = 0; i < 20; i++)
    //     {
    //         tplogptr[i].ShowLog();
    //     }
    delete[] tplogptr;
    */
    /*第十题
    Rectangle1 *pRect1 = new Rectangle1;
    pRect1->setLevel(6);
    cout << pRect1->level() << endl;
    pRect1->setName("happy");
    pRect1->name();
    pRect1->whoIAm();
    pRect1->edgeLength(5);
    pRect1->edgeLength(6, 7);
    Rectangle2 *pRect2 = new Rectangle2;
    pRect2->showName();
    */
    TPLog *tplogPtr2 = new TPLog[50];
    vector<TPLog> logVec;
    for (int i = 0; i < 50; i++)
    {
        logVec.push_back(tplogPtr2[i]);
        logVec[i].createLog(rand() % 10000 + 1, to_string(rand() % 5),
                            to_string(rand() % 5), "rand");
        logVec[i].showLog();
    }
    cout << "===============rand===============" << endl;
    for (int i = 0; i < 50; i++)
    {
        swap(logVec[i], logVec[rand() % 50]);
    }
    for (int i = 0; i < 50; i++)
    {
        logVec[i].showLog();
    }
    cout << "===============sort===============" << endl;
    logVec[0].logSort(logVec);
    for (int i = 0; i < 50; i++)
    {
        logVec[i].showLog();
    }
    delete[] tplogPtr2;
    getchar();
    return 0;
}
