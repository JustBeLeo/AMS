#pragma once
#include"global.h"
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

//���˵������ļ���
void bill_to_file(Billing ptr);

//���ϻ���Ϣд������
void doLogin(LinkedLoginInfo* head,LoginInfo info);
//��ȡ�ϻ�ʱ��
time_t getLoginTime(LinkedLoginInfo* head, char *cCardName);
//���»���Ϣ���ϻ���Ϣ�ϲ�����billing



