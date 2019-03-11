#pragma once
#include"global.h"

//����Ϣ
typedef struct Card {
	char cNum[18];		//����
	char cPwd[8];		//����
	int iStatus;		//״̬ 0-δ�ϻ� 1-�����ϻ�	2-��ע�� 3-ʧЧ
	time_t tStart;		//����ʱ��
	time_t tEnd;		//��ֹ����
	time_t tLast;		//���ʹ��ʱ��
	float fTotalUse;	//�ۼƽ��
	int iUseCount;		//ʹ�ô���
	float fBalance;		//���
	int iDel;			//ɾ����ʶ 0-δɾ�� 1-��ɾ��
}Card;

//��ʼ������Ϣ
Card initCard();

//����ת���ַ���
void cardToString(Card card, char* cCard);

//���ַ���ת����
Card stringToCard(char *ptr);

