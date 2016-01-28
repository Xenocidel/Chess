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

int turn=0;
int pieceSelected=0;

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
	printMessage(turn);
	
	/*handleInput();*/
}

void printMessage(int turn){ /* for turns: white = even, black = odd */
	if (turn == 0){
		printf("Select a piece by typing its location like: a1\nAlternatively, you may directly move a piece by typing its location and its destination like: a2 a3");
	}
	if (turn%2 == 0){
		printf("White's turn\n");
	}
	else{
		printf("Black's turn\n");
	}
	
	printf("\n>");
}
/*
void handleInput(){
	char *loc;
	fgets(loc, 5, stdin);
	int cellID = toID(loc);
	if (cellID == -2){
		printe(entry);
	}
	if (cellID == -3){
		exit(0);
	}
	if (strlen(loc) == 4){
		loc+=2;
		
	}
	switch (movePiece(cellID->piece, destCell)){
		case -2:
			printp(cellID->piece);
			break;
		case 1:
			pawnPromotion(cellID->piece);
			break;
		
	}
}

int toID(char *loc){ 
	if (strncmp("quit", loc, 4) == 0 || strncmp("exit", loc, 4 == 0))
		return -3;
	
	if (2 == strlen(loc) && strncmp("a1", loc, 2) == 0) return 0;
	if (2 == strlen(loc) && strncmp("b1", loc, 2) == 0) return 1;
	if (2 == strlen(loc) && strncmp("c1", loc, 2) == 0) return 2;
	if (2 == strlen(loc) && strncmp("d1", loc, 2) == 0) return 3;
	if (2 == strlen(loc) && strncmp("e1", loc, 2) == 0) return 4;
	if (2 == strlen(loc) && strncmp("f1", loc, 2) == 0) return 5;
	if (2 == strlen(loc) && strncmp("g1", loc, 2) == 0) return 6;
	if (2 == strlen(loc) && strncmp("h1", loc, 2) == 0) return 7;
	
	if (2 == strlen(loc) && strncmp("a2", loc, 2) == 0) return 8;
	if (2 == strlen(loc) && strncmp("b2", loc, 2) == 0) return 9;
	if (2 == strlen(loc) && strncmp("c2", loc, 2) == 0) return 10;
	if (2 == strlen(loc) && strncmp("d2", loc, 2) == 0) return 11;
	if (2 == strlen(loc) && strncmp("e2", loc, 2) == 0) return 12;
	if (2 == strlen(loc) && strncmp("f2", loc, 2) == 0) return 13;
	if (2 == strlen(loc) && strncmp("g2", loc, 2) == 0) return 14;
	if (2 == strlen(loc) && strncmp("h2", loc, 2) == 0) return 15;

	if (2 == strlen(loc) && strncmp("a3", loc, 2) == 0) return 16;
	if (2 == strlen(loc) && strncmp("b3", loc, 2) == 0) return 17;
	if (2 == strlen(loc) && strncmp("c3", loc, 2) == 0) return 18;
	if (2 == strlen(loc) && strncmp("d3", loc, 2) == 0) return 19;
	if (2 == strlen(loc) && strncmp("e3", loc, 2) == 0) return 20;
	if (2 == strlen(loc) && strncmp("f3", loc, 2) == 0) return 21;
	if (2 == strlen(loc) && strncmp("g3", loc, 2) == 0) return 22;
	if (2 == strlen(loc) && strncmp("h3", loc, 2) == 0) return 23;
	
	if (2 == strlen(loc) && strncmp("a4", loc, 2) == 0) return 24;
	if (2 == strlen(loc) && strncmp("b4", loc, 2) == 0) return 25;
	if (2 == strlen(loc) && strncmp("c4", loc, 2) == 0) return 26;
	if (2 == strlen(loc) && strncmp("d4", loc, 2) == 0) return 27;
	if (2 == strlen(loc) && strncmp("e4", loc, 2) == 0) return 28;
	if (2 == strlen(loc) && strncmp("f4", loc, 2) == 0) return 29;
	if (2 == strlen(loc) && strncmp("g4", loc, 2) == 0) return 30;
	if (2 == strlen(loc) && strncmp("h4", loc, 2) == 0) return 31;
	
	if (2 == strlen(loc) && strncmp("a5", loc, 2) == 0) return 32;
	if (2 == strlen(loc) && strncmp("b5", loc, 2) == 0) return 33;
	if (2 == strlen(loc) && strncmp("c5", loc, 2) == 0) return 34;
	if (2 == strlen(loc) && strncmp("d5", loc, 2) == 0) return 35;
	if (2 == strlen(loc) && strncmp("e5", loc, 2) == 0) return 36;
	if (2 == strlen(loc) && strncmp("f5", loc, 2) == 0) return 37;
	if (2 == strlen(loc) && strncmp("g5", loc, 2) == 0) return 38;
	if (2 == strlen(loc) && strncmp("h5", loc, 2) == 0) return 39;
	
	if (2 == strlen(loc) && strncmp("a6", loc, 2) == 0) return 40;
	if (2 == strlen(loc) && strncmp("b6", loc, 2) == 0) return 41;
	if (2 == strlen(loc) && strncmp("c6", loc, 2) == 0) return 42;
	if (2 == strlen(loc) && strncmp("d6", loc, 2) == 0) return 43;
	if (2 == strlen(loc) && strncmp("e6", loc, 2) == 0) return 44;
	if (2 == strlen(loc) && strncmp("f6", loc, 2) == 0) return 45;
	if (2 == strlen(loc) && strncmp("g6", loc, 2) == 0) return 46;
	if (2 == strlen(loc) && strncmp("h6", loc, 2) == 0) return 47;
	
	if (2 == strlen(loc) && strncmp("a7", loc, 2) == 0) return 48;
	if (2 == strlen(loc) && strncmp("b7", loc, 2) == 0) return 49;
	if (2 == strlen(loc) && strncmp("c7", loc, 2) == 0) return 50;
	if (2 == strlen(loc) && strncmp("d7", loc, 2) == 0) return 51;
	if (2 == strlen(loc) && strncmp("e7", loc, 2) == 0) return 52;
	if (2 == strlen(loc) && strncmp("f7", loc, 2) == 0) return 53;
	if (2 == strlen(loc) && strncmp("g7", loc, 2) == 0) return 54;
	if (2 == strlen(loc) && strncmp("h7", loc, 2) == 0) return 55;
	
	if (2 == strlen(loc) && strncmp("a8", loc, 2) == 0) return 56;
	if (2 == strlen(loc) && strncmp("b8", loc, 2) == 0) return 57;
	if (2 == strlen(loc) && strncmp("c8", loc, 2) == 0) return 58;
	if (2 == strlen(loc) && strncmp("d8", loc, 2) == 0) return 59;
	if (2 == strlen(loc) && strncmp("e8", loc, 2) == 0) return 60;
	if (2 == strlen(loc) && strncmp("f8", loc, 2) == 0) return 61;
	if (2 == strlen(loc) && strncmp("g8", loc, 2) == 0) return 62;
	if (2 == strlen(loc) && strncmp("h8", loc, 2) == 0) return 63;
	
	return -2;
}
*/
/*//Message bar for the player to select options.

	//Option for undoing last movement
	printf("If you want to undo your last Chess move type undo.\n\n");
	scanf("%c, &c");
	if (c = undo){
		printf("The Undo function is currently unavailable, please try later.\n\n");
	}
	else{
		printf("Unknown command. Please try again.\n\n");
	}

	//If the player wants to quit the game
	int a, b, c, move, quit = 0, exit = 0, Exit = 0; Quit = 0;
	quit = 0;
	printf("If you want to quit the game type quit or exit.\n");
	scanf("%c", &c);
	if (c = quit || exit || Quit || Exit){
		return(0);
	}
	else{
		printf("Unknown command. Please try again.\n\n");
	}

	//Player moves a piece using two board location


	cell *tmp = getCell(input, board);
	movePiece(tmp->piece, getCell(input2, board));

		//If Piece is in the actual location
		int input;
		printf("Please type the current location of your piece.");
		scanf(%s, &input);
		if (input = ""){
			printf("Please input where you want to move this piece.");
		}
		//If theres np piece in that location
		else{
			printf("Invalid selection.Please try again.\n\n");
		}
	}
}*/

