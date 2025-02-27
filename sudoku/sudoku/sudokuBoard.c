#include "sudokuBoard.h"

Array*** PossibleDigits(short sudokuBoard[][COLS]) {
	Array*** sudokoPointer;
	sudokoPointer = (Array***)malloc(sizeof(Array**) * COLS);
	checkMalloc(sudokoPointer);

	for (int i = 0; i < ROWS; i++) {
		sudokoPointer[i] = (Array**)malloc(sizeof(Array*) * COLS);
		checkMalloc(sudokoPointer[i]);
	}

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (sudokuBoard[i][j] == -1) {
				unsigned short size = 0;
				short* possibilities = (short*)malloc(sizeof(short) * COLS);

				for (int z = 1; z <= 9; z++) {
					BOOL isInRow = IsInRow(i, z, sudokuBoard);
					BOOL isInCol = IsInCol(j, z, sudokuBoard);
					BOOL isInBox = IsInBox(i, j, z, sudokuBoard);
					if (!isInRow && !isInCol && !isInBox) {
						possibilities[size] = z;
						size++;
					}
				}
				Array* tempArr = (Array*)malloc(sizeof(Array));
				tempArr->arr = possibilities;
				tempArr->size = size;
				sudokoPointer[i][j] = tempArr;
			}
			else {
				sudokoPointer[i][j] = NULL;
			}
		}
	}
	return sudokoPointer;
}

int OneStage(short board[][COLS], Array*** possibilities, int* x, int* y) {
	BOOL flag = TRUE;

	while (flag) {
		flag = FALSE;

		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {

				if (possibilities[i][j] == NULL)
					continue;
				if (possibilities[i][j]->size == 1) {
					flag = TRUE;
					if (!IsMoveLegal(i, j, possibilities[i][j]->arr[0], board))
						return FINISH_FAILURE;
					board[i][j] = possibilities[i][j]->arr[0];
					FreePossibilities(i, j, possibilities);
					DeletePossibilities(i, j, board[i][j], possibilities);
				}
			}
		}
	}

	if (DidWeFinish(board)) {
		return FINISH_SUCCESS;
	}

	FindXAndYCord(possibilities, x, y);
	if (possibilities[*x][*y]->size == 0)
		return FINISH_FAILURE;
	return NOT_FINISH;
}

int FillBoard(short board[][COLS], Array*** possibilities, char* name) {
	int x, y;
	BOOL result;


	while ((result = OneStage(board, possibilities, &x, &y)) == NOT_FINISH) {
		printf("\n\n");
		printf("%s board:\n", name);
		sudokoPrintBoard(board);
		printf("\n\n");
		printf("Cell number [%d,%d] has the min number of options, please enter one of the possibilities: ", x, y);
		for (int i = 0; i < possibilities[x][y]->size; i++) {
			printf("%d ", possibilities[x][y]->arr[i]);
		}
		printf("\n");
		int num;
		scanf("%d", &num);
		if (!IsMoveLegal(x, y, num, board)) {
			return FAIL;
		}
		board[x][y] = num;
		FreePossibilities(x, y, possibilities);
		DeletePossibilities(x, y, board[x][y], possibilities);
	}

	if (result == FINISH_FAILURE)
		return FAIL;

	return FILLED;
}

BOOL IsInRow(int row, int num, short sudokuBoard[][COLS]) {
	for (int i = 0; i < COLS; i++) {
		if (num == sudokuBoard[row][i])
			return TRUE;
	}
	return FALSE;
}

BOOL IsInCol(int col, int num, short sudokuBoard[][COLS]) {
	for (int i = 0; i < ROWS; i++) {
		if (num == sudokuBoard[i][col])
			return TRUE;
	}
	return FALSE;
}

BOOL IsInBox(int row, int col, int num, short sudokuBoard[][COLS]) {
	int TopLeftRow, TopLeftCol;
	TopLeftRow = row - row % 3;
	TopLeftCol = col - col % 3;

	for (int i = TopLeftRow; i < TopLeftRow + 3; i++) {
		for (int j = TopLeftCol; j < TopLeftCol + 3; j++) {
			if (num == sudokuBoard[i][j])
				return TRUE;
		}
	}
	return FALSE;
}


void sudokoPrintBoard(short board[][COLS]) {
	PrintLineOfNums(COLS-1);

	for (int i = 0; i < ROWS; i++) {
		if (i % 3 == 0) {
			for (int i = 0; i <= 32; i++) {
				printf("%c", '_');
			}
			printf("\n");
		}
		printf(" %2d ", i);
		for (int j = 0; j < COLS; j++) {
			if (board[i][j] == -1) {
				if (j % 3 == 0)
					printf("|   ");
				else
					printf("   ");
			}
			else {
				if (j % 3 == 0)
					printf("|%2d ", board[i][j]);
				else
					printf("%2d ", board[i][j]);
			}
		}
		printf("\n");
	}
}

void PrintLineOfNums(int num) /*used for the board printing*/
{
	printf("    ");
	for (int i = 0; i <= num; i++) {
		if (i % 3 == 0)
			printf("| %d", i);
		else
			printf("%2d", i);
		printf(" ");
	}
	printf("\n");
}

void DeleteNumFromRow(int row, int num, Array*** possibilities) {
	for (int i = 0; i < COLS; i++) {
		if (possibilities[row][i] == NULL)
			continue;
		for (int j = 0; j < possibilities[row][i]->size; j++) {
			if (num == possibilities[row][i]->arr[j]) {
				ShiftArray(possibilities[row][i]->arr, possibilities[row][i]->size, j);
				possibilities[row][i]->size--;
			}
		}
	}
}

void DeleteNumFromCol(int col, int num, Array*** possibilities) {
	for (int i = 0; i < ROWS; i++) {
		if (possibilities[i][col] == NULL)
			continue;
		for (int j = 0; j < possibilities[i][col]->size; j++) {
			if (num == possibilities[i][col]->arr[j]) {
				ShiftArray(possibilities[i][col]->arr, possibilities[i][col]->size, j);
				possibilities[i][col]->size--;
			}
		}
	}
}

void DeleteNumFromBox(int row, int col, int num, Array*** possibilities) {

	int TopLeftRow, TopLeftCol;
	TopLeftRow = row - row % 3;
	TopLeftCol = col - col % 3;

	for (int i = TopLeftRow; i < TopLeftRow + 3; i++) {
		for (int j = TopLeftCol; j < TopLeftCol + 3; j++) {
			if (possibilities[i][j] == NULL)
				continue;
			for (int z = 0; z < possibilities[i][j]->size; z++) {
				if (num == possibilities[i][j]->arr[z]) {
					ShiftArray(possibilities[i][j]->arr, possibilities[i][j]->size, z);
					possibilities[i][j]->size--;
				}
			}
		}
	}
}

void DeletePossibilities(int row, int col, int num, Array*** possibilities) {
	DeleteNumFromRow(row, num, possibilities);
	DeleteNumFromCol(col, num, possibilities);
	DeleteNumFromBox(row, col, num, possibilities);
}

void ShiftArray(short* Array, short size, int indx) {
	for (int i = indx; i < size - 1; i++) {
		Array[i] = Array[i + 1];
	}
}

BOOL DidWeFinish(short board[][COLS]) {

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (board[i][j] == -1)
				return FALSE;
		}
	}
	return TRUE;
}

BOOL IsMoveLegal(int row, int col, short num, short board[][COLS]) {
	return !IsInRow(row, num, board) && !IsInCol(col, num, board) && !IsInBox(row, col, num, board);
}

void FindXAndYCord(Array*** possibilities, int* x, int* y) {
	unsigned short SmallestSize;
	SmallestSize = 10;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (possibilities[i][j] != NULL) {
				if (possibilities[i][j]->size < SmallestSize) {
					SmallestSize = possibilities[i][j]->size;
					*x = i;
					*y = j;
				}
			}
		}
	}

}

void FreePossibilities(int row, int col, Array*** possibilities) {
	free(possibilities[row][col]->arr);
	free(possibilities[row][col]);
	possibilities[row][col] = NULL;
}

void CreateRandomBoard(short board[][COLS]) {
	int numOfRandomSquares = 1 + rand() % 20;
	int numOfSquares = ROWS*COLS;
	RandomBoard randomBoard;
	randomBoard = CreateListOfSquares();

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			board[i][j] = -1;
		}
	}

	for (int i = 1; i <= numOfRandomSquares; i++) {
		int row, col;
		int randomSquare;
		randomSquare = 1 + rand() % numOfSquares;
		GetSquareData(randomSquare, &randomBoard, &row, &col);
		InsertRandomNum(row, col, board);
		numOfSquares--;
	}
	freeRandomBoard(&randomBoard);
}

void InsertRandomNum(int row, int col, short board[][COLS]) {
	short* arr = (short*)malloc(sizeof(short) * 9);
	checkMalloc(arr);
	unsigned short size = 0;

	for (int z = 1; z <= 9; z++) {
		BOOL isInRow = IsInRow(row, z, board);
		BOOL isInCol = IsInCol(col, z, board);
		BOOL isInBox = IsInBox(row, col, z, board);
		if (!isInRow && !isInCol && !isInBox) {
			arr[size] = z;
			size++;
		}
	}
		
	int indx = rand() % size;
	short randomNum = arr[indx];
	board[row][col] = randomNum;
	free(arr);
}

void FreePossibleDigits(Array*** posibilities) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (posibilities[i][j] == NULL)
				continue;
			free(posibilities[i][j]->arr);
			free(posibilities[i][j]);    
		}
		free(posibilities[i]);
	}
	free(posibilities);
}

void GetSquareData(int randomSquare, RandomBoard* lst, int *row, int *col) {  /*goes throught the board list to the wanted square, to get the row and the col of the square*/
	Square* current;
	current = lst->firstSquare;
	int numOfLoops = 1;

	if (randomSquare == 1) {
		*row = current->row;
		*col = current->col;
		lst->firstSquare = current->nextSquare;
		free(current);
		return;
	}
	while (numOfLoops != randomSquare - 1)
	{
		current = current->nextSquare;   
		numOfLoops++;
	}

	Square* temp = current->nextSquare;
	*row = temp->row;
	*col = temp->col;
	current->nextSquare = temp->nextSquare;
	if (temp->nextSquare == NULL)
		lst->lastSquare = current;
	free(temp);        
}

RandomBoard CreateListOfSquares() {
	RandomBoard res;
	makeEmptyListBoard(&res);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			insertDataToEndListBoard(i, j, &res);
		}
	}
	return res;
}

void insertDataToEndListBoard(int row, int col, RandomBoard* lst)
{
	Square* newTail;
	newTail = createNewListOfSquares(row, col, NULL);
	insertNodeToEndListBoard(lst, newTail);
}

Square* createNewListOfSquares(int row, int col, Square* next)
{
	Square* output;

	output = (Square*)malloc(sizeof(Square));
	checkMalloc(output);
	output->row = row;
	output->col = col;
	output->nextSquare = next;
	return output;
}

void insertNodeToEndListBoard(RandomBoard* lst, Square* newTail)
{
	if (isEmptyListBoard(lst) == 1)
	{
		lst->firstSquare = newTail;
		lst->lastSquare = newTail;
	}
	else
	{
		lst->lastSquare->nextSquare = newTail;
		lst->lastSquare = newTail;
	}

}

void makeEmptyListBoard(RandomBoard* lst)
{
	lst->firstSquare = NULL;
	lst->lastSquare = NULL;
}

int isEmptyListBoard(RandomBoard* lst)
{
	if (lst->firstSquare == NULL)
		return 1;
	else
		return 0;
}

void freeRandomBoard(RandomBoard* randomBoard) {
	Square* current = randomBoard->firstSquare;
	Square* temp;
	while (current->nextSquare != NULL)
	{
		temp = current;
		current = current->nextSquare;
		free(temp);   
	}
	randomBoard->firstSquare = NULL;
	randomBoard->lastSquare = NULL;
}


void checkMalloc(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Memory allocation error");
		exit(1);
	}
}