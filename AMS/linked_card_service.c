#include"linked_card_service.h"
//��ʼ��
LinkedCard* initLinkedCard(){
	LinkedCard* ptr = (LinkedCard*)malloc(sizeof(LinkedCard));
	ptr->next = NULL;
	return ptr;
}
//��ӿ�
void addLinkedCard(LinkedCard* head) {
	LinkedCard* node = (LinkedCard*)malloc(sizeof(LinkedCard));
	LinkedCard* ptr = head;
	node->card = initCard();
	printf("�����뿨�ţ�����Ϊ1-18����");
	scanf_s("%s", &node->card.cNum, 18);
	printf("���������루����Ϊ1-8����");
	scanf_s("%s", &node->card.cPwd, 8);
	printf("�����뿪����");
	scanf_s("%f", &node->card.fBalance);
	printf("\n------��ӵĿ���Ϣ����------\n");
	printf("����\t����\t״̬\t�������\n");
	printf("%s\t%s\t%d\t%.1f\n\n", node->card.cNum, node->card.cPwd, node->card.iStatus, node->card.fBalance);
	node->next = NULL;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = node;
	printf("��ӳɹ�\n\n");
}
//ɾ����
void deleteLinkedCard(LinkedCard* head) {
	LinkedCard* ptr = head;
	LinkedCard* ptr1 = ptr;
	int isFind = 0;
	char cNum[20];
	printf("������Ҫɾ���Ŀ��ţ�");
	scanf_s("%s", cNum, 20);
	while (ptr != NULL) {
		if (strcmp(ptr->card.cNum, cNum) == 0) {
			ptr1->next = ptr->next;
			ptr->next = NULL;
			free(ptr);
			printf("ɾ���ɹ���\n\n");
			break;
		}
		ptr1 = ptr;
		ptr = ptr->next;
	}
	if (ptr == NULL)printf("δ�ҵ��ÿ�����\n\n");
}
//���ҿ�
int searchLinkedCard(LinkedCard* head, int isPrint) {
	LinkedCard* ptr = head;
	int isFind = 0;
	char cNum[20];
	printf("������Ҫ���ҵĿ��ţ�");
	scanf_s("%s", cNum, 20);
	while (ptr != NULL) {
		if (strcmp(ptr->card.cNum, cNum) == 0) {
			if (isPrint == TRUE) {
				char tStart[20], tEnd[20], tLast[20];
				timeToString(ptr->card.tStart, tStart);
				timeToString(ptr->card.tEnd, tEnd);
				if ((int)ptr->card.tLast == 0) strcpy_s(tLast, 20, "0\t\t");
				else timeToString(ptr->card.tLast, tLast);
				printf("����\t\t����\t\t״̬\t����ʱ��\t\t\t��ֹ����\t\t\t\n");
				printf("%s\t\t%s\t\t%d\t%s\t\t%s\n", ptr->card.cNum, ptr->card.cPwd, ptr->card.iStatus, tStart, tEnd);
				printf("���ʹ��ʱ��\t�ۼƽ��\tʹ�ô���\t���\t\tɾ����ʶ\n");
				printf("%s%f\t%d\t\t%f\t%d\n", tLast, ptr->card.fTotalUse, ptr->card.iUseCount, ptr->card.fBalance, ptr->card.iDel);
			}
			isFind = 1;
			break;
		}
		ptr = ptr->next;
	}
	if (ptr == NULL)printf("δ�ҵ��ÿ�����\n\n");
	return isFind;
}