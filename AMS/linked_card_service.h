#pragma once
#include"card_file.h"
typedef struct cardNode {
	Card card;
	struct cardNode* next;
}LinkedCard;

//��ʼ��
LinkedCard* initLinkedCard();
//��ӿ�
void addLinkedCard(LinkedCard* head);
//ɾ����
void deleteLinkedCard(LinkedCard* head);
//���ҿ�
int searchLinkedCard(LinkedCard* head, int isPrint);