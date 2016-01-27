#ifndef CELL_H_INCLUDED_
#define CELL_H_INCLUDED_
#include "piece.h"
#include "board.h"

typedef struct piece piece;
typedef struct board board;
struct cell{
	char printPiece;
	int cellID;		/*range from -1 to 63. -1 for captured pieces.*/
	piece *piece;
	board *board;
} ;

struct cell *createCell(int cellID, board *board);
void replacePiece(struct cell *cell, piece *p);
void deleteCell(struct cell *cell);	/*deletes all pieces as well*/
void deleteAllCells(board *board); /*used at program shutdown, delete board separately*/
void updatePrintPiece(struct cell *cell);

#endif