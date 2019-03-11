#pragma once
#include"card_file.h"
typedef struct cardNode {
	Card card;
	struct cardNode* next;
}LinkedCard;

//³õÊ¼»¯
LinkedCard* initLinkedCard();
//Ìí¼Ó¿¨
void addLinkedCard(LinkedCard* head);
//É¾³ı¿¨
void deleteLinkedCard(LinkedCard* head);
//²éÕÒ¿¨
int searchLinkedCard(LinkedCard* head, int isPrint);