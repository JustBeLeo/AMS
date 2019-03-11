#include"card_service.h"

void addCard() {
	Card card = initCard();
	char cCard[100], temp[100];
	printf("�����뿨�ţ�����Ϊ1-18����");
	scanf_s("%s", &card.cNum, 18);
	printf("���������루����Ϊ1-8����");
	scanf_s("%s", &card.cPwd, 8);
	printf("�����뿪����");
	scanf_s("%f", &card.fBalance);
	printf("\n------��ӵĿ���Ϣ����------\n");
	printf("����\t����\t״̬\t�������\n");
	printf("%s\t%s\t%d\t%.1f\n\n", card.cNum, card.cPwd, card.iStatus, card.fBalance);
	cardToString(card, cCard);
	FILE *fp;
	errno_t err;
	if ((err = fopen_s(&fp, CARD_FILE_DIR, "a+") != 0)) {
		printf("���ʱ���ļ�ʧ��\n\n");
		return;
	}
	if (fgets(temp, 100, fp) == NULL)
		fputs("����\t\t����\t\t״̬\t����ʱ��\t\t\t��ֹ����\t\t\t���ʹ��ʱ��\t\t�ۼƽ��\tʹ�ô���\t���\t\tɾ����ʶ\n", fp);
	fclose(fp);
	if (searchCard(card.cNum, 0) == 1)
		printf("�ÿ����Ѵ���\n\n");
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
		printf("����ʱ���ļ�ʧ��\n\n");
		return 0;
	}
	//������һ��
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
					printf("�ÿ��ѱ�ɾ��\n\n");
					break;
				}
				printf("����\t\t����\t\t״̬\t����ʱ��\t\t\t��ֹ����\t\t\t\n");
				printf("%s\t\t%s\t\t%d\t%s\t\t%s\n", card.cNum, card.cPwd, card.iStatus, tStart, tEnd);
				printf("���ʹ��ʱ��\t�ۼƽ��\tʹ�ô���\t���\t\tɾ����ʶ\n");
				printf("%s%f\t%d\t\t%f\t%d\n", tLast, card.fTotalUse, card.iUseCount, card.fBalance, card.iDel);
			}
			isFind = 1;
			break;
		}
	}
	if (isPrint == 1)
		if (feof(fp))
			printf("δ�ҵ��ÿ�\n\n");
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
		printf("ɾ��ʱ��ʧ��\n\n");
		return;
	}
	//������һ��
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
		printf("δ�ҵ��ÿ�\n\n");
		fclose(fp1);
		return;
	}
	else if (isDel == 1) {
		printf("�˿���ɾ��\n\n");
		fclose(fp1);
		return;
	}

	if ((err = fopen_s(&fp2, "temp.txt", "w") != 0)) {
		printf("��ʧ��\n\n");
		return;
	}
	fputs("����\t\t����\t\t״̬\t����ʱ��\t\t\t��ֹ����\t\t\t���ʹ��ʱ��\t\t�ۼƽ��\tʹ�ô���\t���\t\tɾ����ʶ\n", fp2);
	//������һ��
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
		printf("��ʧ��\n\n");
		return;
	}
	if ((err = fopen_s(&fp2, "temp.txt", "r") != 0)) {
		printf("��ʧ��\n\n");
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
	printf("ɾ���ɹ�\n\n");
}

void updateCard(Card card) {
	char cCard[100];
	FILE *fp1,*fp2;
	errno_t err;
	Card card1;
	if ((err = fopen_s(&fp1, CARD_FILE_DIR, "r") != 0)) {
		printf("�޸�ʱ���ļ�ʧ��\n\n");
		return;
	}
	if ((err = fopen_s(&fp2, "temp.txt", "w+") != 0)) {
		printf("�򿪻����ļ�ʧ��\n\n");
		return;
	}

	//���ÿ���Ϣ���º�д��temp
	fputs("����\t\t����\t\t״̬\t����ʱ��\t\t\t��ֹ����\t\t\t���ʹ��ʱ��\t\t�ۼƽ��\tʹ�ô���\t���\t\tɾ����ʶ\n", fp2);
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
		printf("��ʧ��\n\n");
		return;
	}
	if ((err = fopen_s(&fp1, CARD_FILE_DIR, "w") != 0)) {
		printf("�޸�ʱ���ļ�ʧ��\n\n");
		return;
	}

	while (fgets(cCard, sizeof(cCard), fp2)!=NULL) {
		fprintf(fp1, "%s", cCard);
	}

	fclose(fp1);
	fclose(fp2);
}





