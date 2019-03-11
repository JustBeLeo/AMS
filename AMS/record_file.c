#include "record_file.h"

void recharge()
{
	char cCard[100],cNum[18],cPwd[8];
	Card card;
	FILE *fp;
	errno_t err;
	float amount;
	int isFind = 0;
	printf("������Ҫ��ֵ�Ŀ���:");
	scanf_s("%s", cNum, sizeof(cNum));

	if ((err = fopen_s(&fp, CARD_FILE_DIR, "r") != 0)) {
		printf("CARD_FILE��ʧ��\n\n");
		return 0;
	}
	//������һ��
	fgets(cCard, 100, fp);
	while (fgets(cCard, 100, fp) != NULL) {
		card = stringToCard(cCard);
		char tStart[20], tEnd[20], tLast[20];
		if (strcmp(card.cNum, cNum) == 0) {
			isFind = 1;
			printf("����������:");
			scanf_s("%s", cPwd, sizeof(cPwd));
			if (strcmp(card.cPwd, cPwd) == 0) {
				printf("�������ֵ��");
				scanf_s("%f", &amount);
				card.fBalance += amount;
				fclose(fp);
				updateCard(card);
				printf("��ֵ�ɹ���\n\n");
			}
			else {
				printf("�������\n\n");
			}
		}
	}
	if (isFind == 0) {
		printf("δ�ҵ��ÿ�\n\n");
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
	printf("������Ҫ�˷ѵĿ���:");
	scanf_s("%s", cNum, sizeof(cNum));

	if ((err = fopen_s(&fp, CARD_FILE_DIR, "r") != 0)) {
		printf("CARD_FILE��ʧ��\n\n");
		return 0;
	}
	//������һ��
	fgets(cCard, 100, fp);
	while (fgets(cCard, 100, fp) != NULL) {
		card = stringToCard(cCard);
		char tStart[20], tEnd[20], tLast[20];
		if (strcmp(card.cNum, cNum) == 0) {
			isFind = 1;
			printf("����������:");
			scanf_s("%s", cPwd, sizeof(cPwd));
			if (strcmp(card.cPwd, cPwd) == 0) {
				printf("�������:%.3f\n",card.fBalance);
				printf("�����Ҫ�˷�������yes��ȷ��\n");
				scanf_s("%s", temp,sizeof(temp));
				{
					if (strcmp(temp, "yes") == 0) {
						card.iDel = 1;
						card.fBalance = 0;
						fclose(fp);
						updateCard(card);
						printf("�ɹ��˷ѣ�\n\n");
						return;
					}
					else {
						printf("��ȡ������\n\n");
						fclose(fp);
						return;
					}
				}
				
			}
			else {
				printf("�������\n\n");
				fclose(fp);
				return;
			}
		}
	}
	if (isFind == 0) {
		printf("δ�ҵ��ÿ�\n\n");
	}
	fclose(fp);
}
