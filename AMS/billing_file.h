#pragma once
#include"global.h"
#include "rate_file.h"

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

typedef struct Use {
	char cCardName[18];	//卡号
	time_t tUse;	//何时消费
	float fUse;		//消费情况
}Use;

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

//将账单存入中
void bill_to_file(Billing ptr);
//将上机信息写入文件
void LoginFile(LoginInfo info);
//下机，将账单写入文件中
void SettleFile(char* cNum, SettleInfo* sInfo);
//将下机信息和上机信息合并存入billing



