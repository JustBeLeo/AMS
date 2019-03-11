#include "billing_service.h"

void Login(LinkedLoginInfo* head) {
	LoginInfo info;
	char cNum[18], cPwd[8];

	printf("请输入卡名:");
	scanf_s("%s", cNum, sizeof(cNum));
	printf("请输入密码:");
	scanf_s("%s", cPwd, sizeof(cPwd));
	FILE *fp;
	char cCard[100];
	Card card;
	errno_t err;
	if ((err = fopen_s(&fp, CARD_FILE_DIR, "a+") != 0)) {
		printf("上机时打开文件失败\n\n");
		return;
	}
	fgets(cCard, 100, fp);
	while (fgets(cCard, 100, fp) != NULL) {
		card = stringToCard(cCard);
		if (strcmp(card.cNum, cNum) == 0) {
			if (strcmp(card.cPwd, cPwd) != 0) {
				printf("密码错误\n\n");
			}
			else if (card.iStatus != 0) {
				if (card.iStatus == 1) printf("该卡正在上机\n\n");
				if (card.iStatus == 2) printf("该卡已注销\n\n");
				if (card.iStatus == 3) printf("该卡已失效\n\n");
			}
			else if (card.fBalance <= 0)
				printf("余额不足\n\n");
			else {
				strcpy_s(info.cCardName,18, cNum);
				info.fBalance = card.fBalance;
				info.tStart = getTime();
				card.iUseCount++;
				card.iStatus = 1;
				fclose(fp);
				updateCard(card);
				doLogin(head, info);
				printf("上机成功！\n\n");
			}
			if(fp!=NULL)
				fclose(fp);
			break;
		}

	}
}

void Settle(LinkedLoginInfo* head) {
	char cNum[18], cPwd[8];
	FILE *fp;
	char cCard[100];
	Card card;
	errno_t err;
	SettleInfo info;

	printf("请输入卡名:");
	scanf_s("%s", cNum, sizeof(cNum));
	printf("请输入密码:");
	scanf_s("%s", cPwd, sizeof(cPwd));

	if ((err = fopen_s(&fp, CARD_FILE_DIR, "a+") != 0)) {
		printf("添加时打开文件失败\n\n");
		return;
	}

	fgets(cCard, 100, fp);
	while (fgets(cCard, 100, fp) != NULL) {
		card = stringToCard(cCard);
		if (strcmp(card.cNum, cNum) == 0) {
			if (strcmp(card.cPwd, cPwd) != 0) {
				printf("密码错误\n\n");
			}
			else if (card.iStatus != 1) {
				printf("该卡目前未在上机\n\n");
			}
			else {
				strcpy_s(info.cCardName, 18, cNum);
				info.tStart = getLoginTime(head, cNum);
				info.tEnd = card.tEnd = getTime();
				info.fAmount = (float)((int)info.tEnd - (int)info.tStart)*0.00000000027;
				info.fBalance = card.fBalance - info.fAmount;
				if (info.fBalance <= 0) {
					printf("%f", info.fAmount);
					printf("余额不足请充值!\n\n");
					return;
				}
				fclose(fp);
				card.fBalance = info.fBalance;
				card.fTotalUse += info.fAmount;
				updateCard(card);
				printf("下机成功！\n\n");
			}
			if (fp != NULL)
				fclose(fp);
			break;
		}

	}
}