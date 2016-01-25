#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "errors.h"
#include "defs.h"
#include "board.h"
#include "piece.h"

int main(){
	board *board = createNewGame();
	/*standard move and jump move*/
	piece *p1 = createPiece(white, pawn, CELL8);
	printf("Piece (type: %d) (color: %d) created in cell %d / ", p1->type, p1->player, p1->loc->cellID);
	printLoc(p1);
	printf("Testing basic pawn movement...\n");
	int *p1moves = checkAvailMoves(p1);
	int numMoves = sizeof(*p1moves)/sizeof(int);
	printf("%d available moves for pawn in cell 8\n", numMoves);
	while(numMoves > 0){
		printf("Pawn in cell 8 can move to cell %d\n", *p1moves);
		if (numMoves > 0){
			p1moves++;
		}
		numMoves--;
	}
	/*capture while on left edge and obstacle in front*/
	piece *p2 = createPiece(black, pawn, CELL16);
	printf("Piece (type: %d) (color: %d) created in cell %d / ", p2->type, p2->player, p2->loc->cellID);
	printLoc(p2);
	piece *p3 = createPiece(black, pawn, CELL17);
	printf("Piece (type: %d) (color: %d) created in cell %d / ", p3->type, p3->player, p3->loc->cellID);
	printLoc(p3);
	printf("Testing pawn basic capture movement...\n");
	int *p1moves2 = checkAvailMoves(p1);
	int numMoves2 = sizeof(*p1moves2)/sizeof(int);
	printf("%d available moves for pawn in cell 8\n", numMoves2);
	while(numMoves2 > 0){
		printf("Pawn in cell 8 can move to cell %d\n", *p1moves2);
		if (numMoves2 > 0){
			p1moves++;
		}
		numMoves2--;
	}
	
	/*clean up all the mallocs*/
	deleteAllCells(board);	/*deletes all pieces as well*/
	printf("All cells and pieces freed\n");
	deleteBoard(board);
	printf("Board freed\n");
	
	exit(0); /*because i'm lazy and i dont' want to free my mallocs*/
	return 0;
}