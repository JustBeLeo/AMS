#include "billing_service.h"

void Login() {
	LoginInfo info;
	char cNum[18], cPwd[8];
	int tag = 0;		//����Ƿ��ҵ��˿�
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
			tag = 1;
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
	if (tag == 0) {
		printf("�ÿ�������\n\n");
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

void QueryConsume()
{
	char cNum[18];
	FILE *fp;
	char temp[100],tUse1[20],tUse2[20];
	errno_t err;
	Use mUse;
	int tag = 0;		//���λ
	printf("�����뿨��:");
	scanf_s("%s", cNum, sizeof(cNum));
	if ((err = fopen_s(&fp, SETTLE_FILE_DIR, "r") != 0)) {
		printf("SETTLE_FILE�ļ���ռ��\n\n");
		return;
	}
	while ((fgets(temp, 100, fp)) != NULL) {
		sscanf_s(temp, "%s %s %s %f", mUse.cCardName,sizeof(mUse.cCardName),tUse1,sizeof(tUse1),tUse2,sizeof(tUse2), &mUse.fUse);
		if (strcmp(mUse.cCardName, cNum) == 0) {
			printf("%s��%s������:%.3fԪ\n", mUse.cCardName, tUse1, mUse.fUse);
			tag = 1;
		}
	}
	if (tag==0) {
		printf("δ�ҵ���¼\n\n");
	}
	fclose(fp);
}

void TotalUse()
{
	char date[18];
	FILE *fp;
	float total = 0;
	char temp[100], tUse1[20], tUse2[20];
	errno_t err;
	Use mUse;
	int tag = 0;		//���λ
	printf("����������(xxxx-xx-xx):");
	scanf_s("%s", date, sizeof(date));
	if ((err = fopen_s(&fp, SETTLE_FILE_DIR, "r") != 0)) {
		printf("SETTLE_FILE�ļ���ռ��\n\n");
		return;
	}
	while ((fgets(temp, 100, fp)) != NULL) {
		sscanf_s(temp, "%s %s %s %f", mUse.cCardName, sizeof(mUse.cCardName), tUse1, sizeof(tUse1), tUse2, sizeof(tUse2), &mUse.fUse);
		if (strcmp(tUse1, date) == 0) {
			total += mUse.fUse;
		}
	}
	printf("%s����Ӫҵ��Ϊ%.3f\n\n",date,total);
	fclose(fp);
}
