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
*                                                                              *
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

int check = 0; /* 1-3 depending on check, checkmate, or stalemate */

void updateGameDisplay(board *board){
	printf("\n");
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
		printf("White pieces are displayed in CAPITALS. Black pieces are displayed in lowercase\n\nMove a piece by typing its location and its destination like: a2 a3 or a2a3\nYou can also see a piece's available moves by typing its location like: a1\n\nLoad a game by typing load (see user manual for more instructions)\n\nTo bring up these instructions again, type help\nExit the game by typing exit or quit\n\n");
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
			if (loc) free(loc);
			return;
		}
	}
	int cellID = toID(loc);
	if (cellID == -2){
		printe(command);
		if (loc) free(loc);
		return;
	}
	if (cellID == -3){
		/* todo: maybe deleteBoard and deleteAllCells? */
		if (loc) free(loc);
		exit(0);
	}
	if (cellID == -4){
		/* undo */
		int undoTurns = board->turn;
		undoTurns -= 2;
		if (undoTurns < 0){
			printf("You have not made a move yet!\n\n");
			if (loc) free(loc);
			return;
		}
		deleteAllCells(board);
		deleteBoard(board);
		board = createNewGame();
		loadUndo("log_loadable.txt", "log_loadable2.txt", board, undoTurns);
		if (loc) free(loc);
		return;
	}
	if (cellID == -5){ /* display help */
		if (board->turn != 0){
			printf("White pieces are displayed in CAPITALS. Black pieces are displayed in lowercase\n\nMove a piece by typing its location and its destination like: a2 a3 or a2a3\nYou can also see a piece's available moves by typing its location like: a1\n\nLoad a game by typing load (see user manual for more instructions)\n\nTo bring up these instructions again, type help\nExit the game by typing exit or quit\n\n");
		}
		if (loc) free(loc);
		return;
	}
	if (cellID == -6){
		printf("Please type the file name to load from, including the extension\n");
		char fname[63];
		fgets(fname, 63, stdin);
		char *tmp;
		if ((tmp = strchr(fname, '\n')) != NULL){ /*cuts off \n at the end of each input*/
			*tmp = '\0';
		}
		loadGame(fname, board);
		return;
	}

	if (strlen(loc) == 5 || strlen(loc) == 4){ /* segment for direct move */
		int loclen = strlen(loc)-2;
		loc += loclen;
		int destCell = toID(loc);
		loc -= loclen;
		if (destCell == -2){
			printe(entryFormat);
			if (loc) free(loc);
			return;
		}
		cell *tmp = getCell(cellID, board);
		if (tmp->piece == NULL){
			printe(emptyCell);
			if (loc) free(loc);
			return;
		}
		if (tmp->piece->player == black && board->turn % 2 == 0){
			/* offSides black trying to move white */
			printe(offSides);
			if (loc) free(loc);
			return;
		}
		else if (tmp->piece->player == white && board->turn % 2 == 1){
			/* offSides white trying to move black */
			printe(offSides);
			if (loc) free(loc);
			return;
		}
		
		/* checkCode is 1 if in check, 2 if checkmate, 3 if stalemate */
		int checkCode = moveSwitch(tmp->piece, destCell);
		switch (checkCode){
			case 1:
				printf("You are in check!\n\n");
				break;
			case 2:
				printf("Checkmate! Game over!\n\n");
				/* todo: deleteBoard and deleteAllCells? */
				exit(0);
			case 3:
				printf("Stalemate! Game over!\n\n");
				/* todo: deleteBoard and deleteAllCells? */
				exit(0);
		}
		
		if (loc) free(loc);
		return;
	}
	else if (strlen(loc) == 2){ /* segment for selecting a piece */
		cell *tmp = getCell(cellID, board);
		if (tmp->piece == NULL){
			printe(emptyCell);
			if (loc) free(loc);
			return;
		}
		checkAvailMovesSwitch(tmp->piece);
		if (loc) free(loc);
		return;
	}
	printe(entryFormat);
	if (loc) free(loc);
	return;
}

void checkAvailMovesSwitch(piece *piece){
	int *tmp = checkAvailMoves(piece);
	if (tmp == NULL || *tmp == -2){
		printp(available, piece);
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

int moveSwitch(piece *piece, int destCell){
	cell *dest = getCell(destCell, piece->loc->board);
	int capture = 0;
	int promo = 0; /* 1-4 depending on piece selected */
	int castle = 0; /* 2-3 depending on kingside or queenside */
	int mp = movePiece(piece, dest);
	switch (mp){
		case -2: /* no available moves */
			printp(available, piece); 
			break;
		case -1: /* invalid move */
			printe(move);
			break;
		case 0: /* standard move or capture */
		{	cell *prison = getCell(-1, piece->loc->board);
			if (prison->piece != NULL && prison->piece->prev == dest){
				capture = 1;
			}
			break;
		}
		case 1: /* pawn promotion */
		{	cell *prison = getCell(-1, piece->loc->board);	
			promo = pawnPromotion(piece);
			if (prison->piece != NULL && prison->piece->prev == dest){
				capture = 1;
			}
			fgetc(stdin); /* absorb the \n produced by scanf */
			break;
		}
		case 2: /*kingside castle*/
			castle = 2;
			break;
		case 3: /*queenside castle*/
			castle = 3;
			break;
	}

	if (mp>=0){
		int i;
		cell *tmp;
		for (i = 0; i < 63; i++){
			tmp = getCell(i, piece->loc->board);
			if (tmp->piece != NULL && tmp->piece->type == king){
				check = checkKingCheck(tmp->piece->loc->cellID, tmp->piece);
				int x, y=1;
				int *avail;
				cell *tmp2;
				while(y){
					/* if there are any available moves, it is a standard check */
					/* otherwise, checkmate if in check, stalemate if not */
					if (check == 1){
						check = 2; /* checkmate */
					}
					else if (check == 0){
						check = 3; /* stalemate */
					}
					for (x=0; x<64; x++){
						tmp2 = getCell(x, piece->loc->board);
						if (tmp2->piece != NULL){
							avail = checkAvailMoves(tmp2->piece);
							if (avail != NULL && *avail == -2){
								y=0;
								check = 1;
								break;
							}
						}
					}
					y=0;
				}
			}
		}

		
		writeMoveLog(piece->loc->board->turn-1, piece, capture, promo, castle, check); /* turn-1 to log the move that just occurred */
		
	}
	return check;
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
	
	if (strncmp("help", loc, 4) == 0){
		return -5;
	}
	
	if (strncmp("load", loc, 4) == 0){
		return -6;
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

/* initializes title bar for movelog */
void createMoveLog(){
	FILE * moveLog;
	moveLog = fopen("movelog.txt", "w");
	if (moveLog == NULL){
		printf("Error writing to move log. Skipping...\n\n");
		return;
	}
	fprintf(moveLog, "   White     Black\n");
	fclose(moveLog);
}

void createLoadableLog(){
	FILE * moveLogLoadable;
	moveLogLoadable = fopen("log_loadable.txt", "w");
	if (moveLogLoadable == NULL){
		printf("Error writing to move log. Skipping...\n\n");
		return;
	}
	fclose(moveLogLoadable);
}


/*  promo 1-4 depending on piece selected (queen, knight, rook, bishop)
 *	castle 2-3 depending on kingside or queenside
 *	check 1-3 depending on check, checkmate, or stalemate
 */
void writeMoveLog(int turn, piece *p, int capture, int promo, int castle, int check){
	assert(p);
	int len=0;
	FILE * moveLog;
	FILE * moveLogLoadable;
	moveLogLoadable = fopen("log_loadable.txt", "a");

	if (moveLogLoadable == NULL){
		printf("Error writing to move log. Skipping...\n\n");
		return;
	}
	/* loadable move log */
	fprintf(moveLogLoadable, "%s", returnCell(p->prev->cellID));
	fprintf(moveLogLoadable, "%s\n", returnCell(p->loc->cellID));
	fclose(moveLogLoadable);
	
	/* formatted move log */
	moveLog = fopen("movelog.txt", "a");
	if (moveLog == NULL){
		printf("Error writing to move log. Skipping...\n\n");
		return;
	}
	
	if (turn%2 == 0){
		fprintf(moveLog, "%d. ", turn/2+1);
	}	
	if (!promo){
		switch (p->type){
		case pawn:
			fprintf(moveLog, "%s", returnCell(p->prev->cellID));
			if (capture)
				fprintf(moveLog, "x");
			else
				fprintf(moveLog, "-");
			fprintf(moveLog, "%s", returnCell(p->loc->cellID));
			len+=5;
			break;
		case knight:
			fprintf(moveLog, "N%s", returnCell(p->prev->cellID));
			if (capture)
				fprintf(moveLog, "x");
			else
				fprintf(moveLog, "-");
			fprintf(moveLog, "%s", returnCell(p->loc->cellID));
			len+=6;
			break;
		case king:
			if (castle == 2){
				fprintf(moveLog, "0-0");
				len+=3;
				break;
			}
			else if (castle == 3){
				fprintf(moveLog, "0-0-0");
				len+=5;
				break;
			}
			fprintf(moveLog, "K%s", returnCell(p->prev->cellID));
			if (capture)
				fprintf(moveLog, "x");
			else
				fprintf(moveLog, "-");
			fprintf(moveLog, "%s", returnCell(p->loc->cellID));
			len+=6;
			break;
		case queen:
			fprintf(moveLog, "Q%s", returnCell(p->prev->cellID));
			if (capture)
				fprintf(moveLog, "x");
			else
				fprintf(moveLog, "-");
			fprintf(moveLog, "%s", returnCell(p->loc->cellID));
			len+=6;
			break;
		case rook:
			fprintf(moveLog, "R%s", returnCell(p->prev->cellID));
			if (capture)
				fprintf(moveLog, "x");
			else
				fprintf(moveLog, "-");
			fprintf(moveLog, "%s", returnCell(p->loc->cellID));
			len+=6;
			break;
		case bishop:
			fprintf(moveLog, "B%s", returnCell(p->prev->cellID));
			if (capture)
				fprintf(moveLog, "x");
			else
				fprintf(moveLog, "-");
			fprintf(moveLog, "%s", returnCell(p->loc->cellID));
			len+=6;
			break;
		}
	}
	if(promo){
		fprintf(moveLog, "%s", returnCell(p->prev->cellID));
		if (capture)
			fprintf(moveLog, "x");
		else
			fprintf(moveLog, "-");
		fprintf(moveLog, "%s", returnCell(p->loc->cellID));
		len+=5;
		switch (promo){
			case 1:
				fprintf(moveLog, "Q");
				len++;
				break;
			case 2:
				fprintf(moveLog, "N");
				len++;
				break;
			case 3:
				fprintf(moveLog, "R");
				len++;
				break;
			case 4:
				fprintf(moveLog, "B");
				len++;
				break;
		}
	}
	switch(check){
		case 1:
			fprintf(moveLog, "+");
			len++;
			break;
		case 2:
			fprintf(moveLog, "#\n");
			if (turn % 2 == 0){
				fprintf(moveLog, "1-0");
				fclose(moveLog);
				return;
			}
			else{
				fprintf(moveLog, "0-1");
				fclose(moveLog);
				return;
			}
		case 3:
			fprintf(moveLog, "\n1/2-1/2");
			fclose(moveLog);
			return;
	}
	
	if (turn%2 != 0){
		fprintf(moveLog, "\n");
	}
	else{
		for (len = 10-len; len>0; len--){
			fprintf(moveLog, " ");
		}
	}
	fclose(moveLog);
}

const char * returnCell(int cellID){
	switch (cellID){
		case 0 : return "a1";
		case 8 : return "a2";
		case 16: return "a3";
		case 24: return "a4";
		case 32: return "a5";
		case 40: return "a6";
		case 48: return "a7";
		case 56: return "a8";
		case 1 : return "b1";
		case 9 : return "b2";
		case 17: return "b3";
		case 25: return "b4";
		case 33: return "b5";
		case 41: return "b6";
		case 49: return "b7";
		case 57: return "b8";
		case 2 : return "c1";
		case 10: return "c2";
		case 18: return "c3";
		case 26: return "c4";
		case 34: return "c5";
		case 42: return "c6";
		case 50: return "c7";
		case 58: return "c8";
		case 3 : return "d1";
		case 11: return "d2";
		case 19: return "d3";
		case 27: return "d4";
		case 35: return "d5";
		case 43: return "d6";
		case 51: return "d7";
		case 59: return "d8";
		case 4 : return "e1";
		case 12: return "e2";
		case 20: return "e3";
		case 28: return "e4";
		case 36: return "e5";
		case 44: return "e6";
		case 52: return "e7";
		case 60: return "e8";
		case 5 : return "f1";
		case 13: return "f2";
		case 21: return "f3";
		case 29: return "f4";
		case 37: return "f5";
		case 45: return "f6";
		case 53: return "f7";
		case 61: return "f8";
		case 6 : return "g1";
		case 14: return "g2";
		case 22: return "g3";
		case 30: return "g4";
		case 38: return "g5";
		case 46: return "g6";
		case 54: return "g7";
		case 62: return "g8";
		case 7 : return "h1";
		case 15: return "h2";
		case 23: return "h3";
		case 31: return "h4";
		case 39: return "h5";
		case 47: return "h6";
		case 55: return "h7";
		case 63: return "h8";
	}
	return "ERROR";
}

void loadGame(char *fname, board *board){
	FILE *file = fopen(fname, "r");
	if (!file){
		printf("\nCan't open file \"%s\" for reading!\n", fname);
		return;
	}
	char *loc = malloc(sizeof(char)*7);
	char *tmp;
	while (fgets(loc, 7, file)){
		if ((tmp = strchr(loc, '\r')) != NULL || (tmp = strchr(loc, '\n')) != NULL){ /*cuts off \r or \n at the end of each input*/
			*tmp = '\0';
		}
		int cellID = toID(loc);
		if (cellID == -2){
			printe(command);
			printf("Error occured while loading. Stopping...\n");
			
			return;
		}
		if (cellID == -3){
			/* todo: maybe deleteBoard and deleteAllCells? */
			
			exit(0);
		}
		if (cellID == -4){
			/* undo */
			printf("You may not recursively undo. Stopping...\n");
			
			return;
		}
		if (cellID == -5){ /* display help */
			if (board->turn != 0){
				printf("White pieces are displayed in CAPITALS. Black pieces are displayed in lowercase\n\nMove a piece by typing its location and its destination like: a2 a3 or a2a3\nYou can also see a piece's available moves by typing its location like: a1\n\nLoad a game by typing load (see user manual for more instructions)\n\nTo bring up these instructions again, type help\nExit the game by typing exit or quit\n\n");
			}
			
			return;
		}
		if (cellID == -6){
			printf("You may not recursively load. Stopping...\n");
			return;
		}

		if (strlen(loc) == 5 || strlen(loc) == 4){ /* segment for direct move */
			int loclen = strlen(loc)-2;
			loc += loclen;
			int destCell = toID(loc);
			loc -= loclen;
			if (destCell == -2){
				printe(entryFormat);
				return;
			}
			cell *tmp = getCell(cellID, board);
			if (tmp->piece == NULL){
				printe(emptyCell);
				
					
				return;
			}
			if (tmp->piece->player == black && board->turn % 2 == 0){
				/* offSides black trying to move white */
				printe(offSides);
				
					
				return;
			}
			else if (tmp->piece->player == white && board->turn % 2 == 1){
				/* offSides white trying to move black */
				printe(offSides);
				
					
				return;
			}
			int checkCode = moveSwitch(tmp->piece, destCell);
			if (checkCode){
				/* if all pieces have no available moves, stalemate */
				int x;
				cell *tmp2;
				int *avail;
				for (x=0; x<64; x++){
					tmp2 = getCell(x, board);
					if (tmp2->piece != NULL){
						avail = checkAvailMoves(tmp2->piece);
						if (!(avail == NULL || (avail != NULL && *avail == -2))){
							break;
						}
					}
					checkCode = 2;
				}
				checkCode = 0;
			}
			switch (checkCode){
				case 1:
					printf("You are in check!\n\n");
					continue;
				case 2:
					printf("Checkmate! Game over!\n\n");
					/* todo: deleteBoard and deleteAllCells? */
					exit(0);
				case 3:
					printf("Stalemate! Game over!\n\n");
					/* todo: deleteBoard and deleteAllCells? */
					exit(0);
			}
			
			continue;
		}
		else if (strlen(loc) == 2){ /* segment for selecting a piece */
			cell *tmp = getCell(cellID, board);
			if (tmp->piece == NULL){
				printe(emptyCell);
				
				continue;
			}
			checkAvailMovesSwitch(tmp->piece);
			
			continue;
		}
		printe(entryFormat);
		
		continue;
	}
	printf("Game loaded!\n");
	free(loc);
}

void loadUndo(char *fname, char *fname2, board *board, int undoTurns){
	FILE *file = fopen(fname, "r");
	if (!file){
		printf("\nCan't open file \"%s\" for reading!\n", fname);
		return;
	}
	FILE *backup = fopen(fname2, "w");
	if (!backup){
		printf("\nCan't open file \"%s\" for reading!\n", fname);
		return;
	}
	char *loc = malloc(sizeof(char)*7);
	char *tmp;
	int num=0;
	while (num < undoTurns){ /* copy file (fname) contents to backup (fname2) */
		fprintf(backup, fgets(loc, 7, file));
		num++;
	}
	
	fclose(file);
	fclose(backup);
	backup = fopen(fname, "w"); /* empty out fname and switch it w/ fname2 */
	fclose(backup);
	file = fopen(fname2, "r");
	num=0;
	
	createMoveLog();
	
	while (num < undoTurns && fgets(loc, 7, file)){
		if ((tmp = strchr(loc, '\r')) != NULL || (tmp = strchr(loc, '\n')) != NULL){ /*cuts off \r or \n at the end of each input*/
			*tmp = '\0';
		}
		int cellID = toID(loc);
		if (cellID == -2){
			printe(command);
			printf("Error occured while loading. Stopping...\n");
			
			return;
		}
		if (cellID == -3){
			/* todo: maybe deleteBoard and deleteAllCells? */
			
			exit(0);
		}
		if (cellID == -4){
			/* undo */
			printf("You may not recursively undo. Stopping...\n");
			return;
		}
		if (cellID == -5){ /* display help */
			if (board->turn != 0){
				printf("White pieces are displayed in CAPITALS. Black pieces are displayed in lowercase\n\nMove a piece by typing its location and its destination like: a2 a3 or a2a3\nYou can also see a piece's available moves by typing its location like: a1\n\nLoad a game by typing load (see user manual for more instructions)\n\nTo bring up these instructions again, type help\nExit the game by typing exit or quit\n\n");
			}
			
			return;
		}
		if (cellID == -6){
			printf("You may not recursively load. Stopping...\n");
			return;
		}

		if (strlen(loc) == 5 || strlen(loc) == 4){ /* segment for direct move */
			int loclen = strlen(loc)-2;
			loc += loclen;
			int destCell = toID(loc);
			loc -= loclen;
			if (destCell == -2){
				printe(entryFormat);
				return;
			}
			cell *tmp = getCell(cellID, board);
			if (tmp->piece == NULL){
				printe(emptyCell);
				
					
				return;
			}
			if (tmp->piece->player == black && board->turn % 2 == 0){
				/* offSides black trying to move white */
				printe(offSides);
				
					
				return;
			}
			else if (tmp->piece->player == white && board->turn % 2 == 1){
				/* offSides white trying to move black */
				printe(offSides);
				
					
				return;
			}
			int checkCode = moveSwitch(tmp->piece, destCell);
			num++;
			if (checkCode){
				/* if all pieces have no available moves, stalemate */
				int x;
				cell *tmp2;
				int *avail;
				for (x=0; x<64; x++){
					tmp2 = getCell(x, board);
					if (tmp2->piece != NULL){
						avail = checkAvailMoves(tmp2->piece);
						if (!(avail == NULL || (avail != NULL && *avail == -2))){
							break;
						}
					}
					checkCode = 2;
				}
				checkCode = 0;
			}
			switch (checkCode){
				case 1:
					printf("You are in check!\n\n");
					continue;
				case 2:
					printf("Checkmate! Game over!\n\n");
					/* todo: deleteBoard and deleteAllCells? */
					exit(0);
				case 3:
					printf("Stalemate! Game over!\n\n");
					/* todo: deleteBoard and deleteAllCells? */
					exit(0);
			}
			
			continue;
		}
		else if (strlen(loc) == 2){ /* segment for selecting a piece */
			cell *tmp = getCell(cellID, board);
			if (tmp->piece == NULL){
				printe(emptyCell);
				
				continue;
			}
			checkAvailMovesSwitch(tmp->piece);
			
			continue;
		}
		printe(entryFormat);
		
		continue;
	}
	printf("Move undone.\n");
	free(loc);
	fclose(file);
}

