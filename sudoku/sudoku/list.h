
#ifndef __list_H
#define __list_H

#include "sudokuBoard.h"
#define MAX_NAME_LEN 100

typedef struct _Player {
	//char name[MAX_NAME_LEN];
	char* name;
	Array*** possibilities;
	short board[9][9];
}Player;

typedef struct listNode {
	Player* data;
	struct listNode* next;
}LNode;

typedef struct list {
	LNode* head;
	LNode* tail;
}List;


LNode** convertToArr(List* playerList, int psize);
LNode* createNewNode(Player* newData, LNode* next);
Player* createPlayer(char* name);
int CountFilledSquares(short board[][COLS]);
int getInput(List* lst);
int isValidBoard(Player* player);
void convertToList(LNode** arrOfPlayers, List* playerList, int psize);
void mergeSort(LNode** arr, int l, int r);
void merge(LNode** arr, int l, int r, int mid);
void sortListOfPlayers(List* playerList, int psize);
void merge(LNode** arr, int l, int r, int mid);
void makeEmptyList(List* lst);
int isEmpty(List* lst);
void insertValueToTail(List* lst, Player* newData);
void printList(List* lst);
void freeList(List* lst);
void deleteFromList(List* lst, char* name);
void checkForWinners(List* lst);
void freePlayer(Player* player);

#endif
