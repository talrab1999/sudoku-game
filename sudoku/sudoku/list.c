#include "list.h"


LNode** convertToArr(List* playerList, int psize) {           /*converts a list to an array*/
	LNode** newArr = (LNode**)malloc(sizeof(LNode*) * psize);
	checkMalloc(newArr);
	LNode* curr = playerList->head;
	int indx = 0;

	while (curr != NULL) {
		newArr[indx] = curr;
		curr = curr->next;
		indx++;
	}
	return newArr;
}

void convertToList(LNode** arrOfPlayers, List* playerList, int psize) {  /*converts an array to a list*/
	playerList->head = arrOfPlayers[0];

	for (int i = 0; i < psize - 1; i++) {
		arrOfPlayers[i]->next = arrOfPlayers[i + 1];
	}
	playerList->tail = arrOfPlayers[psize - 1];
	playerList->tail->next = NULL;
}

void mergeSort(LNode** arr, int l, int r) {

	if (l >= r) {
		return;
	}

	int mid = l + (r - l) / 2;
	mergeSort(arr, l, mid);
	mergeSort(arr, mid + 1, r);
	merge(arr, l, r, mid);
}

void merge(LNode** arr, int l, int r, int mid) {
	int arr1size = mid - l + 1;
	int arr2size = r - mid;
	LNode** tempArr1 = (LNode**)malloc(sizeof(LNode) * arr1size);
	LNode** tempArr2 = (LNode**)malloc(sizeof(LNode) * arr2size);
	checkMalloc(tempArr1);
	checkMalloc(tempArr2);

	for (int i = 0; i < arr1size; i++) {
		tempArr1[i] = arr[l + i];
	}
	for (int i = 0; i < arr2size; i++) {
		tempArr2[i] = arr[mid + 1 + i];
	}

	int indx1 = 0, indx2 = 0, indxArr = l;
	while (indx1 < arr1size && indx2 < arr2size)
	{
		int filledSquares1 = CountFilledSquares(tempArr1[indx1]->data->board);
		int filledSquares2 = CountFilledSquares(tempArr2[indx2]->data->board);
		if (filledSquares1 < filledSquares2) {
			arr[indxArr] = tempArr1[indx1];
			indx1++;
		}
		else if (filledSquares1 == filledSquares2) {
			if (strcmp(tempArr1[indx1]->data->name, tempArr2[indx2]->data->name) > 0) {
				arr[indxArr] = tempArr2[indx2];
				indx2++;
			}
			else {
				arr[indxArr] = tempArr1[indx1];
				indx1++;
			}
		}
		else {
			arr[indxArr] = tempArr2[indx2];
			indx2++;
		}
		indxArr++;
	}

	while (indx1 < arr1size) {
		arr[indxArr] = tempArr1[indx1];
		indx1++;
		indxArr++;
	}
	while (indx2 < arr2size) {
		arr[indxArr] = tempArr2[indx2];
		indx2++;
		indxArr++;
	}
	free(tempArr1);
	free(tempArr2);
}


int CountFilledSquares(short board[][COLS]) {   /*counts how many filled squares are in the board*/
	int count = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] != -1)
				count++;
		}
	}
	return count;
}

void sortListOfPlayers(List* playerList, int psize) {
	LNode** arrOfPlayers = convertToArr(playerList, psize);
	mergeSort(arrOfPlayers, 0, psize - 1);
	convertToList(arrOfPlayers, playerList, psize);
	free(arrOfPlayers);
}

int getInput(List* lst) {
	makeEmptyList(lst);
	int psize;
	char temp[MAX_NAME_LEN];
	printf("Please enter number of players:\n");
	scanf("%d", &psize);

	for (int i = 0; i < psize; i++)
	{
		printf("Please enter player name: ");
		scanf("%s", temp);
		Player* player = createPlayer(temp);
		insertValueToTail(lst, player);
	}
	return psize;
}

Player* createPlayer(char* name) {
	int validBoard = FAIL;
	Player* player = (Player*)malloc(sizeof(Player));
	player->name = (char*)malloc(strlen(name) + 1);
	strcpy(player->name, name);
	while (validBoard == FAIL) {                        /*had to loop to make sure the board is valid at the start of the game*/
		CreateRandomBoard(player->board);
		player->possibilities = PossibleDigits(player->board);
		validBoard = isValidBoard(player);
	}
	return player;
}

int isValidBoard(Player* player) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (player->possibilities[i][j] != NULL) {
				if (player->possibilities[i][j]->size == 0)
					return FAIL;
			}
		}
	}
	return SUCCESS;
}

void checkForWinners(List* lst) {
	LNode* temp = lst->head;

	printf("\n\n\n");
	printf("*****************************************************\n\n");
	if (lst->head == NULL) {
		printf("There are no winners this time, thanks for playing :)\n");
		return;
	}
	while (temp != NULL)
	{
		printf("%s is a winner\n", temp->data->name);
		sudokoPrintBoard(temp->data->board);
		printf("\n\n");
		temp = temp->next;
	}
	printf("Thats all of the winners for the game, thanks for playing :)\n");
}

void makeEmptyList(List* lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}

int isEmpty(List* lst)
{
	if (lst->head == NULL)
		return 1;
	else
		return 0;
}

LNode* createNewNode(Player* newData, LNode* next)
{
	LNode* newNode = (LNode*)malloc(sizeof(LNode));
	checkMalloc(newNode);
	newNode->data = newData;
	newNode->next = next;
	return newNode;
}

void insertValueToTail(List* lst, Player* newData)
{
	LNode* newNode = createNewNode(newData, NULL);
	if (isEmpty(lst))
		lst->head = lst->tail = newNode;
	else
	{
		lst->tail->next = newNode;
		lst->tail = newNode;
	}
}

void deleteFromList(List* lst, char* name) {
	LNode* curr = lst->head;
	LNode* temp = curr;
	if (curr != NULL && strcmp(curr->data->name, name) == 0) {
		lst->head = curr->next;
		free(curr);
		return;
	}
	while (curr != NULL && strcmp(curr->data->name, name) != 0) {   
		temp = curr;
		curr = curr->next;
	}
	if (curr == NULL)
		return;

	temp->next = curr->next;
	free(curr);
}

void printList(List* lst)
{
	LNode* temp = lst->head;
	while (temp != NULL)
	{
		printf("%s\n", temp->data->name);
		sudokoPrintBoard(temp->data->board);
		temp = temp->next;
		printf("\n\n\n");
	}
	printf("end list\n");
}

void freeList(List* lst)  
{
	LNode* current = lst->head;
	while (current)
	{
		LNode* temp = current;
		current = current->next;
		freePlayer(temp->data);
		free(temp);
	}
	free(lst);
}

void freePlayer(Player* player) {
	free(player->name);
	FreePossibleDigits(player->possibilities);
	free(player);
}
