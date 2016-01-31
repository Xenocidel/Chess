#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "errors.h"
#include "defs.h"
#include "board.h"
#include "piece.h"

int aiMove(int diff, int team, board *board){
	int lookAhead = -1; /* Number of moves AI will account for */
	switch(diff){
		case(1): /* Easy, AI accounts for 1 move ahead */
			lookAhead = 2;
			aiChoice(team, board, lookAhead);
			break;
		case(2): /* Medium, AI accounts for 2 additional moves */
			lookAhead = 3;
			aiChoice(team, board, lookAhead);
			break;
		case(3): /* Hard, AI accounts for 3 additional moves */
			lookAhead = 4;
			aiChoice(team, board, lookAhead);
			break;
		case(4): /* Mainly to quickly test AI moving functionality */
			randomMove(team, board);
			break;
		default:
			printf("Missing difficulty parameter.\n");
			break;
	}
	return NULL;
}

/* AI's move is determined by alpha-beta pruning */
/* aiChoice chooses and moves piece */
void aiChoice(int team, board *board, int lookAhd){
	/* runs calcABmax, which should determine the optimal piece & play */
	/* moves piece after selecting optimal move */
	int *piecePointer = 0;
	int *piecePositions = checkPiecePos(team, board);
	int *enemyPositions = checkPiecePos(oppTeam(team), board);
	moveValue *bestMax = CreateMoveValue(NULL, -5, -1000);
	moveValue *bestMin = CreateMoveValue(NULL, -5, 1000);
	moveValue *bestMove = calcABMax(piecePointer, piecePositions, enemyPositions, bestMax, bestMin, lookAhd, team, board);
	movePiece(bestMove->piece, getCell(bestMove->next, board));
	DeleteMoveValue(bestMax);
	DeleteMoveValue(bestMin);
	DeleteMoveValue(bestMove);
}

int oppTeam (int team) { /* Simple inversion function */
	return (team == 1) ? 0 : 1;
}

/* Allocates memory for a moveValue struct and assigns parameters as values */
moveValue *CreateMoveValue(piece *p, int next, int value){ /*Check the syntax to see if malloc is correct*/
	moveValue *move = malloc(sizeof(moveValue));
 	move->piece = p;
	move->next = next;
	move->value = CalcMoveValue(); 
	return move;
}

/*Frees the memory of a moveValue struct*/
void DeleteMoveValue(moveValue *move){
	assert(move);
	move->piece = NULL;
	move->next = 0;
	move->value = 0;
	free(move);
}

/* Compares the value of yoiur move with your previous best options (taking into consideration the opponent's moves as well)*/
moveValue *calcABmax(int *piecePointer, int *piecePositions, int *enemyPositions, moveValue *bestMax, moveValue *bestMin, int lookAhd, int team, board *board){
	/*  
	
	param piecePointer : integer that points to the element of the piece position array so that we can evaluate the piece's moves
	param bestMax : moveValue struct that corresponds to the best move for the AI
	param bestin : moveValue struct that corresponds to the worst move for the player
	param lookAhd : number of additional turns to account for
	param team : Player's team
	param board: The board
	
	*/
	if (*(piecePositions+(*piecePointer)) != -2) {
		if(lookAhd == 0){
			return calcMoveValue(team, board, getCell(*(piecePositions+(*piecePointer)),board)->cellID);
		}
		int i;
		moveValue *currMove = CreateMoveValue(NULL, -5, 0);
		for(i=0; i < totalMoveCount(team, board); i++ ) {
			currMove = calcABmin(piecePointer, piecePositions, enemyPositions, bestMax, bestMin, lookAhd-1, oppTeam(team), board);
			if (currMove->value >= bestMin->value) {
				
				DeleteMoveValue(currMove);
				*piecePointer++;
				return bestMin;
			}
			if (currMove->value > bestMax->value) {
				bestMax->piece = currMove->piece;
				bestMax->next = currMove->next;
				bestMax->value = currMove->value;
				DeleteMoveValue(currMove);
			} 
		}
	}
	return bestMax;
}

/*Compares the value of an opponent's move with the opponent's previous calculated worst move (taking into consideration the AI's moves as well)*/
moveValue *calcABmin(int *piecePointer, int *piecePositions, int *enemyPositions, moveValue *bestMax, moveValue *bestMin, int lookAhd, int team, board *board){
	/*  
	
	param piecePointer : integer that points to the element of the piece position array so that we can evaluate the piece's moves
	param bestMax : moveValue struct that corresponds to the best move for the AI
	param bestin : moveValue struct that corresponds to the worst move for the player
	param lookAhd : number of additional turns to account for
	param team : Opponent's team
	param board: The board
	
	*/
	
	if (*(piecePositions+(*piecePointer)) != -2) {
		if(lookAhd == 0){
			moveValue *nextMove = calcMoveValue(team, board, getCell(*(piecePositions+(*piecePointer)),board)-> cellID);
			nextMove->value *= -1; /* Inverts value when accounting for opponent moves */
			return nextMove;
		}
		int i;
		moveValue *currMove = CreateMoveValue(NULL, -5, 0);
		for(i=0; i < totalMoveCount(team, board); i++ ) {
			currMove = calcABmax(piecePointer, piecePositions, enemyPositions, bestMax, bestMin, lookAhd-1, oppTeam(team), board);
			if (currMove->value <= bestMax->value){
				DeleteMoveValue(currMove);
				*piecePointer++;
				return bestMax;
			}
			if (currMove->value < bestMin->value){ /*Replaces the BestMinimum with the newest calculated move (if the move is better)*/
				bestMin->piece = currMove->piece;
				bestMin->next = currMove->next;
				bestMin->value = currMove->value;
				DeleteMoveValue(currMove);
			}
		}
	}
	return bestMin;
}

/* Calculates the value of an individual move*/
moveValue *calcMoveValue(int team, board *board, int moveLoc){
	/*  1. Weigh the move based on an algorithm
		2. Return the moveValue struct corresponding to that move*/
	piece *p = getCell(moveLoc,board)->piece;
	int pawnValue = 1;
	int rookValue = 3;
	int bishopValue = 2;
	int knightValue = 3;
	int queenValue = 5;
	/* compare next moves */
	/* can ai capture piece? */
	/* how far piece is the piece moving */
	/* how far will piece be from enemy king */
	/* does move put piece in danger */
	int *piecePos = checkPiecePos(team, board);
	*(piecePos+i) /*  */
	/*
	if(would lose piece) points -= piece value
	if(would capture) points += piece value
	if (moves closer to center) + points
	if (moves closer to enemy king) + points
	if (moves away from center) -= points
	if (moves away from your king) -points
	*/
}

/* Basic move decision to quickly see if movement functions at a base level */
void randomMove(int team, board *board){
	int *aiTeamPos = checkPiecePos(team, board); /* Reads team locations */
	int opTeam = (team == 1) ? 0 : 1;
	int *opTeamPos = checkPiecePos(opTeam, board); /* Reads enemy locations */
	
	/* Check moves cell by cell. Currently unused, saving just in case. */
	/* int entry = 0;
	while(aiTeamPos){
		cell *read = getCell(*(aiTeamPos+entry), board)
		int *aiList = checkAvailMoves(read->piece);
		if(*(aiTeamPos+entry) == -2){
			break;
		}
		entry++;
	} */
	
	srand(time(NULL));
	int *pieceMoves;
	cell *moveCell;
	while(1){ /* Selects a random piece to move, and gets corresponding available moves */
		int rNum = rand()%17;
		cell *rCell = getCell(*(aiTeamPos+rNum), board);
		if(*(aiTeamPos+rNum) != -2){
			pieceMoves = checkAvailMoves(rCell->piece);
			moveCell = rCell;
			break;
		}
	}
	int count = 0;
	while(1){ /* Count number of available moves */
		if(*(pieceMoves+count) == -2){
			break;
		}
		count++;
	}
	int selNum = rand()%count;
	int move = *(pieceMoves+selNum);
	cell *nextCell = getCell(move, board);
	replacePiece(nextCell, moveCell->piece);
	
	/* Freeing memory */
	/* deletecell read, free aiList and pieceMoves */
	free(aiTeamPos); free(opTeamPos);
	deleteCell(nextCell);
}

/* Counts number of moves a piece can make */
int pieceMoveCount(piece *p) {
	int moveCount = 0;
	int *moveList = checkAIAvailMoves(p);
	while (1) {
		if (*(moveList) == -2 ) {
			free(moveList);
			return moveCount;
		}
		moveCount++;
		*(moveList++);
	}
}

/* Counts number of moves a player can make */
int totalMoveCount(int team, board *board) {
	int moveCount = 0;
	int pieceCount = 0;
	int *pieceList = checkPiecePos(team, board);
	while (1) { /* Counts amount of pieces for specified player */
		if (*(pieceList) == -2) {
			free(pieceList);
			break;
		}
		pieceCount++;
		*(pieceList++);
	
	}
	int i;
	for (i = 0; i < pieceCount; i++) { /* For loop goes through all of the pieces for one player on his/her 
										side of the board and calculates the total moves of all the pieces combined*/
		moveCount += pieceMoveCount( getCell(*pieceList,board)->piece );
		pieceList++;
	}
	/*Return the total number of moves available to one player*/
	return moveCount;
}

/* Version of checkAvailMoves modified for use with AI (will not display an error message) */
int *checkAIAvailMoves(piece *p){ /* Remember to free memory after usage */
	switch(p->type){
		case pawn:							  
			return checkPawnMoves(p);
		case knight:
			return checkKnightMoves(p);
		case king: 
			return checkKingMoves(p);
		case queen:
			return checkQueenMoves(p);
		case rook:
			return checkRookMoves(p);
		case bishop:
			return checkBishopMoves(p);
	}
	return NULL;
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
			if(checkTeam == team){ /* If the piece corresponds to the input team, add the cellID Number to the end of the cellList*/
				*(cellList+entry) = i;
				entry++;
			}
		}
	}
	int j;
	for(j=entry; j<17; j++){ /* fills last (and any extra) entries with -2 */
		*(cellList+entry) = -2; /* this num signals there's nothing left to read */
	}
	return cellList;
	/* Make sure to free memory after using this function */
}