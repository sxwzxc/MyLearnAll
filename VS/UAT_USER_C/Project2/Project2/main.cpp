#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <windows.h>
#include  "shellapi.h"

VOID ManagerRun(LPCWSTR exe, LPCWSTR param, INT nShow = SW_SHOW)
{ //注意：会跳出提示。
	SHELLEXECUTEINFO ShExecInfo;
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = reinterpret_cast<LPCWSTR>("runas");
	ShExecInfo.lpFile = exe;
	ShExecInfo.lpParameters = param;
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = nShow;
	ShExecInfo.hInstApp = NULL;
	BOOL ret = ShellExecuteEx(&ShExecInfo);
	//等不及了，不等了。
	//CloseHandle(ShExecInfo.hProcess);
	return;
}

BOOL IsRunAsAdministrator()
{
    BOOL fIsRunAsAdmin = FALSE;
    DWORD dwError = ERROR_SUCCESS;
    PSID pAdministratorsGroup = NULL;

    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    if (!AllocateAndInitializeSid(
        &NtAuthority,
        2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0,
        &pAdministratorsGroup))
    {
        dwError = GetLastError();
        goto Cleanup;
    }

    if (!CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin))
    {
        dwError = GetLastError();
        goto Cleanup;
    }

Cleanup:

    if (pAdministratorsGroup)
    {
        FreeSid(pAdministratorsGroup);
        pAdministratorsGroup = NULL;
    }

    if (ERROR_SUCCESS != dwError)
    {
        throw dwError;
    }

    return fIsRunAsAdmin;
}

void ElevateNow()
{
    BOOL bAlreadyRunningAsAdministrator = FALSE;
    try
    {
        bAlreadyRunningAsAdministrator = IsRunAsAdministrator();
    }
    catch (...)
    {

    }
    if (!bAlreadyRunningAsAdministrator)
    {
        WCHAR szPath[MAX_PATH];
        if (GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath)))
        {


            SHELLEXECUTEINFO sei = { sizeof(sei) };

            sei.lpVerb = L"runas";
            sei.lpFile = szPath;
            sei.hwnd = NULL;
            sei.nShow = SW_SHOWDEFAULT;

            if (!ShellExecuteEx(&sei))
            {
                DWORD dwError = GetLastError();
                if (dwError == ERROR_CANCELLED)
                    //Annoys you to Elevate it LOL
                    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ElevateNow, 0, 0, 0);
            }
        }

    }
    else
    {
        ///Code
    }
}

void GainAdminPrivileges(LPCWSTR strApp) {
    SHELLEXECUTEINFO execinfo;
    memset(&execinfo, 0, sizeof(execinfo));
    execinfo.lpFile = strApp;
    //execinfo.cbSize = sizeof(execinfo);
    execinfo.lpVerb = LPCWSTR("runas");
   // execinfo.fMask = SEE_MASK_NO_CONSOLE;
    execinfo.nShow = SW_NORMAL;

    int b=ShellExecuteEx(&execinfo);
    int c = b;
    c++;
}
bool IsProcessRunAsAdmin()
{
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    PSID AdministratorsGroup;
    BOOL b = AllocateAndInitializeSid(
        &NtAuthority,
        2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0,
        &AdministratorsGroup);
    if (b)
    {
        CheckTokenMembership(NULL, AdministratorsGroup, &b);
        FreeSid(AdministratorsGroup);
    }
    return b == TRUE;
}
short GetAdmin(LPCWSTR Param, int Showcmd)
{
    if (IsProcessRunAsAdmin())
        return 0;
    TCHAR Path[MAX_PATH];
    ZeroMemory(Path, MAX_PATH);
    ::GetModuleFileName(NULL, Path, MAX_PATH);           //获取程序路径
    HINSTANCE res;
    res = ShellExecute(NULL, LPCWSTR("runas"), Path, Param, NULL, Showcmd);
    if ((int)res > 32)
        return 1;
    else
        return 0;
}

int main(int argc, char* argv[])
{
    GetAdmin(NULL, 0);
    /* 字符串传入 */
   // ShellExecute(hwnd, lpOperation, "path", lpParameters, lpDictory, nShowCmd);


    /* FILE* fp = fopen("administratortest.txt", "a+");
    if (fp == NULL)
    {
        return 0;
    }

   fprintf(fp, "administratortest:%d.\n", 1);
    fclose(fp);*/

    //获取管理员权限
    WCHAR path[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, path, MAX_PATH);
    GainAdminPrivileges(path);

    FILE* fp = fopen("administratortest.txt", "a+");
    if (fp == NULL)
    {
        return 0;
    }

    fprintf(fp, "administratortest:%d.\n", 2);
    fclose(fp);
    return 0;
}