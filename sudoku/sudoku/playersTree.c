#include "playersTree.h"

Tree* BuildPlayersTree(List* playerList, int psize) {
    int newSize = pow(2, ceil(log2(psize + 1)));
    newSize--;
    Player** arrOfPlayers = convertToArrSizeTree(playerList, newSize);
    Tree* playersTree = (Tree*)malloc(sizeof(Tree));
    checkMalloc(playersTree);
    int indx = 0;
    playersTree->root =  BuildTreeFromArray(arrOfPlayers, newSize);
    free(arrOfPlayers);
    return playersTree;
}

Player** convertToArrSizeTree(List* playerList, int size) {    /*made new converter to add NULLS at the end*/
    Player** newArr = (Player**)malloc(sizeof(Player*) * size);
    checkMalloc(newArr);
    LNode* curr = playerList->head;
    int indx = 0;

    while (curr != NULL) {
        newArr[indx] = curr->data;
        curr = curr->next;
        indx++;
    }
    for (indx; indx < size; indx++) {
        newArr[indx] = NULL;
    }

    return newArr;
}

TreeNode* BuildTreeFromArray(Player** playerArr, int size)
{
    TreeNode* resTree;
    int halfSize;

    resTree = (TreeNode*)malloc(sizeof(TreeNode));
    checkMalloc(resTree);
    if (size == 1)
    {
        resTree->playerP = playerArr[0];
        resTree->left = NULL;
        resTree->right = NULL;
    }
    else
    {
        halfSize = size / 2;
        resTree->playerP = playerArr[halfSize];
        if (playerArr[halfSize / 2] != NULL) //left side
        {
            resTree->left = BuildTreeFromArray(playerArr, halfSize);
        }
        else
        {
            resTree->left = NULL;
        }
        if (playerArr[(halfSize / 2) + 1] != NULL) //right side
        {
            resTree->right = BuildTreeFromArray(playerArr + halfSize + 1, halfSize);
        }
        else
        {
            resTree->right = NULL;
        }
    }
    return resTree;
}


void readTreeInOrder(Tree* tree, List* playerList, List* winnerPlayerList) {
    readTreeInOrderRec(tree->root, playerList, winnerPlayerList);
}

void readTreeInOrderRec(TreeNode* root, List* playerList, List* winnerPlayerList) {  /*reads the tree and controlls the game itself*/
    if (root == NULL)
        return;
    readTreeInOrderRec(root->left, playerList, winnerPlayerList);
    int x;
    int y;
    if (root->playerP != NULL) {
        int didFinish = OneStage(root->playerP->board, root->playerP->possibilities, &x, &y);
        if (didFinish == FAIL) {
            gameOver(root, playerList);
        }
        else if (didFinish == NOT_FINISH) {
           int isLegal = playGame(root->playerP, &x, &y);
           if (isLegal == FAIL) {
               gameOver(root, playerList);
           }
        }
        else
        {
            gameWon(root, playerList, winnerPlayerList);         
        }
    }
    readTreeInOrderRec(root->right, playerList, winnerPlayerList);
}
