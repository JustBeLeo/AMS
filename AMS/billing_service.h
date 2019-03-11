#pragma once
#include "global.h"
#include "billing_file.h"
#include "card_file.h"
#include "card_service.h"

//上机
void Login();
//下机
void Settle();
//查询消费情况
void QueryConsume();
//统计消费总额
void TotalUse();