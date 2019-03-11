#pragma once
#include"global.h"
typedef struct Billing {
	char cCardName[18];	//卡号
	time_t tStart;		//上机时间
	time_t tEnd;		//下机时间
	float fAmount;		//消费金额
	int iStatus;		//消费状态 0-未结算 1-已结算
	int iDel;			//删除状态 0-未删除 1-已删除
}Billing;

typedef struct LoginInfo {
	char cCardName[18];	//卡号
	time_t tStart;		//上机时间
	float fBalance;		//余额
}LoginInfo;

typedef struct LinkedLoginInfo {
	LoginInfo info;
	struct LinkedLoginInfo* next;
}LinkedLoginInfo;

typedef struct SettleInfo {
	char cCardName[18];	//卡号
	time_t tStart;		//上机时间
	time_t tEnd;		//下机时间
	float fAmount;		//消费金额
	float fBalance;		//余额
}SettleInfo;

//将账单存入文件中
void bill_to_file(Billing ptr);

//将上机信息写入链表
void doLogin(LinkedLoginInfo* head,LoginInfo info);
//获取上机时间
time_t getLoginTime(LinkedLoginInfo* head, char *cCardName);
//将下机信息和上机信息合并存入billing



