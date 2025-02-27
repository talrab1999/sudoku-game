
#ifndef __playersTree_H
#define __playersTree_H

#include "list.h"
typedef struct treeNode {
    Player* playerP;
    struct treeNode* left;
    struct treeNode* right;
}TreeNode;

typedef struct tree {
    TreeNode* root;
}Tree;

TreeNode* BuildTreeFromArray(Player** playerArr, int psize);
Tree* BuildPlayersTree(List* playerList, int psize);
Player** convertToArrSizeTree(List* playerList, int psize);
void readTreeInOrder(Tree* tree, List* playerList, List* winnerPlayerList);
void readTreeInOrderRec(TreeNode* root, List* playerList, List* winnerPlayerList);
void printTreeInOrder(Tree* tree);
void printTreeInOrderRec(TreeNode* root);
void freeTree(Tree* tree);
void freeTreeRec(TreeNode* root);

#endif
