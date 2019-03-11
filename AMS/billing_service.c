#include "billing_service.h"

void Login() {
	LoginInfo info;
	char cNum[18], cPwd[8];

	printf("�����뿨��:");
	scanf_s("%s", cNum, sizeof(cNum));
	printf("����������:");
	scanf_s("%s", cPwd, sizeof(cPwd));
	FILE *fp;
	char cCard[100];
	Card card;
	errno_t err;
	if ((err = fopen_s(&fp, CARD_FILE_DIR, "a+") != 0)) {
		printf("CARD_FILE�ļ���ռ��\n\n");
		return;
	}
	fgets(cCard, 100, fp);
	while (fgets(cCard, 100, fp) != NULL) {
		card = stringToCard(cCard);
		if (strcmp(card.cNum, cNum) == 0) {
			if (strcmp(card.cPwd, cPwd) != 0) {
				printf("�������\n\n");
			}
			else if (card.iStatus != 0) {
				if (card.iStatus == 1) printf("�ÿ������ϻ�\n\n");
				if (card.iStatus == 2) printf("�ÿ���ע��\n\n");
				if (card.iStatus == 3) printf("�ÿ���ʧЧ\n\n");
			}
			else if (card.fBalance <= 0)
				printf("����\n\n");
			else {
				strcpy_s(info.cCardName,18, cNum);
				info.fBalance = card.fBalance;
				info.tStart = getTime();
				card.iUseCount++;
				card.iStatus = 1;
				fclose(fp);
				updateCard(card);
				LoginFile(info);
				printf("�ϻ��ɹ���\n\n");
			}
			if(fp!=NULL)
				fclose(fp);
			break;
		}

	}
}

void Settle() {
	char cNum[18], cPwd[8];
	FILE *fp;
	char cCard[100];
	Card card;
	errno_t err;
	SettleInfo* info = (SettleInfo*)malloc(sizeof(SettleInfo));
	printf("�����뿨��:");
	scanf_s("%s", cNum, sizeof(cNum));
	printf("����������:");
	scanf_s("%s", cPwd, sizeof(cPwd));

	if ((err = fopen_s(&fp, CARD_FILE_DIR, "a+") != 0)) {
		printf("CARD_FILE�ļ���ռ��\n\n");
		return;
	}

	fgets(cCard, 100, fp);
	while (fgets(cCard, 100, fp) != NULL) {
		card = stringToCard(cCard);
		if (strcmp(card.cNum, cNum) == 0) {
			if (strcmp(card.cPwd, cPwd) != 0) {
				printf("�������\n\n");
			}
			else if (card.iStatus != 1) {
				printf("�ÿ�Ŀǰδ���ϻ�\n\n");
			}
			else {
				SettleFile(cNum,info);
				if (info->fBalance < 0) {
					return;
				}
				fclose(fp);
				card.fBalance = info->fBalance;
				card.fTotalUse += info->fAmount;
				card.iStatus = 0;
				card.tLast = info->tEnd;
				updateCard(card);
			}
			if (fp != NULL)
				fclose(fp);
			break;
		}

	}
}