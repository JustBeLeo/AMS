#include"card_file.h"
//初始化卡信息
Card initCard() {
	Card card;
	char time[20];
	card.iStatus = card.iDel = card.fTotalUse = card.iUseCount = 0;
	card.tStart = getTime();
	card.tLast = (time_t)0;
	timeToString(card.tStart, time);
	time[2] += 1;
	card.tEnd = stringToTime(time);
	return card;
}

//从类转成字符串
void cardToString(Card card,char* cCard) {
	char tStart[20], tEnd[20], tLast[20];
	timeToString(card.tStart, tStart);
	timeToString(card.tEnd, tEnd);
	if ((int)card.tLast == 0) strcpy_s(tLast,20, "0 0\t\t\t\t");
	else timeToString(card.tLast, tLast);
	sprintf_s(cCard,100, "%s\t\t%s\t\t%d\t\t%s\t%s\t%s\t%f\t%d\t\t\t%f\t%d\n", 
		card.cNum, card.cPwd, card.iStatus, tStart, tEnd, tLast, card.fTotalUse, 
		card.iUseCount, card.fBalance, card.iDel);
}

//从字符串转成类
Card stringToCard(char *ptr) {
	Card card;
	char tStart[30], tEnd[30], tLast[30];
	char temp1[15], temp2[10], temp3[15], temp4[10], temp5[15], temp6[10];
	sscanf_s(ptr, "%s %s %d %s %s %s %s %s %s %f %d %f %d\n"
		, card.cNum, sizeof(card.cNum), card.cPwd, sizeof(card.cPwd),
		&card.iStatus, temp1, sizeof(temp1), temp2, sizeof(temp2),
		temp3, sizeof(temp3), temp4, sizeof(temp4), temp5,
		sizeof(temp5), temp6, sizeof(temp6), &card.fTotalUse,
		&card.iUseCount, &card.fBalance, &card.iDel);
	sprintf_s(tStart, 30, "%s %s", temp1, temp2);
	sprintf_s(tEnd, 30, "%s %s", temp3, temp4);
	sprintf_s(tLast, 30, "%s %s", temp5, temp6);
	card.tStart = stringToTime(tStart);
	card.tEnd = stringToTime(tEnd);
	if (strcmp(tLast, "0 0") == 0) card.tLast = (time_t)0;
	else card.tLast = stringToTime(tLast);
	return card;
}

