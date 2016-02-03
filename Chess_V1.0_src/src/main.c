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
 * Created on 2016-01-13
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "errors.h"
#include "defs.h"
#include "gameDisplay.h"
#include "ai.h"

int main(){
	int in_game=0;
	int turnPre=0;
	int mode=-1;	 	/*range 1-3*/
	int diff=-1; 		/*range 0-3, 0 if pvp*/
	int timer=-1;		/*range 0, 5, 10, 20*/
	int side=-1;        /*range '0' for white, '1' for black*/
	int all41 = -1;		/* range 0-5 depending on piece */
	char confirm='n';	/*range 'n', 'y'*/
	char modeS[26];
	char diffS[26];
	char timerS[26];
	board *board = createNewGame();
	int timer1 = 0;
	int timer2 = 0;
	int timer3 = 0;
	int timer4 = 0;
	int timer5 = 0;
	int altcounter = 1;
	do{	/*game setup*/
		printf("\nChess v1.0 by nøl / C Gets Degrees\n\n");
		while (mode < 1){
			printf("Please select game mode:\n");
			printf("1. Player versus Player\n");
			printf("2. Player versus Computer\n");
			printf("3. Computer versus Computer\n\n");
			scanf("%d", &mode);
			switch(mode){
				case 1:
					printf("Player versus Player selected\n");
					break;
				case 2:
					printf("Player versus Computer selected\n\n");
					printf("Choose a side: White(0) or Black(1)?\n");
					scanf("%d", &side);
					switch(side){
						case 0:
							printf("White selected\n");
							break;
						case 1:
							printf("Black selected\n");
							break;
						default:
							printe(selection);
							side = -1;
							break;
					}
					break;
				case 3:
					printf("Computer versus Computer selected\n");
					break;
				default:
					printe(selection);
					mode = -1;
					break;
			}
		}
		while (all41 < 0){
			printf("\nPlease select game type. All-for-One mode creates all pieces of the same type!\n");
			printf("0. Standard Chess\n");
			printf("1. All-for-Pawn\n");
			printf("2. All-for-Knight\n");
			printf("3. All-for-Queen\n");
			printf("4. All-for-Rook\n");
			printf("5. All-for-Bishop\n");
			scanf("%d", &all41);
			switch(all41){
				case 0:
					printf("Standard chess selected\n");
					break;
				case 1:
					printf("All-for-Pawn selected\n");
					break;
				case 2:
					printf("All-for-Knight selected\n");
					break;
				case 3:
					printf("All-for-Queen selected\n");
					break;
				case 4:
					printf("All-for-Rook selected\n");
					break;
				case 5:
					printf("All-for-Bishop selected\n");
					break;
				default:
					printe(selection);
					all41 = -1;
					break;
			}
		}
		while (diff < 0){
			if (mode == 1){
				diff = 0;
				break;
			}
			printf("\nPlease select computer difficulty:\n");
			printf("1. Easy\n");
			printf("2. Medium\n");
			printf("3. Hard\n\n");
			scanf("%d", &diff);
			switch(diff){
				case 1:
					printf("Easy selected\n");
					break;
				case 2:
					printf("Medium selected\n");
					break;
				case 3:
					printf("Hard selected\n");
					break;
				default:
					printe(selection);
					diff = -1;
					break;
			}
		}
		while (timer < 0){
			printf("\nPlease select game timer length:\n");
			printf("0. No limit\n");
			printf("5. 5 minutes\n");
			printf("10. 10 minutes\n");
			printf("20. 20 minutes\n\n");
			scanf("%d", &timer);
			switch(timer){
				case 0:
					printf("No limit selected\n");
					timer = 0;
					break;
				case 5:
					printf("5 minutes selected\n");
					timer1 = timer*60;
					timer3 = timer*60;
					break;
				case 10:
					printf("10 minutes selected\n");
					timer1 = timer*60;
					timer3 = timer*60;
					break;
				case 20:
					printf("20 minutes selected\n");
					timer1 = timer*60;
					timer3 = timer*60;
					break;
				default:
					printe(selection);
					timer1 = 0;
					timer3 = 0;
					timer = -1;
					break;
			}
		}
		/*CREATE STRINGS FOR SELECTIONS*/
		switch(mode){
			case 1:
				strcpy(modeS, "Player versus Player");
				break;
			case 2:
				strcpy(modeS, "Player versus Computer");
				break;
			case 3:
				strcpy(modeS, "Computer versus Computer");
				break;
		}
		switch(diff){
			case 0:
				strcpy(diffS, "");
				break;
			case 1:
				strcpy(diffS, "\nDifficulty: Easy");
				break;
			case 2:
				strcpy(diffS, "\nDifficulty: Medium");
				break;
			case 3:
				strcpy(diffS, "\nDifficulty: Hard");
				break;
		}
		switch(timer){
			case 0:
				strcpy(timerS, "No time limit");
				break;
			case 5:
				strcpy(timerS, "5 minutes");
				break;
			case 10:
				strcpy(timerS, "10 minutes");
				break;
			case 20:
				strcpy(timerS, "20 minutes");
				break;
		}
		/*CONFIRM SELECTIONS*/
		printf("\n\nPlease confirm selections: [y/n]\n\n");
		printf("Mode: %s", modeS);
		printf("%s", diffS);
		printf("\nTimer: %s\n\n", timerS);
		scanf(" %c", &confirm);

		if (confirm == 'y' || confirm == 'Y'){
			in_game = 1;
			fgetc(stdin); /* absorb the /n produced by the last scanf */
			createMoveLog();
		}
		else if (confirm == 'n' || confirm == 'N'){
			mode = -1;
			side = -1;
			diff = -1;
			timer = -1;
			all41 = -1;
		}
		else{
			printe(selection);
		}
		
		int aiTeam1, aiTeam2;
		if(mode == 2){ /* Inverts input value 0 -> 1, 1 -> 0, other input will cause assertion failure */
			aiTeam1 = oppTeam(side); /* oppTeam function comes from ai.c. Reads an int, returns an int. */
		}
		if(mode == 3){ /* Default for CPU vs CPU */
			aiTeam1 = 0;
			aiTeam2 = 1;
		}
		
		while(in_game){ /* if side = 1, player is black */
			if (timer != 0){
				/* set up timer */
				if (altcounter % 2 != 0){
					timer5 = timer4 - timer2;
					timer1 = timer1 - timer5;
					altcounter = altcounter+1;
				}
				else{
					timer5 = timer4 - timer2;
					timer3 = timer3 - timer5;
					altcounter = altcounter+1;
				}
				if (timer1 <= 0){
				printf("\nWhite has run out of time!\n");
				exit(0);
				}
				if (timer3 <= 0){
					printf("\nBlack has run out of time!\n");
					exit(0);
				}
			}
			int alpha;
			cell *tmp1;
			switch(all41){
				case 0:
				break;
				case 1:
					for(alpha = 0; alpha <64; alpha++){
						tmp1 = getCell(alpha, board);
						if (tmp1->piece != NULL && tmp1->piece->type != king){
							tmp1->piece->type = pawn;
							updatePrintPiece(tmp1);
						}
					}
					break;
				case 2:
					for(alpha = 0; alpha <64; alpha++){
						tmp1 = getCell(alpha, board);
						if (tmp1->piece != NULL && tmp1->piece->type != king){
							tmp1->piece->type = knight;
							updatePrintPiece(tmp1);
						}
					}
					break;
				case 3:
					for(alpha = 0; alpha <64; alpha++){
						tmp1 = getCell(alpha, board);
						if (tmp1->piece != NULL && tmp1->piece->type != king){
							tmp1->piece->type = queen;
							updatePrintPiece(tmp1);
						}
					}
					break;
				case 4:
					for(alpha = 0; alpha <64; alpha++){
						tmp1 = getCell(alpha, board);
						if (tmp1->piece != NULL && tmp1->piece->type != king){
							tmp1->piece->type = rook;
							updatePrintPiece(tmp1);
						}
					}
					break;
				case 5:
					for(alpha = 0; alpha <64; alpha++){
						tmp1 = getCell(alpha, board);
						if (tmp1->piece != NULL && tmp1->piece->type != king){
							tmp1->piece->type = bishop;
							updatePrintPiece(tmp1);
						}
					}
					break;
			}
			
			turnPre = board->turn;
			timer2 = (int) time(NULL);
			updateGameDisplay(board); /* display the entire board only when its a new turn */
			while (turnPre == board->turn){
				cell *temp;
				switch(mode){
					case 1: /* PvP */ 
						updateMessage(board);
						/*board->turn++;*/
						break;
					case 2: /* P vs AI */
						if(board->turn%2 == aiTeam1){ /* AI's turn */
							printMessage(board->turn);
							if (board->turn == 0){
								temp = getCell(12, board);
								movePiece(temp->piece, getCell(20, board));
								temp = NULL;
							}
							else if (board->turn == 1){
								temp = getCell(52, board);
								movePiece(temp->piece, getCell(44, board));
							}
							else if (board->turn == 2){
								temp = getCell(3, board);
								movePiece(temp->piece, getCell(21, board));
							}
							else if (board->turn == 3){
								temp = getCell(59, board);
								movePiece(temp->piece, getCell(45, board));
							}
							else if (board->turn == 4){
								temp = getCell(5, board);
								movePiece(temp->piece, getCell(26, board));
							}
							else if (board->turn == 5){
								temp = getCell(61, board);
								movePiece(temp->piece, getCell(34, board));
							}
							else if (board->turn == 6){
								temp = getCell(21, board);
								movePiece(temp->piece, getCell(53, board));
							}
							else if (board->turn == 7){
								temp = getCell(45, board);
								movePiece(temp->piece, getCell(13, board));
							}
							else{
								aiMove(diff, aiTeam1, board);
							}
						}
						else{
							/* player's turn */
							updateMessage(board);
							/*board->turn++;*/
						}
						break;
					case 3: /* AI vs AI*/
						if(board->turn%2 == 0){ /* White's turn */
							/* aiTeam1 goes */
							printMessage(board->turn);
							aiMove(diff, aiTeam1, board);
							/*board->turn++;*/
						}
						else{ /* Black's turn */
							/* aiTeam2 goes */
							printMessage(board->turn);
							aiMove(diff, aiTeam2, board);
							/*board->turn++;*/
						}
						break;
				}
				/* Exits loop when turn is finished */
			}
			timer4 = (int) time(NULL);
			if (timer != 0 && board->turn > 1){
				printf("DEBUG: Current time: %d\n", timer4);
				printf("DEBUG: Current time: %d\n", timer2);
				printf("Time remaining for Player 1: %d seconds.\n", timer1);
				printf("Time remaining for Player 2: %d seconds.\n", timer3);
			}
		}
			
	}
	while(!in_game);
	
		
	return 0;
}
