// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<ctime>
#include<iostream>
#include<iomanip>
#include<sstream>
#include<string>
#include<cassert>
#include<cinttypes>

//#define PRIu64 "llu"
int main()
{
	std::time_t t = std::time(nullptr);
	std::tm tm = *std::localtime(&t);
	std::ostringstream content;
	content << std::put_time(&tm, "%FT%T:000");
	std::string strtime = content.str();
	std::cout << "time: " << strtime << '\n';
	uint64_t value = 3445;
	char buf[64] = { 0 };
	snprintf(buf, sizeof(buf), "%" PRIu64, value);
	//snprintf(buf, sizeof(buf), "%s", PRIu64);
	
	//auto a = 1;
	//assert(a==2);
	//std::time_t t = std::time(NULL);
	//char mbstr[100];
	//if (std::strftime(mbstr, sizeof(mbstr), "%FT%T:000", std::localtime(&t))) {
	//	std::cout << mbstr << '\n';
	//}
	//std::cout.imbue(std::locale("ru_RU.utf8"));
	//std::cout << "ru_RU: " << std::put_time(&tm, "%c %Z") << '\n';
	//std::cout.imbue(std::locale("ja_JP.utf8"));
	//std::cout << "ja_JP: " << std::put_time(&tm, "%c %Z") << '\n';
    return 0;
}

