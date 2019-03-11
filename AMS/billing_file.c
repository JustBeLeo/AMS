#include"billing_file.h"
void doLogin(LinkedLoginInfo* head,LoginInfo info) {
	LinkedLoginInfo *node = (LinkedLoginInfo*)malloc(sizeof(LinkedLoginInfo));
	LinkedLoginInfo *ptr;
	node->info = info;
	node->next = NULL;
	ptr = head;
	while (ptr->next!=NULL)
	{
		ptr = ptr->next;
	}
	ptr->next = node;
}

void LoginFile(LoginInfo info) {
	FILE *fp;
	errno_t err;
	if ((err = fopen_s(&fp, LOGIN_FILE_DIR , "a+") != 0)) {
		printf("添加时打开文件失败\n\n");
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
	int isLogin;
	LoginInfo lInfo;
	char cInfo[50], tStart[50], temp1[25], temp2[25];
	errno_t err;
	if ((err = fopen_s(&fp, LOGIN_FILE_DIR , "r") != 0)) {
		printf("文件被占用\n\n");
		return;
	}

	if ((err = fopen_s(&fp1, SETTLE_FILE_DIR, "a+") != 0)) {
		printf("文件被占用\n\n");
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
			sInfo->fAmount = (float)((int)sInfo->tEnd - (int)sInfo->tStart)*0.00027;
			sInfo->fBalance = lInfo.fBalance - sInfo->fAmount;
			sprintf_s(cInfo, 50, "%s\t%lf\t\n", sInfo->cCardName, sInfo->fAmount);
			fputs(cInfo, fp1);
		}
	}
	//如果没有找到上机信息
	if (feof(fp1)) {
		printf("未找到该卡的上机信息\n\n");
		fclose(fp1);
		return;
	}
	fclose(fp);
	fclose(fp1);

	//fp指向储存文件，fp1指向缓存文件
	if ((err = fopen_s(&fp, LOGIN_FILE_DIR, "r") != 0)) {
		printf("文件被占用\n\n");
		return;
	}

	if ((err = fopen_s(&fp1, "temp1.txt", "w+") != 0)) {
		printf("文件被占用\n\n");
		return;
	}

	//修改上机信息中的isLogin为0的读写文件操作
	while (fgets(cInfo, 1000, fp) != NULL) {
		sscanf_s(cInfo, "%s %s %s %f %d", lInfo.cCardName, sizeof(lInfo.cCardName), temp1, sizeof(temp1), temp2, sizeof(temp2), &lInfo.fBalance, &isLogin);
		//找到这张卡
		if (strcmp( lInfo.cCardName, cNum) == 0) {
			//修改上机信息中的isLogin为0，这样接下来就不会记录了
			sprintf_s(tStart, 50, "%s %s", temp1, temp2);
			sprintf_s(cInfo, 50, "%s\t%s\t%f 0\n", lInfo.cCardName, tStart,lInfo.fBalance);
		}
		fputs(cInfo, fp1);
	}

	//将缓存写入temp1.txt后将文件关闭
	fclose(fp1);
	fclose(fp);

	//fp指向储存文件，fp1指向缓存文件
	if ((err = fopen_s(&fp, LOGIN_FILE_DIR , "w") != 0)) {
		printf("LOGIN_FILE_DIR 打开失败\n\n");
		return;
	}

	if ((err = fopen_s(&fp1, "temp1.txt", "r") != 0)) {
		printf("temp1文件被占用\n\n");
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
 

time_t getLoginTime(LinkedLoginInfo* head,char *cCardName) {
	LinkedLoginInfo *ptr = head;
	while (ptr->next != NULL)
	{
		if (strcmp(ptr->info.cCardName, cCardName) == 0) {
			return ptr->info.tStart;
		}
		ptr = ptr->next;
	}
	return (time_t)0;
}

