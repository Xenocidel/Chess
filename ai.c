#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "errors.h"
#include "defs.h"
#include "board.h"
#include "piece.h"
#include "ai.h"

/*Global pointer variables holds the value for index of piece and move pointers for AI Team*/
int piecePointer;
int movePointer;

/*Global pointer variables holds the value for index of piece and move pointers for enemy team*/
int enemyPointer;
int enemyMovePointer;

/*Global variable that allows us to reference what team the AI is on without passing the value into every function*/
int aiTeam;

/* Manages how the AI will function in main based on difficulty*/
void aiMove(int diff, int team, board *board){
	int lookAhead = -1; /* Number of moves AI will account for */
	switch(diff){
		case(1): /* Easy */
			lookAhead = 3;
			aiChoice(team, board, lookAhead);
			break;
		case(2): /* Medium */
			lookAhead = 4;
			aiChoice(team, board, lookAhead);
			break;
		case(3): /* Hard */
			lookAhead = 5;
			aiChoice(team, board, lookAhead);
			break;
		default:
			printf("Missing difficulty parameter for AI.\n");
			break;
	}
}

/* AI's move is determined by alpha-beta pruning */
/* aiChoice chooses and moves piece */
void aiChoice(int team, board *board, int lookAhd){
	/* runs calcABmax, which should determine the optimal piece & play */
	/* moves piece after selecting optimal move */
	piecePointer = 0;
	movePointer = 0;
	aiTeam = team;
	/*Pointers for the positions of both the AI's pieces and the enemy's pieces*/
	int *piecePositions = checkPiecePos(team, board);
	int *enemyPositions = checkPiecePos(oppTeam(team), board);
	moveValue *bestMax = CreateMoveValue(NULL, 0, -1000); /* +/-1000 act as default max/min bounds */
	moveValue *bestMin = CreateMoveValue(NULL, 0, 1000);
	/*Calculates the best move for an individual piece using the ABPrune function*/
	moveValue *bestMove = ABPrune (piecePositions, enemyPositions, bestMax, bestMin, lookAhd, team, 1, board);
	movePiece(bestMove->piece, getCell(bestMove->next, board));
	/*Free all the pointers and memory when finished with the function*/
	free(piecePositions);
	piecePositions = NULL;
	free(enemyPositions);
	enemyPositions = NULL;
	DeleteMoveValue(bestMax);
	bestMax = NULL;
	DeleteMoveValue(bestMin);
	bestMin = NULL;
}

/* Simple inversion function for the team */
int oppTeam(int team){ 
	assert(team == 1 || team == 0); /* Handles invalid input */
	return (team == 1) ? 0 : 1;
}

/* Allocates memory for a moveValue struct and assigns parameters as values */
moveValue *CreateMoveValue(piece *p, int next, int value){ /*Check the syntax to see if malloc is correct*/
	moveValue *m = malloc(sizeof(moveValue));
	assert(m);
 	m->piece = p;
	m->next = next;
	m->value = value; 
	return m;
}

/*Frees the memory of a moveValue struct*/
void DeleteMoveValue(moveValue *m){
	assert(m);
	free(m->piece);
	m->piece = NULL;
	m->next = 0;
	m->value = 0;
	free(m);
	m = NULL;
}

/*Recursive Alpha-Beta pruning algorithm that calculates the most optimal move for the AI*/
moveValue *ABPrune(int *piecePositions, int *enemyPositions, moveValue *bestMax, moveValue *bestMin, int lookahd, int team, int max, board *board) {
	int value, i;
	/*Create lists of available moves for a specified piece noted by its location on the board (from piecePositions/enemyPositions parameter)*/
	int *aiList = checkAIAvailMoves(getCell(*(piecePositions + piecePointer), board)->piece);
	int aiListCount = pieceMoveCount(getCell(*(piecePositions + piecePointer), board)->piece);
	int *enemyList = checkAIAvailMoves(getCell(*(enemyPositions + enemyPointer), board)->piece);
	int enemyListCount = pieceMoveCount(getCell(*(enemyPositions + enemyPointer), board)->piece);

	/*These two conditionals start calculating the value of moves when the look ahead to find next turn moves reaches zero
	  and when the piece has a valid move to make (condition fails if the next cell location would be -2)*/
	if (lookahd == 0 && team == aiTeam && *(aiList + movePointer) >= 0 && &*(aiList + movePointer) != NULL) {
		piecePointer++;
		return calcMoveValue(aiTeam, board, getCell(*(piecePositions + piecePointer), board), *(aiList + movePointer));
	}
	else if (lookahd == 0 && team != aiTeam && *(enemyList + movePointer) >= 0 && &*(enemyList + enemyMovePointer) != NULL) {
		enemyPointer++;
		return calcMoveValue(oppTeam(aiTeam), board, getCell(*(enemyPositions + enemyPointer), board), *(enemyList + enemyMovePointer));
	}

	/*
	  The first two conditionals run a maximizer and minimizer. The maximizer evaluates the maximum value of the node one level deeper and compares it to the
	  value for the next move up (e.g. assesses three moves down the line and compares that move to two moves down the line).

	  Maximizer moves are for the AI, minimizer moves are for the human player.

	  If the value for bestMinimum is assessed to be less than the value of the bestMaximum, that means the human player has a move that is better than
	  what the AI can play if the AI chose to make that particular move.

	  This means that the move that the human can play would cause more damage to the AI's pieces than the potential move that the AI
	  would make if it decided to make that move. In this situation, the loop is broken out of and no further moves throughout the node are assessed.
	*/

	if (max == 1 && *(aiList + movePointer) != -2 && *(piecePositions + piecePointer) != -2 && piecePointer < 17) {
		value = -1000;
		for (i = 0; i != -1; i++) {
			int newValue = ABPrune(piecePositions, enemyPositions, bestMax, bestMin, lookahd - 1, team, 0, board)->value;
			value = (value > newValue) ? value : newValue;
			/*If the node's value is greater than the current bestMax value, then it will set the values to of the bestMax moveValue to the piece and its next move*/
			if (value > bestMax->value) {
				bestMax->value = value;
				bestMax->piece = getCell(*(piecePositions + piecePointer), board)->piece;
				bestMax->next = *(aiList + movePointer);
			}
			if (lookahd != 0 && bestMin->value <= bestMax->value) { /* No more moves left to look at for this piece */
				piecePointer++;
				free(aiList);
				free(enemyList);
				break;
			}
			if (bestMin->value <= bestMax->value) {
				free(aiList);
				free(enemyList);
				break; /* If there are still moves worth looking at for same piece */
			}
		}
		int nextLocAI = *(aiList + movePointer);
		if (aiList) {
			free(aiList);
		}
		return CreateMoveValue(getCell(*(piecePositions + piecePointer), board)->piece, nextLocAI, value);
	}

	else if (max == 0 && *(enemyList + enemyMovePointer) != -2 && *(enemyPositions + enemyPointer) != -2 && enemyPointer < 17) {
		value = 1000;
		for (i = 0; i != -1; i++) {
			int newValue = ABPrune(piecePositions, enemyPositions, bestMax, bestMin, lookahd - 1, team, 1, board)->value;
			value = (value < newValue) ? value : newValue;
			if (newValue < bestMin->value) {
				bestMin->value = newValue;
				bestMin->piece = getCell(*(enemyPositions + enemyPointer), board)->piece;
				bestMin->next = *(enemyList + enemyMovePointer);
			}
			if (lookahd == 1 && bestMin->value <= bestMax->value) {
				enemyPointer++;
				free(aiList);
				free(enemyList);
				break;
			}
			if (bestMin->value <= bestMax->value) {
				free(aiList);
				free(enemyList);
				break;
			}
		}
		int nextLocEnemy = *(enemyList + movePointer);
		if (enemyList) {
			free(enemyList);
		}
		return CreateMoveValue(getCell(*(piecePositions + piecePointer), board)->piece, nextLocEnemy, value);
	}

	/*
		This conditional will run if the piece in contention does not have any moves that it can make
		If this is the case, the piecePointer will increment, moving onto the next piece of the same team and evaluates the validity of that piece's moves.
	*/
	else if (max == 1 && *(aiList + movePointer) == -2) {
		piecePointer++;
		free(enemyList);
		free(aiList);
		return ABPrune( piecePositions, enemyPositions, bestMax, bestMin, lookahd, team, max, board);
	}
	else if (max == 0 && *(enemyList + enemyMovePointer) == -2) {
		enemyPointer++;
		free(enemyList);
		free(aiList);
		return ABPrune(piecePositions, enemyPositions, bestMax, bestMin, lookahd, team, max, board);
	}

	int num; /* Set all elements of both lists to NULL to prevent anything being carried over unintentionally */
	for (num = 0; num < pieceMoveCount( getCell( *(piecePositions + piecePointer), board)->piece ); num++){
		*aiList = 0;
		aiList++;
	}
	num = 0;
	for (num = 0; num < pieceMoveCount(getCell(*(enemyPositions + enemyPointer), board)->piece); num++){
		*enemyList = 0;
		enemyList++;
	}
	num = 0;
	for (num = aiListCount - 1; num >= 0; num--) {
		free(aiList + num);
	}
	aiList = NULL;
	num = 0;
	for (num = enemyListCount - 1; num >= 0; num--) {
		free(enemyList + num);
	}
	enemyList = NULL;
	return calcMoveValue(aiTeam, board, getCell(*(piecePositions + piecePointer), board), *(aiList + movePointer))
}

/* Calculates the value of an individual move*/
moveValue *calcMoveValue(int team, board *board, cell *moveLoc, int nextCellLoc){
	/*  1. Weigh the move based on an algorithm
		2. Return the moveValue struct corresponding to that move */

	int value = 0;
	cell *nextCell = getCell(nextCellLoc, board);

	/* Checks if the piece can move. If it cannot, then it will return an empty moveValue*/
	if ( !(nextCellLoc >= 0 && nextCellLoc <= 63) ) {
		value = 0;
		moveValue *calcValue = CreateMoveValue(NULL, -2, 0);
		return calcValue;
	}

	if (nextCell->piece != NULL) { /* Situation where the next move can capture an opposing piece */
		switch(nextCell->piece->type){
			case pawn:							  
				value += 5;
				break;
			case knight:
				value += 10;
				break;
			case king: 
				value += 100;
				break;
			case queen:
				value += 40;
				break;
			case rook:
				value += 10;
				break;
			case bishop:
				value += 20;
				break;
			default: /* Error */
				value += 0;
				break;
		}
	}
	int leftrightComp = nextCellLoc % 8 - moveLoc->cellID % 8; /* Will hold distance next move is left(-) or rigtht(+) from current position */
	int distFromBotRow = nextCellLoc / 8; /*Holds distance of next move from bottom row*/
	int updownComp = distFromBotRow - moveLoc->cellID/ 8; /*Holds positive/negative distance of the move*/
	int rng = -1; /* Make AI slightly less predictable */
	switch(moveLoc->piece->type){ /* Points for movement */
		case pawn: /* Pawn moves forward normally */
			value += 10;
			if(moveLoc->piece->hasMoved == false){ /* First turn move priority */
				value += 1;
			}
			break;
		case knight:
			if((leftrightComp < 0 && nextCellLoc % 8 >= 4) || (leftrightComp > 0 && nextCellLoc % 8  < 4 )){ /* If move would bring piece left/right toward center */
				value += 5;
			}
			if ( (distFromBotRow <= 3 && updownComp > 0) || (distFromBotRow >= 4 && updownComp < 0) ) { /* Forward movement */
				value += 5;	
			}
			if(moveLoc->piece->hasMoved == false){
				srand(time(NULL));
				rng = rand()%3; 
				if(rng == 1){ /* 33% for knight to have priority over unmoved pawn */
					value += 2;
				}
				rng = -1; /* Resets rng */
			}
			break;
		case king:
			if((leftrightComp < 0 && nextCellLoc%8 >= 4) || (leftrightComp > 0 && nextCellLoc % 8  < 4 )){ /* If move would bring piece left/right toward center */
				value -= 1;
			}
			if ( (distFromBotRow <= 3 && updownComp > 0) || (distFromBotRow >= 4 && updownComp < 0) ) { 
				value += 1;	
			}
			break;
		case queen:
			if((leftrightComp < 0 && nextCellLoc%8 >= 4) || (leftrightComp > 0 && nextCellLoc % 8  < 4 )){ /* If move would bring piece left/right toward center */
				value += 10;
			}
			if ( (distFromBotRow <= 3 && updownComp > 0) || (distFromBotRow >= 4 && updownComp < 0) ) { 
				value += 10;	
			}
			break;
		case rook:
			if ( (distFromBotRow <= 3 && updownComp > 0) || (distFromBotRow >= 4 && updownComp < 0) ) { /* If move would bring piece toward opponent's side */
				value += 3;	
			}
			break;
		case bishop:
			if((leftrightComp < 0 && nextCellLoc %8 < 4) || (leftrightComp > 0 && nextCellLoc % 8 >= 4 )){ /* If move would bring piece left/right toward center */
				value += 5;
			}
			if (updownComp > 0 && moveLoc->piece->player == white) { /* Movement vertically away from AI's side */
				value += updownComp*3;	
			}
			else if(updownComp < 0 && moveLoc->piece->player == black){
				value += updownComp*3;
			}
			break;
		default: /* Error */
			value += 0;
			break;
	}
	moveValue *calcValue = CreateMoveValue(moveLoc->piece, nextCellLoc, value);
	movePointer++;
	return calcValue;
}

/* Counts number of moves a piece can make */
int pieceMoveCount(piece *p){
	int moveCount = 0;
	int *moveList = checkAIAvailMoves(p);
	int i;
	for (i = 0; *(moveList+i) != -2 || moveList != NULL; i++) {
		moveCount++;
	}
	free(moveList);
	return moveCount; 
}

/* Version of checkAvailMoves modified for use with AI (will not display an error message) */
int *checkAIAvailMoves(piece *p){ /* Remember to free memory after usage */
	switch(p->type){
		case pawn:
			if (checkPawnMoves(p)) return checkPawnMoves(p);
		case knight:
			if (checkKnightMoves(p)) return checkKnightMoves(p);
		case king: 
			if (checkKingMoves(p)) return checkKingMoves(p);
		case queen:
			if (checkQueenMoves(p)) return checkQueenMoves(p);
		case rook:
			if (checkRookMoves(p)) return checkRookMoves(p);
		case bishop:
			if (checkBishopMoves(p)) return checkBishopMoves(p);
	}
	return NULL;
}

/* Returns pointer to list of specified team's piece locations */
int *checkPiecePos(int team, board *board){ 
	
	/*Creates a cellList with as many values as there are pieces per side*/
	int cellList[17];
	int j;
	for (j = 0; j<17; j++) { /* fills entries with -2 */
		cellList[j] = -2;
	}

	int entry = 0;
	int checkTeam = -1;
	int i = 0;
	cell *read = getCell(0, board);
	/*Goes through the entire board and stores the cell number into the cellList*/
	for(i=0; i<64; i++){
		read = getCell(i, board);
		if(read->piece != NULL){
			if(read->piece->player == white){ /* 0 = white, 1 = black */
				checkTeam = 0;
			}
			else if (read->piece->player == black){
				checkTeam = 1;
			}
			if(checkTeam == team){ /* If the piece corresponds to the input team, add the cellID Number to the end of the cellList*/
				cellList[entry] = i;
				entry++;
			}

		}
		read = NULL;
	}
	i = 0; /* Resets i for next use */
	int *ans = malloc(sizeof(int)*17);
	while (i < 17)
	{
		*ans = cellList[i];
		ans++;
		i++;
	}
	ans -= i;
	return ans;
	/* Make sure to free memory after using this function */
}
