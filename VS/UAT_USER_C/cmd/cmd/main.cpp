#include <windows.h>
#include <iostream>

int main()
{
	int a = 0;
	//std::cout << R"(UAT环境输入1,用户环境输入2,使用有线网卡访问UAT输入3,恢复有线网卡内网访问输入4：)";
	std::cout << R"(UAT环境输入1,用户环境输入2：)";
	std::cin >> a;
	std::cout << R"(请稍等......)" << std::endl;
	if (a == 1)
	{
		system(R"("netsh interface ip set dnsservers name="WLAN" source=dhcp >nul")");
		std::cout << R"(已配置为UAT环境！)";
	}
	else if (a == 2)
	{
		system(R"("netsh interface ip set dnsservers name="WLAN" static 4.2.2.1 primary >nul")");
		system(R"("netsh interface ip add dns "WLAN" 4.2.2.2 index=2 >nul")");
		std::cout << R"(已配置为用户环境！)";
	}
	/*else if (a == 3)
	{
		system(R"("netsh interface ip set dnsservers name="以太网" static 52.83.74.116 primary >nul")");
		system(R"("netsh interface ip add dns "以太网" 172.31.1.1 index=2 >nul")");
		std::cout << R"(已配置为使用有线网卡访问UAT！)";
	}
	else if (a == 4)
	{
		system(R"("netsh interface ip set dnsservers name="以太网" static 10.20.193.2 primary >nul")");
		system(R"("netsh interface ip add dns "以太网" 172.31.1.1 index=2 >nul")");
		std::cout << R"(已恢复有线网卡内网访问！)";
	}*/
	else
	{
		std::cout << R"(您的输入有误！)";
	}
	std::cout << std::endl;
	system(R"("pause")");

	return 0;
}