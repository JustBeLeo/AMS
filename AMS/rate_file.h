#pragma once
#include"global.h"
typedef struct Standard	 {
	//int startTime;		//开始时间
	//int endTime;		//结束时间
	int unit;			//最小计费单元
	float charge;		//每个计费单元的收费
	//int rateType;		//收费类型 0-普通 1-包夜 2-包天
	//int del;			//删除状态 0-未删除 1-已删除
}Standard;

//读取标准
void getStandard(Standard* std, int needPrint);
//修改标准
void changeStandard();
