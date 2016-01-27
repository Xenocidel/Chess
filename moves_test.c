/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                 Chess                                        *
*               Copyright (C) 2016  nøl / C Gets Degrees                       *
*                                                                              *
*    This program is free software; you can redistribute it and/or modify      *
*    it under the terms of the GNU General Public License as published by      *
*    the Free Software Foundation; either version 2 of the License, or         *
*    (at your option) any later version.                                       *
*                                                                              *
*    You should have received a copy of the GNU General Public License         *
*    along with this program; if not, write to the Free Software               *
*    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA *
*                                                                              *                                                       *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 *
 * Created on 2016-01-13
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "errors.h"
#include "defs.h"
#include "board.h"
#include "piece.h"

void pawnTest(board *board);

int main(){
	board *board = createNewGame();
	
	pawnTest(board);
	
	
	/*clean up all the mallocs*/
	deleteAllCells(board);	/*deletes all pieces as well*/
	printf("All cells and pieces freed\n");
	deleteBoard(board);
	printf("Board freed\n");
	
	exit(0);
	return 0;
}

void pawnTest(board *board){
	/* START OF PAWN TEST */
	/* PAWN TEST 1: standard move and jump move*/
	piece *p1 = createPiece(white, pawn, CELL8);
	printf("Piece (type: %d) (color: %d) created in cell %d / ", p1->type, p1->player, p1->loc->cellID);
	printLoc(p1);
	printf("Running pawn test 1...\n");
	int *p1moves = checkAvailMoves(p1);
	while(*p1moves != -2){
		printf("Pawn in cell 8 can move to cell %d\n", *p1moves);
		if (*p1moves == 16 && *p1moves == 24){
			printf("Pawn test 1 failed!\n");
			exit(1);
		}
		p1moves++;
	}
	/* PAWN TEST 2: capture while on left edge and obstacle in front*/
	piece *p2 = createPiece(black, pawn, CELL16);
	printf("Piece (type: %d) (color: %d) created in cell %d / ", p2->type, p2->player, p2->loc->cellID);
	printLoc(p2);
	piece *p3 = createPiece(black, pawn, CELL17);
	printf("Piece (type: %d) (color: %d) created in cell %d / ", p3->type, p3->player, p3->loc->cellID);
	printLoc(p3);
	printf("Running pawn test 2...\n");
	int *p1moves2 = checkAvailMoves(p1);
	while(*p1moves2 != -2){
		printf("Pawn in cell 8 can move to cell %d\n", *p1moves2);
		if (*p1moves2 != 17){
			printf("Pawn test 2 failed!\n");
			exit(1);
		}
		p1moves2++;
	}
	
	/* PAWN TEST 3: p1 on 38 with epFlag on can move to 30 or capture p3, p2 on 39 can en passant p1 to 46 or move to 47, p3 on 29 can capture p1 or move to 37*/
	piece *t3p1 = createPiece(black, pawn, CELL38);
	t3p1->epFlag = 1;
	piece *t3p2 = createPiece(white, pawn, CELL39);
	piece *t3p3 = createPiece(white, pawn, CELL29);
	t3p1->hasMoved = true;
	t3p2->hasMoved = true;
	t3p3->hasMoved = true;
	
	printf("Running pawn test 3...\n");
	int *t3p1moves = checkAvailMoves(t3p1);
	while (*t3p1moves != -2){
		printf("Pawn in cell 38 can move to cell %d\n", *t3p1moves);
		if (*t3p1moves != 30 && *t3p1moves != 29){
			printf("Pawn test 3 failed!\n");
			exit(1);
		}
		t3p1moves++;
	}
	int *t3p2moves = checkAvailMoves(t3p2);
	while (*t3p2moves != -2){
		printf("Pawn in cell 39 can move to cell %d\n", *t3p2moves);
		if (*t3p2moves != 46 && *t3p2moves != 47){
			printf("Pawn test 3 failed!\n");
			exit(1);
		}
		t3p2moves++;
	}
	int *t3p3moves = checkAvailMoves(t3p3);
	while (*t3p3moves != -2){
		printf("Pawn in cell 29 can move to cell %d\n", *t3p3moves);
		if (*t3p3moves != 37 && *t3p3moves != 38){
			printf("Pawn test 3 failed!\n");
			exit(1);
		}
		t3p3moves++;
	}
	
	/* END OF PAWN TEST */
}