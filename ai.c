#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "errors.h"
#include "defs.h"
#include "board.h"
#include "piece.h"

int aiMove(int diff, int team, board *board){
	switch(diff){
		case(1): /* easy */
			easyMove(team, board);
			break;
		case(2): /* medium */
			medMove(team, board);
			break;
		case(3): /* hard */
			hardMove(team, board);
			break;
		default:
			printf("Missing difficulty parameter.\n");
			break;
	}
	return NULL;
}

void easyMove(int team, board *board){
	
}
void medMove(int team, board *board){
	
}
void hardMove(int team, board *board){
	int *aiTeamPos = checkPiecePos(team, board);
	int opTeam = (team == 1) ? 0 : 1;
	int *opTeamPos = checkPiecePos(opTeam, board);
	
	/* check moves cell by cell */
	int entry = 0;
	while(aiTeamPos){
		cell *read = getCell(*(aiTeamPos+entry), board)
		int *aiList = checkAvailMoves(read->piece);
		if(*(aiTeamPos+entry) == -2){
			break;
		}
		entry++;
	}
	
	/* Freeing memory */
	/* deletecell read, free aiList */
	free(aiTeamPos);
	free(opTeamPos);
}

/* Returns pointer to list of specified team's piece locations */
int *checkPiecePos(int team, board *board){
	int *cellList = malloc(sizeof(int)*17);
	int entry = 0;
	int checkTeam = -1;
	int i;
	for(i=0; i<64; i++){
		cell *read = getCell(i, board);
		if(read->piece != NULL){
			if(read->piece->player == white){ /* 0 = white, 1 = black */
				checkTeam = 0;
			}
			else{
				checkTeam = 1;
			}
			if(checkTeam == team){
				*(cellList+entry) = i;
				entry++;
			}
		}
	}
	*(cellList+entry) = -2;
	return cellList;
}