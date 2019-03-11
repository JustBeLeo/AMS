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
		printf("RATE_FILE文件被占用\n\n");
		return;
	}
	//如果文件为空
	if ((fgets(tmp, 30, fp))==NULL) {
		sprintf_s(tmp, 30, "%d %.3f\n", mStandard.unit,mStandard.charge);
		fputs(tmp, fp);
		std->charge = mStandard.charge;
		std->unit = mStandard.unit;
		if (needPrint == 1) {
			printf("最小计费单元%d分钟，每个单元的费用%.3f元\n", mStandard.unit / 60, mStandard.charge);
		}
		fclose(fp);
		return;
	}
	else {
		//不为空
		fclose(fp);
		if ((err = fopen_s(&fp, RATE_FILE_DIR, "r") != 0)) {
			printf(" RATE_FILE文件被占用\n\n");
			return;
		}
		fgets(tmp, 30, fp);
		sscanf_s(tmp, "%d %f", &mStandard.unit, &mStandard.charge);
		std->charge = mStandard.charge;
		std->unit = mStandard.unit;
		if (needPrint == 1) {
			printf("最小计费单元%d分钟，每个单元的费用%f元\n", mStandard.unit / 60, mStandard.charge);
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
	printf("请输入最小计费单元(分钟):");
	scanf_s("%d", &unit);
	mStandard.unit = unit * 60;
	printf("请输入每个计费单元的价格(元):");
	scanf_s("%f", &mStandard.charge);
	if ((err = fopen_s(&fp, RATE_FILE_DIR, "w") != 0)) {
		printf("RATE_FILE 文件被占用\n\n");
		return;
	}
	sprintf_s(tmp, 30, "%d %.3f\n", mStandard.unit, mStandard.charge);
	fputs(tmp, fp);
	fclose(fp);
}
