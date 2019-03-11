#pragma once
#include "global.h"
#include "billing_file.h"
#include "card_file.h"
#include "card_service.h"

//上机
void Login(LinkedLoginInfo* head);
//下机
void Settle(LinkedLoginInfo* head);
