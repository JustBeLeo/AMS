#include "record_file.h"

void recharge()
{
	char cCard[100],cNum[18],cPwd[8];
	Card card;
	FILE *fp;
	errno_t err;
	float amount;
	int isFind = 0;
	printf("请输入要充值的卡号:");
	scanf_s("%s", cNum, sizeof(cNum));

	if ((err = fopen_s(&fp, CARD_FILE_DIR, "r") != 0)) {
		printf("CARD_FILE打开失败\n\n");
		return 0;
	}
	//读掉第一行
	fgets(cCard, 100, fp);
	while (fgets(cCard, 100, fp) != NULL) {
		card = stringToCard(cCard);
		char tStart[20], tEnd[20], tLast[20];
		if (strcmp(card.cNum, cNum) == 0) {
			isFind = 1;
			printf("请输入密码:");
			scanf_s("%s", cPwd, sizeof(cPwd));
			if (strcmp(card.cPwd, cPwd) == 0) {
				printf("请输入充值金额：");
				scanf_s("%f", &amount);
				card.fBalance += amount;
				fclose(fp);
				updateCard(card);
				printf("充值成功！\n\n");
			}
			else {
				printf("密码错误\n\n");
			}
		}
	}
	if (isFind == 0) {
		printf("未找到该卡\n\n");
	}
	fclose(fp);
}

void refund()
{
	char cCard[100], cNum[18], cPwd[8];
	Card card;
	FILE *fp;
	errno_t err;
	char temp[5];
	int isFind = 0;
	printf("请输入要退费的卡号:");
	scanf_s("%s", cNum, sizeof(cNum));

	if ((err = fopen_s(&fp, CARD_FILE_DIR, "r") != 0)) {
		printf("CARD_FILE打开失败\n\n");
		return 0;
	}
	//读掉第一行
	fgets(cCard, 100, fp);
	while (fgets(cCard, 100, fp) != NULL) {
		card = stringToCard(cCard);
		char tStart[20], tEnd[20], tLast[20];
		if (strcmp(card.cNum, cNum) == 0) {
			isFind = 1;
			printf("请输入密码:");
			scanf_s("%s", cPwd, sizeof(cPwd));
			if (strcmp(card.cPwd, cPwd) == 0) {
				printf("你的余额还有:%.3f\n",card.fBalance);
				printf("你真的要退费吗，输入yes来确定\n");
				scanf_s("%s", temp,sizeof(temp));
				{
					if (strcmp(temp, "yes") == 0) {
						card.iDel = 1;
						card.fBalance = 0;
						fclose(fp);
						updateCard(card);
						printf("成功退费！\n\n");
						return;
					}
					else {
						printf("已取消！！\n\n");
						fclose(fp);
						return;
					}
				}
				
			}
			else {
				printf("密码错误\n\n");
				fclose(fp);
				return;
			}
		}
	}
	if (isFind == 0) {
		printf("未找到该卡\n\n");
	}
	fclose(fp);
}
