#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "piece.h"
#include "cell.h"
#include "board.h"


cell *createCell(int cellID, board *board){
	cell *ans = malloc(sizeof(cell));
	ans->cellID = cellID;
	ans->piece = NULL;
	ans->board = board;
	return ans;
}

void replacePiece(cell *cell, piece *p){
	cell->piece = p;
}

void deleteCell(cell *cell){	/*used at program shutdown, be sure to delete board separately*/
	if(cell->piece != NULL){	/*deletes all pieces as well*/
		deletePiece(cell->piece);
	}
	free(cell);
}

void deleteAllCells(board *board){
	int i;
	for (i=-1; i<64; i++){
		deleteCell(getCell(i, board));
	}
}