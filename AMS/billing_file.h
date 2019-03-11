#pragma once
#include"global.h"
#include "rate_file.h"

typedef struct Billing {
	char cCardName[18];	//����
	time_t tStart;		//�ϻ�ʱ��
	time_t tEnd;		//�»�ʱ��
	float fAmount;		//���ѽ��
	int iStatus;		//����״̬ 0-δ���� 1-�ѽ���
	int iDel;			//ɾ��״̬ 0-δɾ�� 1-��ɾ��
}Billing;

typedef struct LoginInfo {
	char cCardName[18];	//����
	time_t tStart;		//�ϻ�ʱ��
	float fBalance;		//���
}LoginInfo;

typedef struct Use {
	char cCardName[18];	//����
	time_t tUse;	//��ʱ����
	float fUse;		//�������
}Use;

typedef struct LinkedLoginInfo {
	LoginInfo info;
	struct LinkedLoginInfo* next;
}LinkedLoginInfo;

typedef struct SettleInfo {
	char cCardName[18];	//����
	time_t tStart;		//�ϻ�ʱ��
	time_t tEnd;		//�»�ʱ��
	float fAmount;		//���ѽ��
	float fBalance;		//���
}SettleInfo;

//���˵�������
void bill_to_file(Billing ptr);
//���ϻ���Ϣд���ļ�
void LoginFile(LoginInfo info);
//�»������˵�д���ļ���
void SettleFile(char* cNum, SettleInfo* sInfo);
//���»���Ϣ���ϻ���Ϣ�ϲ�����billing



