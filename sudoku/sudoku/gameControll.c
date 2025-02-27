#include "gameControll.h"

void letTheFunBegin() {                                  /*the king function, show it some respect*/
    List* playerList = (List*)malloc(sizeof(List));
    List* winnerPlayerList = (List*)malloc(sizeof(List));
    Tree* playersTree = start(playerList, winnerPlayerList);

    while (playerList->head != NULL) {
        readTreeInOrder(playersTree, playerList, winnerPlayerList);
    }
    endGame(playerList, winnerPlayerList, playersTree);
}

void gameOver(TreeNode* root, List* playerList) {
    printf("\n\n\n%s selections led to duplications\n", root->playerP->name);
    deleteFromList(playerList, root->playerP->name);
    free(root->playerP->possibilities);
    free(root->playerP->name);
    free(root->playerP);
    root->playerP = NULL;
}

void gameWon(TreeNode* root, List* playerList, List* winnerPlayerList) {
    printf("\n\n\n%s Board filled successfully\n", root->playerP->name);
    sudokoPrintBoard(root->playerP->board);
    insertValueToTail(winnerPlayerList, root->playerP);
    deleteFromList(playerList, root->playerP->name);
    root->playerP = NULL;
}

int playGame(Player* player, int* x, int* y) {  /*gets the input from the user every turn*/
    printf("\n\n");
    printf("%s board:\n", player->name);
    sudokoPrintBoard(player->board);
    printf("\n\n");
    printf("Cell number [%d,%d] has the min number of options, please enter one of the possibilities: ", *x, *y);
    for (int i = 0; i < player->possibilities[*x][*y]->size; i++) {
        printf("%d ", player->possibilities[*x][*y]->arr[i]);
    }
    printf("\n");
    int isValidNum = NOT_VALID;
    int num;
    while (isValidNum == NOT_VALID) {
        scanf("%d", &num);
        isValidNum = checkIfNumIsValid(num);
        if(isValidNum == NOT_VALID)
            printf("Please choose a valid option\n");
    }
    if (!IsMoveLegal(*x, *y, num, player->board)) {
        return FAIL;
    }
    player->board[*x][*y] = num;
    FreePossibilities(*x, *y, player->possibilities);
    DeletePossibilities(*x, *y, player->board[*x][*y], player->possibilities);
    return NOT_FINISH;
}

int checkIfNumIsValid(int num) {
    if (num < 1)
        return NOT_VALID;
    else if (num > 9)
        return NOT_VALID;
    else
        return VALID;
}

Tree* start(List* playerList, List* winnerPlayerList) {   /*gets the input for the names of the players, builds the structs of the players, the lists and the tree*/
    makeEmptyList(winnerPlayerList);
    int playerssize = getInput(playerList);
    sortListOfPlayers(playerList, playerssize);
    return BuildPlayersTree(playerList, playerssize);
}

void endGame(List* playerList, List* winnerPlayerList, Tree* playersTree) {  /*checks if there are any winners and free the memory*/
    checkForWinners(winnerPlayerList);
    free(playerList);
    freeList(winnerPlayerList);
}