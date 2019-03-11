#include"global.h"
#include"menu.h"

void menu() {
	int num = 0;
	logininfo_head = (LinkedLoginInfo*)malloc(sizeof(LinkedLoginInfo));
	logininfo_head->next = NULL;
	while (num != 6) {
		printf("--------��ӭʹ�üƷѹ���ϵͳ--------\n");
		printf("1. ������							\n");
		printf("2. �Ʒѱ�׼����						\n");
		printf("3. �Ʒѹ���							\n");
		printf("4. ���ù���							\n");
		printf("5. ��ѯͳ��							\n");
		printf("6. �˳�								\n\n");
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
		printf("---------------������---------------\n");
		printf("1. ��ӿ�							\n");
		printf("2. ��ѯ��							\n");
		printf("3. ɾ����							\n");
		printf("4. �����							\n");
		printf("5. �˳�								\n\n");
		scanf_s("%d", &num);
		switch (num)
		{
		case 1:
			addCard();
			break;
		case 2:
			printf("��������Ҫ��ѯ�Ŀ��ţ�");
			scanf_s("%s", cNum, 18);
			searchCard(cNum,1);
			break;
		case 3:
			printf("��������Ҫɾ���Ŀ��ţ�");
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
		printf("-------------��������-------------\n");
		printf("1. ��ӿ�							\n");
		printf("2. ɾ����							\n");
		printf("3. ���ҿ�							\n");
		printf("4. �˳�								\n\n");
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
		printf("------------�Ʒѱ�׼����------------\n");
		printf("1. ��ѯ��׼							\n");
		printf("2. �޸ı�׼							\n");
		printf("3. �˳�								\n\n");
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
		printf("--------------�Ʒѹ���--------------\n");
		printf("1. �ϻ�								\n");
		printf("2. �»�								\n");
		printf("3. �˳�								\n\n");
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
		printf("--------------���ù���--------------\n");
		printf("1. ��ֵ								\n");
		printf("2. �˷�								\n");
		printf("3. �˳�								\n\n");
		scanf_s("%d", &num);

	}
}

void showMenu5() {
	int num = 0;
	while (num != 3) {
		printf("--------------��ѯͳ��--------------\n");
		printf("1. ��ѯ���Ѽ�¼						\n");
		printf("2. ͳ����Ӫҵ��						\n");
		printf("3. �˳�								\n\n");
		scanf_s("%d", &num);

	}
}