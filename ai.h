#ifndef "AI_H_INCLUDED"
#define "AI_H_INCLUDED"
#include "board.h"

int aiMove(int difficulty, int team, board *board);

void easyMove(int team, board *board);
void medMove(int team, board *board);
void hardMove(int team, board *board);

int *checkPiecePos(int team, board *board);

#endif