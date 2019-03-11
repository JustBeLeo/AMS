#pragma once
#include"global.h"

//将时间转成字符串
void timeToString(time_t t, char* pBuf);

//将字符串转成时间
time_t stringToTime(char* pTime);

//获取当前时间
time_t getTime();