#ifndef "AI_H_INCLUDED"
#define "AI_H_INCLUDED"
#include "board.h"
#include "piece.h"
#include "cell.h"
/*STUFF THAT IS FINISHED:
	ALPHA BETA ALGORITHM
	CHECKING/COUNTING PIECE POSITIONS AND MOVES
	ACTUALLY MOVING THE PIECE (FROM AIMOVE FUNCTION)
	FUNCTIONS THAT CREATE/FREE MEMORY FOR MOVEVALUE STRUCTURES*/
	
/*STUFF TO DO TOMORROW:
	MOVE WEIGHING ALGORITHM
	DEBUGGING
	COMPILATION
	TESTING*/
	
typedef struct moveValue{
	piece *piece;
	int next; /* Cell ID for next move */
	int value; /* Value of potential next move */
} moveValue;

int aiMove(int diff, int team, board *board);

void aiChoice(int team, board *board, int lookAhd);

int oppTeam (int team);

moveValue *CreateMoveValue(piece p, int next, int value);
void DeleteMoveValue(moveValue *move);
moveValue *calcABmax(int *piecePointer, int *piecePositions, int *enemyPositions, moveValue *bestMax, moveValue *bestMin, int lookAhd, int team, board *board);
moveValue *calcABmin(int *piecePointer, int *piecePositions, int *enemyPositions, moveValue *bestMax, moveValue *bestMin, int lookAhd, int team, board *board);
moveValue *calcMoveValue(int team, board *board, int moveLoc);

void randomMove(int team, board *board); /* Probably not used. Just ignore */

int pieceMoveCount(piece *p);
int totalMoveCount(int team, board *board);

int *checkAIAvailMoves(piece *p);
int *checkPiecePos(int team, board *board);

#endif