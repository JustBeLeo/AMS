#include"billing_file.h"

void LoginFile(LoginInfo info) {
	FILE *fp;
	errno_t err;
	if ((err = fopen_s(&fp, LOGIN_FILE_DIR , "a+") != 0)) {
		printf("LOGIN_FILE�ļ���ռ��\n\n");
		return;
	}
	char str[100],	tStart[50];
	timeToString(info.tStart, tStart);
	sprintf_s(str, 100, "%s\t%s\t%f\t1\n", info.cCardName, tStart, info.fBalance);
	fputs(str,fp);
}

void SettleFile(char* cNum,SettleInfo* sInfo)
{
	FILE *fp,*fp1;
	int isLogin;		//�Ƿ��¼
	Standard* std = (Standard*)malloc(sizeof(Standard));		//�����շѱ�׼
	getStandard(std, 0);			//�õ��շѱ�׼
	int time;						//�����ϻ�ʱ��(s)
	LoginInfo lInfo;
	char cInfo[50], tStart[50], temp1[25], temp2[25];
	errno_t err;
	if ((err = fopen_s(&fp, LOGIN_FILE_DIR , "r") != 0)) {
		printf("LOGIN_FILE�ļ���ռ��\n\n");
		return;
	}

	if ((err = fopen_s(&fp1, SETTLE_FILE_DIR, "a+") != 0)) {
		printf("LOGIN_FILE�ļ���ռ��\n\n");
		return;
	}

	while (fgets(cInfo, 100, fp) != NULL)
	{
		sscanf_s(cInfo, "%s %s %s %f %d", lInfo.cCardName, sizeof(lInfo.cCardName), temp1,sizeof(temp1),temp2, sizeof(temp2), &lInfo.fBalance, &isLogin);
		if ((strcmp(lInfo.cCardName,cNum)==0)&&isLogin==1)
		{
			strcpy_s(sInfo->cCardName, 18, lInfo.cCardName);
			sprintf_s(tStart, 50, "%s %s", temp1, temp2);
			sInfo->tStart = stringToTime(tStart);
			sInfo->tEnd = getTime();
			if (((int)sInfo->tEnd - (int)sInfo->tStart) < std->unit * 60) {
				time = 1;
			}
			else {
				time = ((int)sInfo->tEnd - (int)sInfo->tStart)/60;
			}
			sInfo->fAmount = time * std->charge;
			sInfo->fBalance = lInfo.fBalance - sInfo->fAmount;
			if (sInfo->fBalance < 0) {
				printf("���㣬���ȳ�ֵ");
				return;
			}
			sprintf_s(cInfo, 50, "%s\t%lf\t\n", sInfo->cCardName, sInfo->fAmount);
			printf("�»��ɹ�");
			fputs(cInfo, fp1);
		}
	}
	//���û���ҵ��ϻ���Ϣ
	if (feof(fp1)) {
		printf("δ�ҵ��ÿ����ϻ���Ϣ\n\n");
		fclose(fp1);
		return;
	}
	fclose(fp);
	fclose(fp1);

	//fpָ�򴢴��ļ���fp1ָ�򻺴��ļ�
	if ((err = fopen_s(&fp, LOGIN_FILE_DIR, "r") != 0)) {
		printf("LOGIN_FILE�ļ���ռ��\n\n");
		return;
	}

	if ((err = fopen_s(&fp1, "temp1.txt", "w+") != 0)) {
		printf("LOGIN_FILE�ļ���ռ��\n\n");
		return;
	}

	//�޸��ϻ���Ϣ�е�isLoginΪ0�Ķ�д�ļ�����
	while (fgets(cInfo, 1000, fp) != NULL) {
		sscanf_s(cInfo, "%s %s %s %f %d", lInfo.cCardName, sizeof(lInfo.cCardName), temp1, sizeof(temp1), temp2, sizeof(temp2), &lInfo.fBalance, &isLogin);
		//�ҵ����ſ�
		if (strcmp( lInfo.cCardName, cNum) == 0) {
			//�޸��ϻ���Ϣ�е�isLoginΪ0�������������Ͳ����¼��
			sprintf_s(tStart, 50, "%s %s", temp1, temp2);
			sprintf_s(cInfo, 50, "%s\t%s\t%f 0\n", lInfo.cCardName, tStart,lInfo.fBalance);
		}
		fputs(cInfo, fp1);
	}

	//������д��temp1.txt���ļ��ر�
	fclose(fp1);
	fclose(fp);

	//fpָ�򴢴��ļ���fp1ָ�򻺴��ļ�
	if ((err = fopen_s(&fp, LOGIN_FILE_DIR , "w") != 0)) {
		printf("LOGIN_FILE �ļ���ռ��\n\n");
		return;
	}

	if ((err = fopen_s(&fp1, "temp1.txt", "r") != 0)) {
		printf("temp1�ļ���ռ��\n\n");
		return;
	}

	strcpy_s(cInfo, 50, "");
	while (!feof(fp1)) {
		fgets(cInfo, sizeof(cInfo), fp1);
		fputs(cInfo, fp);
		strcpy_s(cInfo, 50, "");
	}

	fclose(fp);
	fclose(fp1);
}

