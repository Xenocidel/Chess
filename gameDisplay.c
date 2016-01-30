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
 * Created on 2016-01-06
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "gameDisplay.h"
#include "piece.h"
#include "board.h"
#include "errors.h"
#include "defs.h"

void updateGameDisplay(board *board){
	printf("    a   b   c   d   e   f   g   h\n");
	printf("  +---+---+---+---+---+---+---+---+\n");
	printf("8 | %c | %c | %c | %c | %c | %c | %c | %c | 8\n", CELL56->printPiece, CELL57->printPiece, CELL58->printPiece, CELL59->printPiece, CELL60->printPiece, CELL61->printPiece, CELL62->printPiece, CELL63->printPiece);
	printf("  +---+---+---+---+---+---+---+---+\n");
	printf("7 | %c | %c | %c | %c | %c | %c | %c | %c | 7\n", CELL48->printPiece, CELL49->printPiece, CELL50->printPiece, CELL51->printPiece, CELL52->printPiece, CELL53->printPiece, CELL54->printPiece, CELL55->printPiece);
	printf("  +---+---+---+---+---+---+---+---+\n");
	printf("6 | %c | %c | %c | %c | %c | %c | %c | %c | 6\n", CELL40->printPiece, CELL41->printPiece, CELL42->printPiece, CELL43->printPiece, CELL44->printPiece, CELL45->printPiece, CELL46->printPiece, CELL47->printPiece);
	printf("  +---+---+---+---+---+---+---+---+\n");
	printf("5 | %c | %c | %c | %c | %c | %c | %c | %c | 5\n", CELL32->printPiece, CELL33->printPiece, CELL34->printPiece, CELL35->printPiece, CELL36->printPiece, CELL37->printPiece, CELL38->printPiece, CELL39->printPiece);
	printf("  +---+---+---+---+---+---+---+---+\n");
	printf("4 | %c | %c | %c | %c | %c | %c | %c | %c | 4\n", CELL24->printPiece, CELL25->printPiece, CELL26->printPiece, CELL27->printPiece, CELL28->printPiece, CELL29->printPiece, CELL30->printPiece, CELL31->printPiece);
	printf("  +---+---+---+---+---+---+---+---+\n");
	printf("3 | %c | %c | %c | %c | %c | %c | %c | %c | 3\n", CELL16->printPiece, CELL17->printPiece, CELL18->printPiece, CELL19->printPiece, CELL20->printPiece, CELL21->printPiece, CELL22->printPiece, CELL23->printPiece);
	printf("  +---+---+---+---+---+---+---+---+\n");
	printf("2 | %c | %c | %c | %c | %c | %c | %c | %c | 2\n", CELL8 ->printPiece, CELL9 ->printPiece, CELL10->printPiece, CELL11->printPiece, CELL12->printPiece, CELL13->printPiece, CELL14->printPiece, CELL15->printPiece);
	printf("  +---+---+---+---+---+---+---+---+\n");
	printf("1 | %c | %c | %c | %c | %c | %c | %c | %c | 1\n", CELL0 ->printPiece, CELL1 ->printPiece, CELL2 ->printPiece, CELL3 ->printPiece, CELL4 ->printPiece, CELL5 ->printPiece, CELL6 ->printPiece, CELL7 ->printPiece);
	printf("  +---+---+---+---+---+---+---+---+\n");
	printf("    a   b   c   d   e   f   g   h\n");
	printf("\n\n");
	printMessage(board->turn);
	handleInput(board);
}

void updateMessage(board *board){
	printf("\n");
	printMessage(board->turn);
	handleInput(board);
}

void printMessage(int turn){ /* for turns: white = even, black = odd */
	if (turn%2 == 0){
		printf("White's turn\n\n");
	}
	else{
		printf("Black's turn\n\n");
	}
	if (turn == 0){
		printf("White pieces are displayed in CAPITALS. Black pieces are displayed in lowercase\n\nMove a piece by typing its location and its destination like: a2 a3\nYou can also see a piece's available moves by typing its location like: a1\n\n");
	}
	
	printf("\n>");
}

void handleInput(board *board){
	char *loc = malloc(sizeof(char)*7);
	if (fgets(loc, 7, stdin)){
		char *tmp;
		if ((tmp = strchr(loc, '\n')) != NULL){ /*cuts off \n at the end of each input*/
			*tmp = '\0';
		}
		if (strlen(loc) > 5){
			int c;
			while((c = getchar()) != '\n' && c != EOF); /* purges excess or \n input */
			printe(entryFormat);
			free(loc);
			return;
		}
	}
	int cellID = toID(loc);
	if (cellID == -2){
		printe(command);
		free(loc);
		return;
	}
	if (cellID == -3){
		/* todo: maybe deleteBoard and deleteAllCells? */
		free(loc);
		exit(0);
	}
	if (cellID == -4){
		/* undo */
		printf("Undo move functionality is currently unavailable.\n");
		free(loc);
		return;
	}
	if (cellID == -5){ /*do nothing*/
		free(loc);
		return;
	}

	if (strlen(loc) == 5){ /* segment for direct move */
		loc+=3;
		int destCell = toID(loc);
		loc-=3;
		if (destCell == -2){
			printe(entryFormat);
			free(loc);
			return;
		}
		cell *tmp = getCell(cellID, board);
		if (tmp->piece->player == black && board->turn % 2 == 0){
			/* offSides black trying to move white */
			printe(offSides);
			free(loc);
			return;
		}
		else if (tmp->piece->player == white && board->turn % 2 == 1){
			/* offSides white trying to move black */
			printe(offSides);
			free(loc);
			return;
		}
		moveSwitch(tmp->piece, destCell);
		free(loc);
		return;
	}
	else if (strlen(loc) == 2){ /* segment for selecting a piece */
		cell *tmp = getCell(cellID, board);
		if (tmp->piece == NULL){
			printe(emptyCell);
			free(loc);
			return;
		}
		checkAvailMovesSwitch(tmp->piece);
		free(loc);
		return;
	}
	printe(entryFormat);
	free(loc);
	return;
}

void checkAvailMovesSwitch(piece *piece){
	int *tmp = checkAvailMoves(piece);
	if (tmp == NULL || *tmp == -2){
		return;
	}
	printf("Possible locations for ");
	switch(piece->player){
		case white: printf("White "); break;
		case black: printf("Black "); break;
	}
	switch(piece->type){
		case pawn: printf("Pawn "); break;
		case bishop: printf("Bishop "); break;
		case king: printf("King "); break;
		case queen: printf("Queen "); break;
		case rook: printf("Rook "); break;
		case knight: printf("Knight "); break;
	}
	printf("in location ");
	printLoc(piece);
	while (*tmp != -2){
		printCell(*tmp);
		printf(" ");
		tmp++;
	}
	printf("\n");
}

void moveSwitch(piece *piece, int destCell){
	switch (movePiece(piece, getCell(destCell, piece->loc->board))){
		case -2: /* no available moves */
			printp(available, piece); 
			break;
		case 0: /* standard move or capture */
			/* nothing for now */
			break;
		case 1: /* pawn promotion */
			pawnPromotion(piece);
			break;
		/* another case for check/checkmate? */
	}
}

int toID(char *loc){ 
	
	if (strncmp("quit", loc, 4) == 0){ 
		return -3;
	}

	if (strncmp("exit", loc, 4) == 0){
		return -3;
	}
	
	if (strncmp("undo", loc, 4) == 0){
		return -4;
	}
	
	if (strncmp("a1", loc, 2) == 0) return 0;
	if (strncmp("b1", loc, 2) == 0) return 1;
	if (strncmp("c1", loc, 2) == 0) return 2;
	if (strncmp("d1", loc, 2) == 0) return 3;
	if (strncmp("e1", loc, 2) == 0) return 4;
	if (strncmp("f1", loc, 2) == 0) return 5;
	if (strncmp("g1", loc, 2) == 0) return 6;
	if (strncmp("h1", loc, 2) == 0) return 7;
	
	if (strncmp("a2", loc, 2) == 0) return 8;
	if (strncmp("b2", loc, 2) == 0) return 9;
	if (strncmp("c2", loc, 2) == 0) return 10;
	if (strncmp("d2", loc, 2) == 0) return 11;
	if (strncmp("e2", loc, 2) == 0) return 12;
	if (strncmp("f2", loc, 2) == 0) return 13;
	if (strncmp("g2", loc, 2) == 0) return 14;
	if (strncmp("h2", loc, 2) == 0) return 15;

	if (strncmp("a3", loc, 2) == 0) return 16;
	if (strncmp("b3", loc, 2) == 0) return 17;
	if (strncmp("c3", loc, 2) == 0) return 18;
	if (strncmp("d3", loc, 2) == 0) return 19;
	if (strncmp("e3", loc, 2) == 0) return 20;
	if (strncmp("f3", loc, 2) == 0) return 21;
	if (strncmp("g3", loc, 2) == 0) return 22;
	if (strncmp("h3", loc, 2) == 0) return 23;
	
	if (strncmp("a4", loc, 2) == 0) return 24;
	if (strncmp("b4", loc, 2) == 0) return 25;
	if (strncmp("c4", loc, 2) == 0) return 26;
	if (strncmp("d4", loc, 2) == 0) return 27;
	if (strncmp("e4", loc, 2) == 0) return 28;
	if (strncmp("f4", loc, 2) == 0) return 29;
	if (strncmp("g4", loc, 2) == 0) return 30;
	if (strncmp("h4", loc, 2) == 0) return 31;
	
	if (strncmp("a5", loc, 2) == 0) return 32;
	if (strncmp("b5", loc, 2) == 0) return 33;
	if (strncmp("c5", loc, 2) == 0) return 34;
	if (strncmp("d5", loc, 2) == 0) return 35;
	if (strncmp("e5", loc, 2) == 0) return 36;
	if (strncmp("f5", loc, 2) == 0) return 37;
	if (strncmp("g5", loc, 2) == 0) return 38;
	if (strncmp("h5", loc, 2) == 0) return 39;
	
	if (strncmp("a6", loc, 2) == 0) return 40;
	if (strncmp("b6", loc, 2) == 0) return 41;
	if (strncmp("c6", loc, 2) == 0) return 42;
	if (strncmp("d6", loc, 2) == 0) return 43;
	if (strncmp("e6", loc, 2) == 0) return 44;
	if (strncmp("f6", loc, 2) == 0) return 45;
	if (strncmp("g6", loc, 2) == 0) return 46;
	if (strncmp("h6", loc, 2) == 0) return 47;
	
	if (strncmp("a7", loc, 2) == 0) return 48;
	if (strncmp("b7", loc, 2) == 0) return 49;
	if (strncmp("c7", loc, 2) == 0) return 50;
	if (strncmp("d7", loc, 2) == 0) return 51;
	if (strncmp("e7", loc, 2) == 0) return 52;
	if (strncmp("f7", loc, 2) == 0) return 53;
	if (strncmp("g7", loc, 2) == 0) return 54;
	if (strncmp("h7", loc, 2) == 0) return 55;
	
	if (strncmp("a8", loc, 2) == 0) return 56;
	if (strncmp("b8", loc, 2) == 0) return 57;
	if (strncmp("c8", loc, 2) == 0) return 58;
	if (strncmp("d8", loc, 2) == 0) return 59;
	if (strncmp("e8", loc, 2) == 0) return 60;
	if (strncmp("f8", loc, 2) == 0) return 61;
	if (strncmp("g8", loc, 2) == 0) return 62;
	if (strncmp("h8", loc, 2) == 0) return 63;
	
	return -2;
}

