#include"linked_card_service.h"
//初始化
LinkedCard* initLinkedCard(){
	LinkedCard* ptr = (LinkedCard*)malloc(sizeof(LinkedCard));
	ptr->next = NULL;
	return ptr;
}
//添加卡
void addLinkedCard(LinkedCard* head) {
	LinkedCard* node = (LinkedCard*)malloc(sizeof(LinkedCard));
	LinkedCard* ptr = head;
	node->card = initCard();
	printf("请输入卡号（长度为1-18）：");
	scanf_s("%s", &node->card.cNum, 18);
	printf("请输入密码（长度为1-8）：");
	scanf_s("%s", &node->card.cPwd, 8);
	printf("请输入开卡金额：");
	scanf_s("%f", &node->card.fBalance);
	printf("\n------添加的卡信息如下------\n");
	printf("卡号\t密码\t状态\t开卡金额\n");
	printf("%s\t%s\t%d\t%.1f\n\n", node->card.cNum, node->card.cPwd, node->card.iStatus, node->card.fBalance);
	node->next = NULL;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = node;
	printf("添加成功\n\n");
}
//删除卡
void deleteLinkedCard(LinkedCard* head) {
	LinkedCard* ptr = head;
	LinkedCard* ptr1 = ptr;
	int isFind = 0;
	char cNum[20];
	printf("请输入要删除的卡号：");
	scanf_s("%s", cNum, 20);
	while (ptr != NULL) {
		if (strcmp(ptr->card.cNum, cNum) == 0) {
			ptr1->next = ptr->next;
			ptr->next = NULL;
			free(ptr);
			printf("删除成功！\n\n");
			break;
		}
		ptr1 = ptr;
		ptr = ptr->next;
	}
	if (ptr == NULL)printf("未找到该卡数据\n\n");
}
//查找卡
int searchLinkedCard(LinkedCard* head, int isPrint) {
	LinkedCard* ptr = head;
	int isFind = 0;
	char cNum[20];
	printf("请输入要查找的卡号：");
	scanf_s("%s", cNum, 20);
	while (ptr != NULL) {
		if (strcmp(ptr->card.cNum, cNum) == 0) {
			if (isPrint == TRUE) {
				char tStart[20], tEnd[20], tLast[20];
				timeToString(ptr->card.tStart, tStart);
				timeToString(ptr->card.tEnd, tEnd);
				if ((int)ptr->card.tLast == 0) strcpy_s(tLast, 20, "0\t\t");
				else timeToString(ptr->card.tLast, tLast);
				printf("卡号\t\t密码\t\t状态\t开卡时间\t\t\t截止日期\t\t\t\n");
				printf("%s\t\t%s\t\t%d\t%s\t\t%s\n", ptr->card.cNum, ptr->card.cPwd, ptr->card.iStatus, tStart, tEnd);
				printf("最后使用时间\t累计金额\t使用次数\t余额\t\t删除标识\n");
				printf("%s%f\t%d\t\t%f\t%d\n", tLast, ptr->card.fTotalUse, ptr->card.iUseCount, ptr->card.fBalance, ptr->card.iDel);
			}
			isFind = 1;
			break;
		}
		ptr = ptr->next;
	}
	if (ptr == NULL)printf("未找到该卡数据\n\n");
	return isFind;
}