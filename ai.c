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

int piecePointer;
int movePointer;

int enemyPointer;
int enemyMovePointer;

int aiTeam;

void aiMove(int diff, int team, board *board){
	int lookAhead = -1; /* Number of moves AI will account for */
	switch(diff){
		case(1): /* Easy, AI accounts for 1 move ahead */
			lookAhead = 3;
			aiChoice(team, board, lookAhead);
			break;
		case(2): /* Medium, AI accounts for 2 additional moves */
			lookAhead = 4;
			aiChoice(team, board, lookAhead);
			break;
		case(3): /* Hard, AI accounts for 3 additional moves */
			lookAhead = 5;
			aiChoice(team, board, lookAhead);
			break;
		/* case(4): Mainly to quickly test AI moving functionality. Unused. 
			randomMove(team, board);
			break; */
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
<<<<<<< HEAD
	/* int *piecePointer = 0; */ piecePointer = 0;
	int *piecePositions = checkPiecePos(team, board);
	/* printf("First element in piece pos: %d\n", *piecePositions); DEBUG */
	int *enemyPositions = checkPiecePos(oppTeam(team), board);
	/*printf("First element in enemy pos: %d\n", *enemyPositions); DEBUG */
	/* int *movePointer = 0; */ movePointer = 0;
	moveValue *bestMax = CreateMoveValue(NULL, -1, -1000); /* +/-1000 act as default max/min bounds */
	printf("content of value for bestMax is %d\n", bestMax->value); /* DEBUG */
	moveValue *bestMin = CreateMoveValue(NULL, -1, 1000);
	printf("content of value for bestMin is %d\n", bestMin->value); /* DEBUG */
	moveValue *bestMove = calcABmax(/*piecePointer, movePointer,*/ piecePositions, enemyPositions, bestMax, bestMin, lookAhd, team, board);
	printf("content of value for bestMove is %d\n", bestMove->value); /* DEBUG */
=======
	piecePointer = 0;
	movePointer = 0;
	aiTeam = team;
	int *piecePositions = checkPiecePos(oppTeam(team), board);
	/*printf("Second element in piece pos: %d\n", *piecePositions+1); DEBUG */
	int *enemyPositions = checkPiecePos(team, board);
	/*printf("Second element in enemy pos: %d\n", *enemyPositions+1); DEBUG */
	moveValue *bestMax = CreateMoveValue(NULL, 0, -1000); /* +/-1000 act as default max/min bounds */
	/*printf("\ncontent of value for bestMax is %d", bestMax->value);
	printf("\ncontent of value for bestMax piece is %c", bestMax->piece->loc->printPiece); DEBUG */
	moveValue *bestMin = CreateMoveValue(NULL, 0, 1000);
	/*printf("\ncontent of value for bestMin is %d", bestMin->value); DEBUG 
	printf("\nmovepointer is %d", movePointer);
	printf("\npiecepointer is %d", piecePointer);
	printf("\ncontent of value for bestMin piece is %c\n", bestMin->piece->loc->printPiece); DEBUG */
	/*int *moveList = checkAIAvailMoves(getCell( *(piecePositions + piecePointer), board ) -> piece);
	printf("\nThe piece for AIAvailMoves is %c", getCell( *(piecePositions + 8), board ) -> printPiece);
	printf("\ncontent of first move for AIAvailMoves is %d", *moveList);*/
	moveValue *bestMove = ABPrune (piecePositions, enemyPositions, bestMax, bestMin, lookAhd, team, 1, board);
	/*printf("\ncontent of value for bestMove is %d\n", bestMove->value);
	printf("\ncontent of value for bestMove is %d", bestMove->value);  DEBUG */
>>>>>>> origin/ai-into-main-v1
	movePiece(bestMove->piece, getCell(bestMove->next, board));
	/*movePiece(getCell(8,board)->piece, getCell(16, board));*/
	free(piecePositions);
	piecePositions = NULL;
	free(enemyPositions);
	enemyPositions = NULL;
	DeleteMoveValue(bestMax);
	bestMax = NULL;
	DeleteMoveValue(bestMin);
	bestMin = NULL;
	/*DeleteMoveValue(bestMove);
	bestMove = NULL;*/
}

int oppTeam(int team){ /* Simple inversion function */
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

/* Compares the value of yoiur move with your previous best options (taking into consideration the opponent's moves as well)
moveValue *calcABmax(int *moveList, int *piecePositions, int *enemyPositions, moveValue *bestMax, moveValue *bestMin, int lookAhd, int team, board *board) {
	

	param piecePointer : integer that points to the element of the piece position array so that we can evaluate the piece's moves
	param bestMax : moveValue struct that corresponds to the best move for the AI
	param bestin : moveValue struct that corresponds to the worst move for the player
	param lookAhd : number of additional turns to account for
	param team : Player's team
	param board: The board

	
	if (*(piecePositions + piecePointer) != -2 && *(moveList + movePointer) != -2) {
		if (lookAhd == 0) {
			moveValue *newValue = calcMoveValue(team, board, getCell(*(piecePositions + piecePointer), board), *(moveList + movePointer));
			int dummy = movePointer; Prevents a warning while incrementing the content of the pointer
			dummy++;
			return newValue;
		}
		int i;
		moveValue *currMove = CreateMoveValue(NULL, -5, 0);
		for (i = 0; i < totalMoveCount(team, board); i++) {
			currMove = calcABmin( moveList, piecePositions, enemyPositions, bestMax, bestMin, lookAhd - 1, oppTeam(team), board);
			if (currMove->value >= bestMin->value) {
				DeleteMoveValue(currMove);
				currMove = NULL;
				int dummy = piecePointer++;
				dummy++;
				return bestMin;
			}
			if (currMove->value > bestMax->value) {
				bestMax->piece = currMove->piece;
				bestMax->next = currMove->next;
				bestMax->value = currMove->value;
				DeleteMoveValue(currMove);
				currMove = NULL;
			}
		}
	}
	return bestMax;
}*/

/*Compares the value of an opponent's move with the opponent's previous calculated worst move (taking into consideration the AI's moves as well)
moveValue *calcABmin(int *moveList, int *piecePositions, int *enemyPositions, moveValue *bestMax, moveValue *bestMin, int lookAhd, int team, board *board) {


	param piecePointer : integer that points to the element of the piece position array so that we can evaluate the piece's moves
	param bestMax : moveValue struct that corresponds to the best move for the AI
	param bestin : moveValue struct that corresponds to the worst move for the player
	param lookAhd : number of additional turns to account for
	param team : Opponent's team
	param board: The board


	if (*(piecePositions + piecePointer) != -2 && *(moveList + movePointer) != -2) {
		if (lookAhd == 0) {
			moveValue *newValue = calcMoveValue(team, board, getCell(*(piecePositions + piecePointer), board), *(moveList + movePointer));
			newValue->value *= -1;
			int dummy = movePointer;
			dummy++;
			return newValue;
		}
		int i;
		moveValue *currMove = CreateMoveValue(NULL, -5, 0);
		for (i = 0; i < totalMoveCount(team, board); i++) {
			currMove = calcABmax(moveList, piecePositions, enemyPositions, bestMax, bestMin, lookAhd - 1, oppTeam(team), board);
			if (currMove->value <= bestMax->value) {
				DeleteMoveValue(currMove);
				currMove = NULL;
				int dummy = piecePointer++;
				dummy++;
				return bestMax;
			}
			if (currMove->value < bestMin->value) { Replaces the BestMinimum with the newest calculated move (if the move is better)
				bestMin->piece = currMove->piece;
				bestMin->next = currMove->next;
				bestMin->value = currMove->value;
				DeleteMoveValue(currMove);
				currMove = NULL;
			}
		}
	}
	return bestMin;
} */

/* I'm pretty sure the global integers for pointer values are being overcounted. Fix this. */
moveValue *ABPrune(int *piecePositions, int *enemyPositions, moveValue *bestMax, moveValue *bestMin, int lookahd, int team, int max, board *board) {
	int value, i;
	int *aiList = checkAIAvailMoves(getCell(*(piecePositions + piecePointer), board)->piece);
	int *enemyList = checkAIAvailMoves(getCell(*(enemyPositions + enemyPointer), board)->piece);
	/*These two conditionals start calculating the value of moves when the look ahead to find next turn moves reaches zero
	  and when the piece has a valid move to make (condition fails if the next cell location would be -2)*/
	if (lookahd == 0 && team == aiTeam && *(aiList + movePointer) >= 0 && &*(aiList + movePointer) != NULL) {
		return calcMoveValue(aiTeam, board, getCell(*(piecePositions + piecePointer), board), *(aiList + movePointer));
	}
	else if (lookahd == 0 && team != aiTeam && *(enemyList + movePointer) >= 0 && &*(enemyList + enemyMovePointer) != NULL) {
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
		for (i = 0; i < totalMoveCount(team, board); i++) {
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
				break;
			}
			if (bestMin->value <= bestMax->value) break; /* If there are still moves worth looking at for same piece */
		}
		return CreateMoveValue(getCell(*(piecePositions + piecePointer), board)->piece, *(aiList + movePointer), value);
	}

	else if (max == 0 && *(enemyList + enemyMovePointer) != -2 && *(enemyPositions + enemyPointer) != -2 && enemyPointer < 17) {
		value = 1000;
		for (i = 0; i < totalMoveCount(team, board); i++) {
			int newValue = ABPrune(piecePositions, enemyPositions, bestMax, bestMin, lookahd - 1, team, 1, board)->value;
			value = (value < newValue) ? value : newValue;
			if (newValue < bestMin->value) {
				bestMin->value = newValue;
				bestMin->piece = getCell(*(enemyPositions + enemyPointer), board)->piece;
				bestMin->next = *(enemyList + enemyMovePointer);
			}
			if (lookahd == 1 && bestMin->value <= bestMax->value) {
				enemyPointer++;
				break;
			}
			if (bestMin->value <= bestMax->value) break;
		}
		return CreateMoveValue(getCell(*(piecePositions + piecePointer), board)->piece, *(enemyList + movePointer), value);
	}

	/*
		This conditional will run if the piece in contention does not have any moves that it can make
		If this is the case, the piecePointer will increment, moving onto the next piece of the same team and evaluates the validity of that piece's moves.
	*/
	else if (max == 1 && *(aiList + movePointer) == -2) {
		piecePointer++;
		return ABPrune( piecePositions, enemyPositions, bestMax, bestMin, lookahd, team, max, board);
	}
	else if (max == 0 && *(enemyList + enemyMovePointer) == -2) {
		enemyPointer++;
		return ABPrune(piecePositions, enemyPositions, bestMax, bestMin, lookahd, team, max, board);
	}

	int num; /* Set all elements of both lists to NULL to prevent anything being carried over unintentionally */
	for (num = 0; num < pieceMoveCount( getCell( *(piecePositions + piecePointer), board)->piece ); num++){
		*aiList++ = 0;
	}
	for (num = 0; num < pieceMoveCount(getCell(*(enemyPositions + enemyPointer), board)->piece); num++){
		*enemyList++ = 0;
	}
	free(aiList);
	free(enemyList);
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

/* Basic move decision to quickly see if movement functions at a base level. Noted out and unused. */
/* void randomMove(int team, board *board){
	int *aiTeamPos = checkPiecePos(team, board); Reads team locations 
	int opTeam = (team == 1) ? 0 : 1;
	int *opTeamPos = checkPiecePos(opTeam, board); Reads enemy locations 
	
	 Check moves cell by cell. Currently unused, saving just in case. 
	int entry = 0;
	while(aiTeamPos){
		cell *read = getCell(*(aiTeamPos+entry), board)
		int *aiList = checkAvailMoves(read->piece);
		if(*(aiTeamPos+entry) == -2){
			break;
		}
		entry++;
	} 
	
	srand(time(NULL));
	int *pieceMoves;
	cell *moveCell;
	while(1){  Selects a random piece to move, and gets corresponding available moves 
		int rNum = rand()%17;
		cell *rCell = getCell(*(aiTeamPos+rNum), board);
		if(*(aiTeamPos+rNum) != -2){
			pieceMoves = checkAvailMoves(rCell->piece);
			moveCell = rCell;
			break;
		}
	}
	int count = 0;
	while(1){  Count number of available moves 
		if(*(pieceMoves+count) == -2){
			break;
		}
		count++;
	}
	int selNum = rand()%count;
	int m = *(pieceMoves+selNum);
	cell *nextCell = getCell(m, board);
	replacePiece(nextCell, moveCell->piece);
	
	 Freeing memory
	free(aiTeamPos); free(opTeamPos);
	deleteCell(nextCell);
} */

/* Counts number of moves a piece can make */
int pieceMoveCount(piece *p){
	int moveCount = 0;
	int *moveList = checkAIAvailMoves(p);
	while (1) {
<<<<<<< HEAD
		if (*(moveList) == -2 || moveList == NULL) {
			int j;
			for(j=pieceCount; j>=0; j--){
				pieceList = NULL;
				pieceList--;
			}
=======
		if (*(moveList) == -2 /*|| *moveList == NULL*/) {
			int num;
			assert(moveList);
			for (num = 0; num < moveCount; num++) {
				*moveList++ = 0;
			}
			free(moveList);
>>>>>>> origin/ai-into-main-v1
			break;
			return moveCount;
		}
		moveCount++;
		moveList++;
	}
	return moveCount;
}

/* Counts number of moves a player can make */
int totalMoveCount(int team, board *board){
	int moveCount = 0;
	int pieceCount = 0;
	int *pieceList = checkPiecePos(team, board);
<<<<<<< HEAD
	while (1) { /* Counts amount of pieces for specified player */
		if (*(pieceList) == -2 || pieceList == NULL) {
			int j;
			for(j=pieceCount; j>=0; j--){
				pieceList = NULL;
				pieceList--;
			}
			break;
		}
=======

	int j; /* Counts amount of pieces for specified player */
	for (j = 0; *pieceList != -2; j++) {
>>>>>>> origin/ai-into-main-v1
		pieceCount++;
		pieceList++;
	}

	int num; /* Cleans the list when finished counting the amount of pieces*/
	for (num = 0; num < pieceCount; num++) {
		*pieceList++ = 0;
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
	printf("\ntotal move count is running");
	int *cellList = (int*) malloc(sizeof(int)*17);
	int idk = 0;
	for (idk = 0; idk <= 17; idk++) {
		*(cellList + idk) = 0;
	}
	int entry = 0;
	int checkTeam = -1;
	int i = 0;
	printf("\n%d", i);
	printf("\n%d", entry);
	cell *read = getCell(0, board);
	for(i=0; i<64; i++){
		read = getCell(i, board);
		if(read->piece != NULL){
			if(read->piece->player == white){ /* 0 = white, 1 = black */
				printf("\npiece is: %c", read->printPiece);
				checkTeam = 0;
			}
			else if (read->piece->player == black){
				printf("\npiece is: %c", read->printPiece);
				checkTeam = 1;
			}
			if(checkTeam == team){ /* If the piece corresponds to the input team, add the cellID Number to the end of the cellList*/
				*(cellList+entry) = i;
				printf("\nfound piece: %d", entry);
				printf("\ncell of found piece: %d", i);
				entry++;
			}

		}
		deleteCell(read);
		read = NULL;
	}
	int j;
	for(j=entry; j<17; j++){ /* fills last (and any extra) entries with -2 */
		*(cellList+entry) = -2; /* this num signals there's nothing left to read */
		printf("\n-2 added to end of list");
	}
	cellList -= entry;
	return cellList;
	/* Make sure to free memory after using this function */
}