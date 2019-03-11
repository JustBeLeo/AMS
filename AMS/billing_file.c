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

