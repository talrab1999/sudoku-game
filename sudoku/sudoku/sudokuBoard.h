
#ifndef __sudokuBoard_H
#define __sudokuBoard_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define SIZE 100
#define ROWS 9
#define COLS 9
#define NOT_FINISH 0
#define FINISH_SUCCESS 1
#define FINISH_FAILURE -1
#define FAIL -1
#define FILLED 1
#define NO_PLAYER 1
#define SUCCESS 1
#define NOT_VALID 0
#define VALID 1


typedef int BOOL;
#define FALSE 0
#define TRUE 1

typedef struct _Array
{
	short* arr;
	unsigned short size;
}Array;

typedef struct _Square {
	int row;
	int col;
	struct Square* nextSquare;
}Square;

typedef struct _RandomBoard {
	Square* firstSquare;
	Square* lastSquare;
}RandomBoard;

Array*** PossibleDigits(short sudokuBoard[][COLS]);
BOOL IsInRow(int row, int num, short sudokuBoard[][COLS]);
BOOL IsInCol(int col, int num, short sudokuBoard[][COLS]);
BOOL IsInBox(int row, int col, int num, short sudokuBoard[][COLS]);
int OneStage(short board[][COLS], Array*** possibilities, int* x, int* y);
void DeleteNumFromRow(int row, int num, Array*** possibilities);
void DeleteNumFromCol(int col, int num, Array*** possibilities);
void DeleteNumFromBox(int row, int col, int num, Array*** possibilities);
void DeletePossibilities(int row, int col, int num, Array*** possibilities);
void ShiftArray(short* Array, short size, int indx);
BOOL DidWeFinish(short board[][COLS]);
BOOL IsMoveLegal(int row, int col, short squareNum, short board[][COLS]);
void FindXAndYCord(Array*** possibilities, int* x, int* y);
int FillBoard(short board[][COLS], Array*** possibilities, char* name);
void FreePossibilities(int row, int col, Array*** possibilities);
void sudokoPrintBoard(short board[][COLS]);
void PrintLineOfNums(int num);
void CreateRandomBoard(short board[][COLS]);
RandomBoard CreateListOfSquares();
void insertDataToEndListBoard(int row, int col, RandomBoard* lst);
Square* createNewListOfSquares(int row, int col, Square* next);
void insertNodeToEndListBoard(RandomBoard* lst, Square* newTail);
void makeEmptyListBoard(RandomBoard* lst);
int isEmptyListBoard(RandomBoard* lst);
void GetSquareData(int randomSquare, RandomBoard* lst, int* row, int* col);
void FreePossibleDigits(Array*** posibilities);
void InsertRandomNum(int row, int col, short board[][COLS]);
void freeRandomBoard(RandomBoard* randomBoard);
void checkMalloc(void* ptr);



#endif