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
void updatePrintPiece(cell *cell){
	if (cell->piece == NULL){
		cell->printPiece = ' ';
	}
	else{
		switch (cell->piece->player){
		case black:
			switch (cell->piece->type){
			case queen:
				cell->printPiece = 'q';
				break;
			case king:
				cell->printPiece = 'k';
				break;
			case knight:
				cell->printPiece = 'n';
				break;
			case rook:
				cell->printPiece = 'r';
				break;
			case bishop:
				cell->printPiece = 'b';
				break;
			case pawn:
				cell->printPiece = 'p';
				break;
			}
			break;
		case white:
			switch (cell->piece->type){
			case queen:
				cell->printPiece = 'Q';
				break;
			case king:
				cell->printPiece = 'K';
				break;
			case knight:
				cell->printPiece = 'N';
				break;
			case rook:
				cell->printPiece = 'R';
				break;
			case bishop:
				cell->printPiece = 'B';
				break;
			case pawn:
				cell->printPiece = 'P';
				break;
			}
			break;
		}
	}
}