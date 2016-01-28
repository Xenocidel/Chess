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
	printMessage();
	int tmp;
	scanf("%d", &tmp);
	printf("This concludes the alpha preview of Chess. Please run MovesTest if you wish to test game logic.\n\n");
	/*handleInput();*/
}

void printMessage(){
	printf("White's turn\n");
	printf("Please select a piece by typing its location like a1\n");
	
}
/*
void handleInput(){
	char loc[3];
	fgets(loc, 2, stdin);
	int cellID = toID(loc);
	if (cellID == -2){
		printe(selection);
	}
	if (cellID == -3){
		exit(0);
	}
}
int toID(char loc[]){

	if (loc == "a1") return 0;
	if (loc == "b1") return 1;
	if (loc == "c1") return 2;
	if (loc == "d1") return 3;
	if (loc == "e1") return 4;
	if (loc == "f1") return 5;
	if (loc == "g1") return 6;
	if (loc == "h1") return 7;
	
	if (loc == "a2") return 8;
	if (loc == "b2") return 9;
	if (loc == "c2") return 10;
	if (loc == "d2") return 11;
	if (loc == "e2") return 12;
	if (loc == "f2") return 13;
	if (loc == "g2") return 14;
	if (loc == "h2") return 15;
	
	if (loc == "a3") return 16;
	if (loc == "b3") return 17;
	if (loc == "c3") return 18;
	if (loc == "d3") return 19;
	if (loc == "e3") return 20;
	if (loc == "f3") return 21;
	if (loc == "g3") return 22;
	if (loc == "h3") return 23;
	
	if (loc == "a4") return 24;
	if (loc == "b4") return 25;
	if (loc == "c4") return 26;
	if (loc == "d4") return 27;
	if (loc == "e4") return 28;
	if (loc == "f4") return 29;
	if (loc == "g4") return 30;
	if (loc == "h4") return 31;
	
	if (loc == "a5") return 32;
	if (loc == "b5") return 33;
	if (loc == "c5") return 34;
	if (loc == "d5") return 35;
	if (loc == "e5") return 36;
	if (loc == "f5") return 37;
	if (loc == "g5") return 38;
	if (loc == "h5") return 39;
	
	if (loc == "a6") return 40;
	if (loc == "b6") return 41;
	if (loc == "c6") return 42;
	if (loc == "d6") return 43;
	if (loc == "e6") return 44;
	if (loc == "f6") return 45;
	if (loc == "g6") return 46;
	if (loc == "h6") return 47;
	
	if (loc == "a7") return 48;
	if (loc == "b7") return 49;
	if (loc == "c7") return 50;
	if (loc == "d7") return 51;
	if (loc == "e7") return 52;
	if (loc == "f7") return 53;
	if (loc == "g7") return 54;
	if (loc == "h7") return 55;
	
	if (loc == "a8") return 56;
	if (loc == "b8") return 57;
	if (loc == "c8") return 58;
	if (loc == "d8") return 59;
	if (loc == "e8") return 60;
	if (loc == "f8") return 61;
	if (loc == "g8") return 62;
	if (loc == "h8") return 63;
	
	if (loc == "qu" || loc == "ex") return -3;
	
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

