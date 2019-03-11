#pragma once
#include"card_file.h"

//Ìí¼Ó¿¨
void addCard();
//É¾³ı¿¨
void deleteCard(char *cNum);
//²éÕÒ¿¨
int searchCard(char *cNum, int isPrint);
//ĞŞ¸Ä¿¨
void updateCard(Card card);