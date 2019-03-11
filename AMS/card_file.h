#pragma once
#include"global.h"

//卡信息
typedef struct Card {
	char cNum[18];		//卡号
	char cPwd[8];		//密码
	int iStatus;		//状态 0-未上机 1-正在上机	2-已注销 3-失效
	time_t tStart;		//开卡时间
	time_t tEnd;		//截止日期
	time_t tLast;		//最后使用时间
	float fTotalUse;	//累计金额
	int iUseCount;		//使用次数
	float fBalance;		//余额
	int iDel;			//删除标识 0-未删除 1-已删除
}Card;

//初始化卡信息
Card initCard();

//从类转成字符串
void cardToString(Card card, char* cCard);

//从字符串转成类
Card stringToCard(char *ptr);

