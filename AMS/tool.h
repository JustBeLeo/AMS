#pragma once
#include"global.h"

//��ʱ��ת���ַ���
void timeToString(time_t t, char* pBuf);

//���ַ���ת��ʱ��
time_t stringToTime(char* pTime);

//��ȡ��ǰʱ��
time_t getTime();