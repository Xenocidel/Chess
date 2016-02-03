#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include "board.h"
#include "piece.h"
#include "cell.h"

typedef struct moveValue{ /* Structure that groups piece, next cell ID, and value */
	piece *piece;
	int next; /* Cell ID for next move */
	int value; /* Value of potential next move */
} moveValue ;

void aiMove(int diff, int team, board *board);

void aiChoice(int team, board *board, int lookAhd);

int oppTeam (int team);

void DeleteMoveValue(struct moveValue *m);
moveValue *ABPrune(int *piecePositions, int *enemyPositions, moveValue *bestMax, moveValue *bestMin, int lookahd, int team, int max, board *board);
/*struct moveValue *calcABmax(int *moveList, int *piecePositions, int *enemyPositions, struct moveValue *bestMax, struct moveValue *bestMin, int lookAhd, int team, board *board);
struct moveValue *calcABmin(int *moveList, int *piecePositions, int *enemyPositions, struct moveValue *bestMax, struct moveValue *bestMin, int lookAhd, int team, board *board);*/
struct moveValue *calcMoveValue(int team, board *board, cell *moveLoc, int nextCellLoc);
struct moveValue *CreateMoveValue(piece *p, int next, int value); 

/* void randomMove(int team, board *board); Unused */

int pieceMoveCount(piece *p);
int totalMoveCount(int team, board *board);

int *checkAIAvailMoves(piece *p);
int *checkPiecePos(int team, board *board);

#endif