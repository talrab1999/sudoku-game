#ifndef __gameControll_H
#define __gameControll_H

#include "playersTree.h"

//functions for the game itself, like when somebody wins or loses
void letTheFunBegin();
int playGame(Player* player, int* x, int* y);
int checkIfNumIsValid(int num);
Tree* start(List* playerList, List* winnerPlayerList);
void gameOver(TreeNode* root, List* playerList);
void gameWon(TreeNode* root, List* playerList, List* winnerPlayerList);
void endGame(List* playerList, List* winnerPlayerList, Tree* playersTree);

#endif