#include"global.h"
#include"menu.h"

void menu() {
	int num = 0;
	logininfo_head = (LinkedLoginInfo*)malloc(sizeof(LinkedLoginInfo));
	logininfo_head->next = NULL;
	while (num != 6) {
		printf("--------欢迎使用计费管理系统--------\n");
		printf("1. 卡管理							\n");
		printf("2. 计费标准管理						\n");
		printf("3. 计费管理							\n");
		printf("4. 费用管理							\n");
		printf("5. 查询统计							\n");
		printf("6. 退出								\n\n");
		scanf_s("%d", &num);
		switch (num) {
		case 1:
			showMenu1();
			break;
		case 2:
			showMenu2();
			break;
		case 3:
			showMenu3();
			break;
		case 4:
			showMenu4();
			break;
		case 5:
			showMenu5();
			break;
		case 6:
			break;
		}
	}
}

void showMenu1() {
	int num = 0;
	char cNum[18];
	while (num != 5) {
		printf("---------------卡管理---------------\n");
		printf("1. 添加卡							\n");
		printf("2. 查询卡							\n");
		printf("3. 删除卡							\n");
		printf("4. 链表版							\n");
		printf("5. 退出								\n\n");
		scanf_s("%d", &num);
		switch (num)
		{
		case 1:
			addCard();
			break;
		case 2:
			printf("请输入需要查询的卡号：");
			scanf_s("%s", cNum, 18);
			searchCard(cNum,1);
			break;
		case 3:
			printf("请输入需要删除的卡号：");
			scanf_s("%s", cNum, 18);
			deleteCard(cNum);
			break;
		case 4:
			showMenu1_1();
			break;
		}
	}
}
void showMenu1_1() {
	int num = 0;
	card_head = initLinkedCard();
	while (num != 4) {
		printf("-------------链表卡管理-------------\n");
		printf("1. 添加卡							\n");
		printf("2. 删除卡							\n");
		printf("3. 查找卡							\n");
		printf("4. 退出								\n\n");
		scanf_s("%d", &num);
		switch (num)
		{
		case 1:
			addLinkedCard(card_head);
			break;
		case 2:
			deleteLinkedCard(card_head);
			break;
		case 3:
			searchLinkedCard(card_head, 1);
			break;
		case 4:
			break;
		}
	}
}
void showMenu2() {
	int num = 0;
	Standard* std = (Standard*)malloc(sizeof(Standard));
	while (num != 3) {
		printf("------------计费标准管理------------\n");
		printf("1. 查询标准							\n");
		printf("2. 修改标准							\n");
		printf("3. 退出								\n\n");
		scanf_s("%d", &num);
		switch (num)
		{
		case 1:
			getStandard(std, 1);
			break;
		case 2:
			changeStandard();
			break;
		}
	}
}

void showMenu3() {
	int num = 0;
	while (num != 3) {
		printf("--------------计费管理--------------\n");
		printf("1. 上机								\n");
		printf("2. 下机								\n");
		printf("3. 退出								\n\n");
		scanf_s("%d", &num);
		switch (num)
		{
		case 1:
			Login();
			break;
		case 2:
			Settle();
			break;
		case 3:
			break;
		}
	}
}

void showMenu4() {
	int num = 0;
	while (num != 3) {
		printf("--------------费用管理--------------\n");
		printf("1. 充值								\n");
		printf("2. 退费								\n");
		printf("3. 退出								\n\n");
		scanf_s("%d", &num);

	}
}

void showMenu5() {
	int num = 0;
	while (num != 3) {
		printf("--------------查询统计--------------\n");
		printf("1. 查询消费记录						\n");
		printf("2. 统计总营业额						\n");
		printf("3. 退出								\n\n");
		scanf_s("%d", &num);

	}
}