#pragma once
#include"global.h"
typedef struct Standard	 {
	//int startTime;		//��ʼʱ��
	//int endTime;		//����ʱ��
	int unit;			//��С�Ʒѵ�Ԫ
	float charge;		//ÿ���Ʒѵ�Ԫ���շ�
	//int rateType;		//�շ����� 0-��ͨ 1-��ҹ 2-����
	//int del;			//ɾ��״̬ 0-δɾ�� 1-��ɾ��
}Standard;

//��ȡ��׼
void getStandard(Standard* std, int needPrint);
//�޸ı�׼
void changeStandard();
