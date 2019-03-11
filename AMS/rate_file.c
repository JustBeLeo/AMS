#include "rate_file.h"

void getStandard(Standard* std,int needPrint)
{
	FILE *fp;
	errno_t err;
	Standard mStandard;
	char tmp[30],ch = 'a';
	mStandard.unit = 3600;
	mStandard.charge = 10;
	if((err = fopen_s(&fp, RATE_FILE_DIR, "r") != 0)) {
		printf("RATE_FILE�ļ���ռ��\n\n");
		return;
	}
	//����ļ�Ϊ��
	if ((fgets(tmp, 30, fp))==NULL) {
		sprintf_s(tmp, 30, "%d %.3f\n", mStandard.unit,mStandard.charge);
		fputs(tmp, fp);
		std->charge = mStandard.charge;
		std->unit = mStandard.unit;
		if (needPrint == 1) {
			printf("��С�Ʒѵ�Ԫ%d���ӣ�ÿ����Ԫ�ķ���%.3fԪ\n", mStandard.unit / 60, mStandard.charge);
		}
		fclose(fp);
		return;
	}
	else {
		//��Ϊ��
		fclose(fp);
		if ((err = fopen_s(&fp, RATE_FILE_DIR, "r") != 0)) {
			printf(" RATE_FILE�ļ���ռ��\n\n");
			return;
		}
		fgets(tmp, 30, fp);
		sscanf_s(tmp, "%d %f", &mStandard.unit, &mStandard.charge);
		std->charge = mStandard.charge;
		std->unit = mStandard.unit;
		if (needPrint == 1) {
			printf("��С�Ʒѵ�Ԫ%d���ӣ�ÿ����Ԫ�ķ���%fԪ\n", mStandard.unit / 60, mStandard.charge);
		}
		fclose(fp);
		return;
	}
}

void changeStandard()
{
	Standard mStandard;
	errno_t err;
	FILE *fp;
	char tmp[50];
	int unit;
	printf("��������С�Ʒѵ�Ԫ(����):");
	scanf_s("%d", &unit);
	mStandard.unit = unit * 60;
	printf("������ÿ���Ʒѵ�Ԫ�ļ۸�(Ԫ):");
	scanf_s("%f", &mStandard.charge);
	if ((err = fopen_s(&fp, RATE_FILE_DIR, "w") != 0)) {
		printf("RATE_FILE �ļ���ռ��\n\n");
		return;
	}
	sprintf_s(tmp, 30, "%d %.3f\n", mStandard.unit, mStandard.charge);
	fputs(tmp, fp);
	fclose(fp);
}
