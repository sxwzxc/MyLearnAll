#include <windows.h>
#include <iostream>

int main()
{
	int a = 0;
	//std::cout << R"(UAT��������1,�û���������2,ʹ��������������UAT����3,�ָ���������������������4��)";
	std::cout << R"(UAT��������1,�û���������2��)";
	std::cin >> a;
	std::cout << R"(���Ե�......)" << std::endl;
	if (a == 1)
	{
		system(R"("netsh interface ip set dnsservers name="WLAN" source=dhcp >nul")");
		std::cout << R"(������ΪUAT������)";
	}
	else if (a == 2)
	{
		system(R"("netsh interface ip set dnsservers name="WLAN" static 4.2.2.1 primary >nul")");
		system(R"("netsh interface ip add dns "WLAN" 4.2.2.2 index=2 >nul")");
		std::cout << R"(������Ϊ�û�������)";
	}
	/*else if (a == 3)
	{
		system(R"("netsh interface ip set dnsservers name="��̫��" static 52.83.74.116 primary >nul")");
		system(R"("netsh interface ip add dns "��̫��" 172.31.1.1 index=2 >nul")");
		std::cout << R"(������Ϊʹ��������������UAT��)";
	}
	else if (a == 4)
	{
		system(R"("netsh interface ip set dnsservers name="��̫��" static 10.20.193.2 primary >nul")");
		system(R"("netsh interface ip add dns "��̫��" 172.31.1.1 index=2 >nul")");
		std::cout << R"(�ѻָ����������������ʣ�)";
	}*/
	else
	{
		std::cout << R"(������������)";
	}
	std::cout << std::endl;
	system(R"("pause")");

	return 0;
}