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
#include "gameDisplay.h"

int main(){
	int in_game=0;
	int turnPre=0;
	int mode=-1;	 	/*range 1-3*/
	int diff=-1; 		/*range 0-3, 0 if pvp*/
	int timer=-1;		/*range 0, 5, 10, 20*/
	int side=-1;        /*range '0' for white, '1' for black*/
	char confirm='n';	/*range 'n', 'y'*/
	char modeS[26];
	char diffS[26];
	char timerS[26];
	board *board = createNewGame();
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
					break;
				case 5:
					printf("5 minutes selected\n");
					break;
				case 10:
					printf("10 minutes selected\n");
					break;
				case 20:
					printf("20 minutes selected\n");
					break;
				default:
					printe(selection);
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
		}
		else if (confirm == 'n' || confirm == 'N'){
			mode = -1;
			diff = -1;
			timer = -1;
		}
		else{
			printe(selection);
		}
		
		while(in_game){ /* if side = 1, player is black */
			/* if mode = 2 or 3, set up AI. if timer !=0, set up timer */
			turnPre = board->turn;
			updateGameDisplay(board); /* display the entire board only when its a new turn */
			while (turnPre == board->turn){
				updateMessage(board);
			}
		}
			
	}
	while(!in_game);
	
		
	return 0;
}
