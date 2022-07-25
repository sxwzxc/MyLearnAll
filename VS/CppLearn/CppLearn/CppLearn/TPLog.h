#pragma once
#include <math.h>
#include <windows.h>

#include <ctime>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
using namespace std;

class TPLog
{
public:
    enum Module
    {
        Album,
        Player,
        Comm,
        Message,
        Device
    };
    enum Level
    {
        VERB,
        DEBUG,
        INFO,
        WARN,
        ERR
    };
    TPLog();
    virtual ~TPLog();
    long long UsePureTime();
    int GetId();
    void showLog();
    void createLog(int logId, string modulename, string levelname,
                   string content);
    void logSort(TPLog* tplogptr);
    void logSort(vector<TPLog> logVec);
    string getPureTime(string time);

private:
    int logId;
    string moduleName;
    string levelName;
    string nowTime;
    string content;
    string getTime();
    long long pureTime;
};
