#include"card_service.h"

void addCard() {
	Card card = initCard();
	char cCard[100], temp[100];
	printf("请输入卡号（长度为1-18）：");
	scanf_s("%s", &card.cNum, 18);
	printf("请输入密码（长度为1-8）：");
	scanf_s("%s", &card.cPwd, 8);
	printf("请输入开卡金额：");
	scanf_s("%f", &card.fBalance);
	printf("\n------添加的卡信息如下------\n");
	printf("卡号\t密码\t状态\t开卡金额\n");
	printf("%s\t%s\t%d\t%.1f\n\n", card.cNum, card.cPwd, card.iStatus, card.fBalance);
	cardToString(card, cCard);
	FILE *fp;
	errno_t err;
	if ((err = fopen_s(&fp, CARD_FILE_DIR, "a+") != 0)) {
		printf("添加时打开文件失败\n\n");
		return;
	}
	if (fgets(temp, 100, fp) == NULL)
		fputs("卡号\t\t密码\t\t状态\t开卡时间\t\t\t截止日期\t\t\t最后使用时间\t\t累计金额\t使用次数\t余额\t\t删除标识\n", fp);
	fclose(fp);
	if (searchCard(card.cNum, 0) == 1)
		printf("该卡号已存在\n\n");
	else {
		fopen_s(&fp, CARD_FILE_DIR, "a+");
		fputs(cCard, fp);
	}

	fclose(fp);
}

int searchCard(char *cNum,int isPrint) {
	char cCard[100];
	Card card;
	FILE *fp;
	errno_t err;
	int isFind = 0;
	if ((err = fopen_s(&fp, CARD_FILE_DIR, "r") != 0)) {
		printf("搜索时打开文件失败\n\n");
		return 0;
	}
	//读掉第一行
	fgets(cCard, 100, fp);
	while (fgets(cCard, 100, fp) != NULL) {
		card = stringToCard(cCard);
		char tStart[20], tEnd[20], tLast[20];
		if (strcmp(card.cNum, cNum) == 0) {
			timeToString(card.tStart, tStart);
			timeToString(card.tEnd, tEnd);
			if ((int)card.tLast == 0) strcpy_s(tLast, 20, "0\t\t");
			else timeToString(card.tLast, tLast);
			if (isPrint == 1) {
				if (card.iDel == 1) {
					printf("该卡已被删除\n\n");
					break;
				}
				printf("卡号\t\t密码\t\t状态\t开卡时间\t\t\t截止日期\t\t\t\n");
				printf("%s\t\t%s\t\t%d\t%s\t\t%s\n", card.cNum, card.cPwd, card.iStatus, tStart, tEnd);
				printf("最后使用时间\t累计金额\t使用次数\t余额\t\t删除标识\n");
				printf("%s%f\t%d\t\t%f\t%d\n", tLast, card.fTotalUse, card.iUseCount, card.fBalance, card.iDel);
			}
			isFind = 1;
			break;
		}
	}
	if (isPrint == 1)
		if (feof(fp))
			printf("未找到该卡\n\n");
	fclose(fp);
	return isFind;
}

void deleteCard(char *cNum) {
	char cCard[200];
	Card card;
	FILE *fp1,*fp2;
	errno_t err;
	int isDel = 0;
	if ((err = fopen_s(&fp1, CARD_FILE_DIR, "r+") != 0)) {
		printf("删除时打开失败\n\n");
		return;
	}
	//读掉第一行
	fgets(cCard, 200, fp1);
	while (fgets(cCard, 200, fp1) != NULL) {
		card = stringToCard(cCard);
		if (strcmp(card.cNum, cNum) == 0) {
			if (card.iDel == 1) {
				isDel = 1;
				break;
			}
			break;
		}
	}

	if (feof(fp1)) {
		printf("未找到该卡\n\n");
		fclose(fp1);
		return;
	}
	else if (isDel == 1) {
		printf("此卡已删除\n\n");
		fclose(fp1);
		return;
	}

	if ((err = fopen_s(&fp2, "temp.txt", "w") != 0)) {
		printf("打开失败\n\n");
		return;
	}
	fputs("卡号\t\t密码\t\t状态\t开卡时间\t\t\t截止日期\t\t\t最后使用时间\t\t累计金额\t使用次数\t余额\t\t删除标识\n", fp2);
	//读掉第一行
	fseek(fp1, 0L,SEEK_SET);
	fgets(cCard, 200, fp1);
	while (fgets(cCard, 1000, fp1) != NULL) {
		card = stringToCard(cCard);
		if (strcmp(card.cNum, cNum) == 0) {
			card.iDel = 1;
			card.tLast = getTime();
			cardToString(card, cCard);
		}
		fputs(cCard, fp2);
	}
	
	fclose(fp1);
	fclose(fp2);

	if ((err = fopen_s(&fp1, CARD_FILE_DIR, "w+") != 0)) {
		printf("打开失败\n\n");
		return;
	}
	if ((err = fopen_s(&fp2, "temp.txt", "r") != 0)) {
		printf("打开失败\n\n");
		return;
	}
	strcpy_s(cCard, 100, "");
	while (!feof(fp2)) {
		fgets(cCard, sizeof(cCard), fp2);
		fprintf(fp1, "%s", cCard);
		strcpy_s(cCard, 100, "");
	}
	fclose(fp1);
	fclose(fp2);
	printf("删除成功\n\n");
}

void updateCard(Card card) {
	char cCard[100];
	FILE *fp1,*fp2;
	errno_t err;
	Card card1;
	if ((err = fopen_s(&fp1, CARD_FILE_DIR, "r") != 0)) {
		printf("修改时打开文件失败\n\n");
		return;
	}
	if ((err = fopen_s(&fp2, "temp.txt", "w+") != 0)) {
		printf("打开缓存文件失败\n\n");
		return;
	}

	//将该卡信息更新后写入temp
	fputs("卡号\t\t密码\t\t状态\t开卡时间\t\t\t截止日期\t\t\t最后使用时间\t\t累计金额\t使用次数\t余额\t\t删除标识\n", fp2);
	fgets(cCard, 1000, fp1);
	while (fgets(cCard, 1000, fp1) != NULL) {
		card1 = stringToCard(cCard);
		if (strcmp(card.cNum, card1.cNum) == 0) {
			cardToString(card, cCard);
		}
		fputs(cCard, fp2);
	}

	fclose(fp1);
	fclose(fp2);

	if ((err = fopen_s(&fp2, "temp.txt", "r") != 0)) {
		printf("打开失败\n\n");
		return;
	}
	if ((err = fopen_s(&fp1, CARD_FILE_DIR, "w") != 0)) {
		printf("修改时打开文件失败\n\n");
		return;
	}

	while (fgets(cCard, sizeof(cCard), fp2)!=NULL) {
		fprintf(fp1, "%s", cCard);
	}

	fclose(fp1);
	fclose(fp2);
}





