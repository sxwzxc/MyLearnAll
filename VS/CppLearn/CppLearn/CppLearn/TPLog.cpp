#include "TPLog.h"
TPLog::TPLog()
{
    // cout << endl << "============================" << endl <<
    // "TPLog类已开始创建"<<endl;
}

TPLog::~TPLog()
{
    // cout << endl << "============================" << endl << "TPLog类已结束"
    // << endl;
}

long long TPLog::UsePureTime()
{
    return TPLog::pureTime;
}

int TPLog::GetId()
{
    return logId;
}

string TPLog::getTime()
{
    SYSTEMTIME systime;
    GetLocalTime(&systime);
    char temp[200];
    sprintf_s(temp, 200, "%d-%02d-%02d %02d:%02d:%02d", systime.wYear,
              systime.wMonth, systime.wDay, systime.wHour, systime.wMinute,
              systime.wSecond);
    return temp;
}

void TPLog::showLog()
{
    cout << TPLog::logId << " | ";
    cout << TPLog::moduleName << " | ";
    cout << TPLog::levelName << " | ";
    cout << TPLog::nowTime << " | ";
    cout << TPLog::content << endl;
}

void TPLog::createLog(int logId, string modulename, string levelname,
                      string content)
{
    TPLog::logId = logId;
    TPLog::levelName = levelname;
    TPLog::nowTime = getTime();
    long long temp = -1;
    try
    {
        temp = std::stoll(getPureTime(TPLog::nowTime));
    }
    catch (...)
    {
    }
    TPLog::pureTime = temp;
    try
    {
        temp = -1;
        temp = stoi(modulename);
    }
    catch (...)
    {
    }
    Sleep(200);

    switch (temp)
    {
        case 0:
            TPLog::moduleName = "Album";
            switch (rand() % 4)
            {
                case 0:
                    TPLog::content = "Album crashed !";
                case 1:
                    TPLog::content = "Album memory leaks !";
                case 2:
                    TPLog::content = "Album is running in a good state !";
                case 3:
                    TPLog::content = "Album is busy !";
                default:
                    break;
            }
            break;
        case 1:
            TPLog::moduleName = "Player";
            switch (rand() % 4)
            {
                case 0:
                    TPLog::content = "Player crashed !";
                case 1:
                    TPLog::content = "Player is too busy !";
                case 2:
                    TPLog::content = "Player is running well !";
                case 3:
                    TPLog::content = "Player restarted !";
                default:
                    break;
            }
            break;
        case 2:
            TPLog::moduleName = "Comm";
            switch (rand() % 4)
            {
                case 0:
                    TPLog::content = "Comm crashed !";
                case 1:
                    TPLog::content = "Comm memory leaks !";
                case 2:
                    TPLog::content = "Comm timeout !";
                case 3:
                    TPLog::content = "Comm is busy !";
                default:
                    break;
            }
            break;
        case 3:
            TPLog::moduleName = "Message";
            switch (rand() % 4)
            {
                case 0:
                    TPLog::content = "Message crashed !";
                case 1:
                    TPLog::content = "Message is updating !";
                case 2:
                    TPLog::content = "Message is running well !";
                case 3:
                    TPLog::content = "Message is busy !";
                default:
                    break;
            }
            break;
        case 4:
            TPLog::moduleName = "Device";
            switch (rand() % 4)
            {
                case 0:
                    TPLog::content = "Device crashed !";
                case 1:
                    TPLog::content = "Device is running well !";
                case 2:
                    TPLog::content = "Device encounters an error !";
                case 3:
                    TPLog::content = "Device is restarted !";
                default:
                    break;
            }
            break;
        default:
            TPLog::moduleName = modulename;
            break;
    }

    try
    {
        temp = -1;
        temp = std::stoi(levelname);
    }
    catch (...)
    {
    }
    switch (temp)
    {
        case 0:
            TPLog::levelName = "VERB";
            break;
        case 1:
            TPLog::levelName = "DEBUG";
            break;
        case 2:
            TPLog::levelName = "INFO";
            break;
        case 3:
            TPLog::levelName = "WARN";
            break;
        case 4:
            TPLog::levelName = "ERR";
            break;
        default:
            TPLog::levelName = levelname;
            break;
    }
}

void TPLog::logSort(TPLog *tplogptr)
{
    TPLog *temp = new TPLog;
    for (int i = 0; i < 20; i++)
    {
        for (int j = i; j < 20; j++)
        {
            if (tplogptr[i].GetId() > tplogptr[j].GetId())
            {
                *temp = tplogptr[i];
                tplogptr[i] = tplogptr[j];
                tplogptr[j] = *temp;
            }
        }
    }
    for (int i = 0; i < 20; i++)
    {
        for (int j = i; j < 20; j++)
        {
            if (tplogptr[i].UsePureTime() > tplogptr[j].UsePureTime())
            {
                *temp = tplogptr[i];
                tplogptr[i] = tplogptr[j];
                tplogptr[j] = *temp;
            }
        }
    }
}

void TPLog::logSort(vector<TPLog> logVec)
{
    for (int i = 0; i < 50; i++)
    {
        for (int j = i; j < 20; j++)
        {
            if (logVec[i].GetId() > logVec[j].GetId())
            {
                swap(logVec[i], logVec[j]);
            }
        }
    }
    for (int i = 0; i < 50; i++)
    {
        for (int j = i; j < 50; j++)
        {
            if (logVec[i].UsePureTime() > logVec[j].UsePureTime())
            {
                swap(logVec[i], logVec[j]);
            }
        }
    }
}

string TPLog::getPureTime(string time)
{
    int pos;
    int n;
    string target = " ";
    n = target.size();
    while (time.find(target) != -1)
    {
        pos = time.find(target);
        time = time.erase(pos, n);
    }
    target = "-";
    n = target.size();
    while (time.find(target) != -1)
    {
        pos = time.find(target);
        time = time.erase(pos, n);
    }
    target = ":";
    n = target.size();
    while (time.find(target) != -1)
    {
        pos = time.find(target);
        time = time.erase(pos, n);
    }
    return time;
}
