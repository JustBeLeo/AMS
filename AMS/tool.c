#include"tool.h"

void timeToString(time_t t,char* pBuf) {
	struct tm *tm = (struct tm*)malloc(sizeof(struct tm));   //tm�ṹָ��
	localtime_s(tm, &t);   //��ȡ�������ں�ʱ��
	strftime(pBuf, 20, "%Y-%m-%d %H:%M", tm);
}

time_t stringToTime(char* pTime) {
	struct tm t1;
	time_t time1;
	sscanf_s(pTime, "%d-%d-%d %d:%d", &t1.tm_year, &t1.tm_mon, &t1.tm_mday, &t1.tm_hour, &t1.tm_min);
	t1.tm_year -= 1900;
	t1.tm_mon -= 1;
	t1.tm_sec = 0;
	t1.tm_isdst = -1;

	time1 = mktime(&t1);
	return time1;
}

time_t getTime() {
	time_t now;  //����time_t���ͱ���
	time(&now);      //��ȡϵͳ���ں�ʱ��
	return now;
}