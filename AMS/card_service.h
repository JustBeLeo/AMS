#pragma once
#include"card_file.h"

//��ӿ�
void addCard();
//ɾ����
void deleteCard(char *cNum);
//���ҿ�
int searchCard(char *cNum, int isPrint);
//�޸Ŀ�
void updateCard(Card card);