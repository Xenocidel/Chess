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
void bishopTest(board *board);
void bishopTest(board *board);

int main(){
	board *board = createBoard();
	
	pawnTest(board);
	bishopTest(board);
	kingTest(board);
	
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
	assert(p1moves);
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
	assert(p1moves2);
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
	assert(t3p1moves);
	while (*t3p1moves != -2){
		printf("Pawn in cell 38 can move to cell %d\n", *t3p1moves);
		if (*t3p1moves != 30 && *t3p1moves != 29){
			printf("Pawn test 3 failed!\n");
			exit(1);
		}
		t3p1moves++;
	}
	int *t3p2moves = checkAvailMoves(t3p2);
	assert(t3p2);
	while (*t3p2moves != -2){
		printf("Pawn in cell 39 can move to cell %d\n", *t3p2moves);
		if (*t3p2moves != 46 && *t3p2moves != 47){
			printf("Pawn test 3 failed!\n");
			exit(1);
		}
		t3p2moves++;
	}
	int *t3p3moves = checkAvailMoves(t3p3);
	assert(t3p3);
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

void bishopTest(board *board){
	/* Test free movement */
	piece *b1 = createPiece(white, bishop, CELL11);
	printf("A %d (%d) has been created in cell %d\n", b1->type, b1->player, b1->loc->cellID);
	printLoc(b1);
	printf("Testing basic bishop movements...\n");
	int *b1moves = checkAvailMoves(b1);
	while(*b1moves != -2){
		printf("Bishop (cell 11) can move to cell %d\n", *b1moves);
		b1moves++;
	}
	b1moves = NULL;
	/* Test for option to capture enemy and not move to invalid position */
	piece *b2 = createPiece(white, bishop, CELL43);
	printf("A %d (%d) has been created in cell %d\n", b2->type, b2->player, b2->loc->cellID);
	printLoc(b2);
	piece *b3 = createPiece(black, bishop, CELL34);
	printf("A %d (%d) has been created in cell %d\n", b3->type, b3->player, b3->loc->cellID);
	printLoc(b3);
	piece *b4 = createPiece(white, bishop, CELL36);
	printf("A %d (%d) has been created in cell %d\n", b4->type, b4->player, b4->loc->cellID);
	printLoc(b4);
	printf("Testing capture movements and blocking movements...\n");
	int *b2moves = checkAvailMoves(b2);
	while(*b2moves != -2){
		printf("Bishop (cell 43) can move to cell %d\n", *b2moves);
		b2moves++;
	}
	b2moves = NULL;
}
void kingTest(board *board){
	piece *k1 = createPiece(white, king, CELL0);
	piece *k2 = createPiece(white, king, CELL7);
	piece *k3 = createPiece(white, king, CELL56);
	piece *k4 = createPiece(white, king, CELL63);
	piece *k5 = createPiece(white, king, CELL32);
	piece *k6 = createPiece(white, king, CELL39);
	piece *k7 = createPiece(white, king, CELL59);
	piece *k8 = createPiece(white, king, CELL4);
	piece *k9 = createPiece(white, king, CELL21);
	printf("Running Test 1: Cell 0\n");
	int *k1moves = checkAvailMoves(k1);
	printf("%d", *k1moves);
	while (*k1moves != -2){
		printf("King in Cell 0 can move to %d\n", *k1moves);
		k1moves++;
	}
	printf("\n\nRunning Test 2: Cell 7\n");
	int *k2moves = checkAvailMoves(k2);
	while (*k2moves != -2){
		printf("King in Cell 7 can move to %d\n", *k2moves);
		k2moves++;
	}
	printf("\n\nRunning Test 3: Cell 56\n");
	int *k3moves = checkAvailMoves(k3);
	while (*k3moves != -2){
		printf("King in Cell 56 can move to %d\n", *k3moves);
		k3moves++;
	}
	printf("\n\nRunning Test 4: Cell 63\n");
	int *k4moves = checkAvailMoves(k4);
	while (*k4moves != -2){
		printf("King in Cell 63 can move to %d\n", *k4moves);
		k4moves++;
	}
	printf("\n\nRunning Test 5: Cell 32\n");
	int *k5moves = checkAvailMoves(k5);
	while (*k5moves != -2){
		printf("King in Cell 32 can move to %d\n", *k5moves);
		k5moves++;
	}
	printf("\n\nRunning Test 6: Cell 39\n");
	int *k6moves = checkAvailMoves(k6);
	while (*k6moves != -2){
		printf("King in Cell 39 can move to %d\n", *k6moves);
		k6moves++;
	}
	printf("\n\nRunning Test 7: Cell 59\n");
	int *k7moves = checkAvailMoves(k7);
	while (*k7moves != -2){
		printf("King in Cell 59 can move to %d\n", *k7moves);
		k7moves++;
	}
	printf("\n\nRunning Test 8: Cell 4\n");
	int *k8moves = checkAvailMoves(k8);
	while (*k8moves != -2){
		printf("King in Cell 4 can move to %d\n", *k8moves);
		k8moves++;
	}
	printf("\n\nRunning Test 9: Cell 21\n");
	int *k9moves = checkAvailMoves(k9);
	while (*k9moves != -2){
		printf("King in Cell 21 can move to %d\n", *k9moves);
		k9moves++;
	}
}