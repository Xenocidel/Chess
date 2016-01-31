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
#include "piece.h"
#include "cell.h"
#include "defs.h"
#include "errors.h"
#include "board.h"

piece *createPiece(enum player player, enum type type, cell *cell){
	piece *ans = malloc(sizeof(piece));
	ans->player = player;
	ans->type = type;
	ans->hasMoved = false;
	ans->castleFlag = 0;
	ans->epFlag = 0;
	ans->loc = cell;
	assert(ans->loc == cell);
	ans->prev = NULL;
	cell->piece = ans;
	return ans;
}

void deletePiece(piece *p){
	p->loc = NULL;
	p->prev = NULL;
	free(p);
}

void printCell(int cellID){
	switch (cellID){
		case 0 : printf("a1"); break;
		case 8 : printf("a2"); break;
		case 16: printf("a3"); break;
		case 24: printf("a4"); break;
		case 32: printf("a5"); break;
		case 40: printf("a6"); break;
		case 48: printf("a7"); break;
		case 56: printf("a8"); break;
		case 1 : printf("b1"); break;
		case 9 : printf("b2"); break;
		case 17: printf("b3"); break;
		case 25: printf("b4"); break;
		case 33: printf("b5"); break;
		case 41: printf("b6"); break;
		case 49: printf("b7"); break;
		case 57: printf("b8"); break;
		case 2 : printf("c1"); break;
		case 10: printf("c2"); break;
		case 18: printf("c3"); break;
		case 26: printf("c4"); break;
		case 34: printf("c5"); break;
		case 42: printf("c6"); break;
		case 50: printf("c7"); break;
		case 58: printf("c8"); break;
		case 3 : printf("d1"); break;
		case 11: printf("d2"); break;
		case 19: printf("d3"); break;
		case 27: printf("d4"); break;
		case 35: printf("d5"); break;
		case 43: printf("d6"); break;
		case 51: printf("d7"); break;
		case 59: printf("d8"); break;
		case 4 : printf("e1"); break;
		case 12: printf("e2"); break;
		case 20: printf("e3"); break;
		case 28: printf("e4"); break;
		case 36: printf("e5"); break;
		case 44: printf("e6"); break;
		case 52: printf("e7"); break;
		case 60: printf("e8"); break;
		case 5 : printf("f1"); break;
		case 13: printf("f2"); break;
		case 21: printf("f3"); break;
		case 29: printf("f4"); break;
		case 37: printf("f5"); break;
		case 45: printf("f6"); break;
		case 53: printf("f7"); break;
		case 61: printf("f8"); break;
		case 6 : printf("g1"); break;
		case 14: printf("g2"); break;
		case 22: printf("g3"); break;
		case 30: printf("g4"); break;
		case 38: printf("g5"); break;
		case 46: printf("g6"); break;
		case 54: printf("g7"); break;
		case 62: printf("g8"); break;
		case 7 : printf("h1"); break;
		case 15: printf("h2"); break;
		case 23: printf("h3"); break;
		case 31: printf("h4"); break;
		case 39: printf("h5"); break;
		case 47: printf("h6"); break;
		case 55: printf("h7"); break;
		case 63: printf("h8"); break;
	}
}

void printLoc(piece *p){
	switch (p->loc->cellID){
		case 0 : printf("a1\n"); break;
		case 8 : printf("a2\n"); break;
		case 16: printf("a3\n"); break;
		case 24: printf("a4\n"); break;
		case 32: printf("a5\n"); break;
		case 40: printf("a6\n"); break;
		case 48: printf("a7\n"); break;
		case 56: printf("a8\n"); break;
		case 1 : printf("b1\n"); break;
		case 9 : printf("b2\n"); break;
		case 17: printf("b3\n"); break;
		case 25: printf("b4\n"); break;
		case 33: printf("b5\n"); break;
		case 41: printf("b6\n"); break;
		case 49: printf("b7\n"); break;
		case 57: printf("b8\n"); break;
		case 2 : printf("c1\n"); break;
		case 10: printf("c2\n"); break;
		case 18: printf("c3\n"); break;
		case 26: printf("c4\n"); break;
		case 34: printf("c5\n"); break;
		case 42: printf("c6\n"); break;
		case 50: printf("c7\n"); break;
		case 58: printf("c8\n"); break;
		case 3 : printf("d1\n"); break;
		case 11: printf("d2\n"); break;
		case 19: printf("d3\n"); break;
		case 27: printf("d4\n"); break;
		case 35: printf("d5\n"); break;
		case 43: printf("d6\n"); break;
		case 51: printf("d7\n"); break;
		case 59: printf("d8\n"); break;
		case 4 : printf("e1\n"); break;
		case 12: printf("e2\n"); break;
		case 20: printf("e3\n"); break;
		case 28: printf("e4\n"); break;
		case 36: printf("e5\n"); break;
		case 44: printf("e6\n"); break;
		case 52: printf("e7\n"); break;
		case 60: printf("e8\n"); break;
		case 5 : printf("f1\n"); break;
		case 13: printf("f2\n"); break;
		case 21: printf("f3\n"); break;
		case 29: printf("f4\n"); break;
		case 37: printf("f5\n"); break;
		case 45: printf("f6\n"); break;
		case 53: printf("f7\n"); break;
		case 61: printf("f8\n"); break;
		case 6 : printf("g1\n"); break;
		case 14: printf("g2\n"); break;
		case 22: printf("g3\n"); break;
		case 30: printf("g4\n"); break;
		case 38: printf("g5\n"); break;
		case 46: printf("g6\n"); break;
		case 54: printf("g7\n"); break;
		case 62: printf("g8\n"); break;
		case 7 : printf("h1\n"); break;
		case 15: printf("h2\n"); break;
		case 23: printf("h3\n"); break;
		case 31: printf("h4\n"); break;
		case 39: printf("h5\n"); break;
		case 47: printf("h6\n"); break;
		case 55: printf("h7\n"); break;
		case 63: printf("h8\n"); break;
	}		
}

/*returns pointer with available cellID positions*/
/* WARNING: You cannot find the length of a pointer, so at the very end put a -2 as a null terminator and look for it on the receiving end */
int *checkAvailMoves(piece *p){
	switch(p->type){
		case pawn: return checkPawnMoves(p);
		case knight: return checkKnightMoves(p);
		case king: return checkKingMoves(p);
		case queen: return checkQueenMoves(p);
		case rook: return checkRookMoves(p);
		case bishop: return checkBishopMoves(p);
	}
	return NULL;
}

int *checkPawnMoves(piece *p){
	int num=0;				/*number of available moves*/
	int frontchk = -1;      /*pawn can move forward*/
	int leftchk = -1;       /*pawn can capture diagonally left*/
	int rightchk = -1;      /*pawn can capture diagonally right*/
	int front2chk = -1;     /*pawn can move 2 spaces forward if it hasn't moved before*/
	int epleftchk = -1;         /*pawn can en passant left*/
	int eprightchk = -1;		/*pawn can en passant right*/
	
	if (p->player == white){	/*the else block reverses direction of the pawn*/
		assert((p->loc->cellID)+8);	/* the pawn should always be able to move forward */
		cell *front = getCell((p->loc->cellID)+8, p->loc->board);
		cell *front2 = getCell((p->loc->cellID)+16, p->loc->board);
		cell *left = getCell((p->loc->cellID)+7, p->loc->board);
		cell *right = getCell((p->loc->cellID)+9, p->loc->board);
		cell *epleft = getCell((p->loc->cellID)-1, p->loc->board);
		cell *epright = getCell((p->loc->cellID)+1, p->loc->board);
		
		/*first move jump 2*/
		if (p->hasMoved == false){
			if (front2->piece == NULL && front->piece == NULL){ /*if both front locations are empty (can't jump over a piece)*/
				num++;
				front2chk = front2->cellID;
			}
		}
		/*basic forward movement of pawn*/
		if (front->piece == NULL){
			num++;
			frontchk = front->cellID;
		}
		
		if (front->cellID%8 != 0){ /*runs when not on left edge*/
			/*standard left diagonal capture*/
			if (left->piece != NULL){ /*if piece exists, necessary to avoid seg fault*/
				if (left->piece->player != p->player){ /*if its the opponent piece*/
					num++;
					leftchk = left->cellID;
				}
			}
			if (epleft->piece != NULL){ /* both capturer and captive must have epFlag on */
				if (p->epFlag == 1 && epleft->piece->epFlag == 1 && epleft->piece->type == pawn && epleft->piece->player != p->player){ /*en passant capture left */
					num++;
					epleftchk = left->cellID;	/*not epleft because pawn captures diagonally */
				}
			}
		}
		
		if ((right->cellID)%8 != 0){ /*runs when not on right edge*/
			/*standard right diagonal capture*/
			if (right->piece != NULL){ /*if piece exists, necessary to avoid seg fault*/
				if (right->piece->player != p->player){ /*if its the opponent piece*/
					num++;
					rightchk = right->cellID;
				}
			}
			if (epright->piece != NULL){
				if (p->epFlag == 1 && epright->piece->epFlag == 1 && epright->piece->type == pawn && epright->piece->player != p->player){ /*en passant capture right */
					num++;
					eprightchk = right->cellID;	/*not epright because pawn captures diagonally */
				}
			}
		}
	}
	else{
		assert((p->loc->cellID)-8);	/* the pawn should always be able to move forward */
		cell *front = getCell((p->loc->cellID)-8, p->loc->board);
		cell *front2 = getCell((p->loc->cellID)-16, p->loc->board);
		cell *left = getCell((p->loc->cellID)-9, p->loc->board);
		cell *right = getCell((p->loc->cellID)-7, p->loc->board);
		cell *epleft = getCell((p->loc->cellID)-1, p->loc->board);
		cell *epright = getCell((p->loc->cellID)+1, p->loc->board);
		/*first move jump 2*/
		if (p->hasMoved == false){
			if (front2->piece == NULL && front->piece == NULL){ /*if both front locations are empty (can't jump over a piece)*/
				num++;
				front2chk = front2->cellID;
			}
		}
		/*basic forward movement of pawn*/
		if (front->piece == NULL){		
			num++;
			frontchk = front->cellID;
		}
		
		if (front->cellID%8 != 0){ /*runs when not on left edge*/
			/*standard left diagonal capture*/
			if (left->piece != NULL){ /*if piece exists, necessary to avoid seg fault*/
				if (left->piece->player != p->player){ /*if its the opponent piece*/
					num++;
					leftchk = left->cellID;
				}
			}
			if (epleft->piece != NULL){
				if (p->epFlag == 1 && epleft->piece->epFlag == 1 && epleft->piece->type == pawn && epleft->piece->player != p->player){ /*en passant capture left */
					num++;
					epleftchk = left->cellID;	/*not epleft because pawn captures diagonally */
				}
			}
		}
		
		if ((right->cellID)%8 != 0){ /*runs when not on right edge*/
			/*standard right diagonal capture*/
			if (right->piece != NULL){ /*if piece exists, necessary to avoid seg fault*/
				if (right->piece->player != p->player){ /*if its the opponent piece*/
					num++;
					rightchk = right->cellID;
				}
			}
			if (epright->piece != NULL){
				if (p->epFlag == 1 && epright->piece->epFlag == 1 && epright->piece->type == pawn && epright->piece->player != p->player){ /*en passant capture right */
					num++;
					eprightchk = right->cellID;	/*not epright because pawn captures diagonally */
				}
			}
		}
	}
		
	/*if no available moves, print error and return null*/
	if (num==0){
		return NULL;
	}
	/*compile all available moves*/
	int *ans;
	ans = malloc(sizeof(int) * (num+1));
	int i;
	for (i=num; i>0; i--){
		if (frontchk > 0){
			*ans = frontchk;
			frontchk = -2;
			ans++;
		}
		if (leftchk > 0){
			*ans = leftchk;
			leftchk = -2;
			ans++;
		}
		if (rightchk > 0){
			*ans = rightchk;
			rightchk = -2;
			ans++;
		}
		if (front2chk > 0){
			*ans = front2chk;
			front2chk = -2;
			ans++;
		}
		if (epleftchk > 0){
			*ans = epleftchk;
			epleftchk = -2;
			ans++;
		}
		if (eprightchk > 0){
			*ans = eprightchk;
			eprightchk = -2;
			ans++;
		}
	}
	*ans = -2;
	ans -= num;
	/*still need to figure out a way to free ans*/
	return ans;
}

int *checkKnightMoves(piece *p){
	int num = 0; /* number of possible moves */
	int fwd = 0;
	int back = 0;
	int left, right = 0;
	int frontchk, frontchk2, frontchk3, frontchk4 = -1; /* the "forward" movements */
	int backchk, backchk2, backchk3, backchk4 = -1; /* the "back" movements */
	
	if(p->player == white){
		/* available moves for the knight, not including edge detection */
		cell *front  = getCell((p->loc->cellID)+6, p->loc->board);
		cell *front2 = getCell((p->loc->cellID)+10, p->loc->board);
		cell *front3 = getCell((p->loc->cellID)+15, p->loc->board);
		cell *front4 = getCell((p->loc->cellID)+17, p->loc->board);
		
		cell *back  = getCell((p->loc->cellID)-6, p->loc->board);
		cell *back2 = getCell((p->loc->cellID)-10, p->loc->board);
		cell *back3 = getCell((p->loc->cellID)-15, p->loc->board);
		cell *back4 = getCell((p->loc->cellID)-17, p->loc->board);
		
		/*basic "forward" movement of Knight */
		if(front->piece == NULL){
			fwd++;
			frontchk = front->cellID;
		}
		if(front->piece != NULL){
			if(front->piece->player != p->player){
				fwd++;
				frontchk = front->cellID;
			}
		}
		if(front2->piece == NULL){
			fwd++;
			frontchk2 = front2->cellID;
		}
		if(front2->piece != NULL){
			if(front2->piece->player != p->player){
				fwd++;
				frontchk2 = front2->cellID;
			}
		}
		if(front3->piece == NULL){
			fwd++;
			frontchk3 = front3->cellID;
		}
		if(front3->piece != NULL){
			if(front3->piece->player != p->player){
				fwd++;
				frontchk3 = front3->cellID;
			}
		}
		if(front4->piece == NULL){
			fwd++;
			frontchk4 = front4->cellID;
		}
		if(front4->piece != NULL){
			if(front4->piece->player != p->player){
				fwd++;
				frontchk4 = front4->cellID;
			}
		}
		
		/*basic "back" movement of Knight*/
		if(back->piece == NULL){
			back++;
			backchk = back->cellID;
		}
		if(back->piece != NULL){
			if(back->piece->player != p->player){
				back++;
				backchk = back->cellID;
			}
		}
		
		if(back2->piece == NULL){
			back++;
			backchk2 = back2->cellID;
		}
		if(back2->piece != NULL){
			if(back2->piece->player != p->player){
				back++;
				backchk2 = back2->cellID;
			}
		}
		
		if(back3->piece == NULL){
			back++;
			backchk3 = back3->cellID;
		}
		if(back3->piece != NULL){
			if(back3->piece->player != p->player){
				back++;
				backchk3 = back3->cellID;
			}
		}
		
		if(back4->piece == NULL){
			back++;
			backchk4 = back4->cellID;
		}
		if(back4->piece != NULL){
			if(back4->piece->player != p->player){
				back++;
				backchk4 = back4->cellID;
			}
		}
		
		/*when the Knight is on the left edge*/
		if(front->cellID%8 == 0){
			left = 0;
		}
		
		/*when the Knight is on the right edge*/
		if(front->cellID%8 == 7){
			right = 0;
		}		
	}
	else{
		cell *front  = getCell((p->loc->cellID)-6, p->loc->board);
		cell *front2 = getCell((p->loc->cellID)-10, p->loc->board);
		cell *front3 = getCell((p->loc->cellID)-15, p->loc->board);
		cell *front4 = getCell((p->loc->cellID)-17, p->loc->board);
		
		cell *back  = getCell((p->loc->cellID)+6, p->loc->board);
		cell *back2 = getCell((p->loc->cellID)+10, p->loc->board);
		cell *back3 = getCell((p->loc->cellID)+15, p->loc->board);
		cell *back4 = getCell((p->loc->cellID)+17, p->loc->board);		
		
		/*basic "forward" movement of Knight */
		if(front->piece == NULL){
			fwd++;
			frontchk = front->cellID;
		}
		if(front->piece != NULL){
			if(front->piece->player != p->player){
				fwd++;
				frontchk = front->cellID;
			}
		}
		
		if(front2->piece == NULL){
			fwd++;
			frontchk2 = front2->cellID;
		}
		if(front2->piece != NULL){
			if(front2->piece->player != p->player){
				fwd++;
				frontchk2 = front2->cellID;
			}
		}
		
		if(front3->piece == NULL){
			fwd++;
			frontchk3 = front3->cellID;
		}
		if(front3->piece != NULL){
			if(front3->piece->player != p->player){
				fwd++;
				frontchk3 = front3->cellID;
			}
		}
		
		if(front4->piece == NULL){
			fwd++;
			frontchk4 = front4->cellID;
		}
		if(front4->piece != NULL){
			if(front4->piece->player != p->player){
				fwd++;
				frontchk4 = front4->cellID;
			}
		}
		
		/*basic "back" movement of Knight*/
		if(back->piece == NULL){
			back++;
			backchk = back->cellID;
		}
		if(back->piece != NULL){
			if(back->piece->player != p->player){
				back++;
				backchk = back->cellID;
			}
		}
		
		if(back2->piece == NULL){
			back++;
			backchk2 = back2->cellID;
		}
		if(back2->piece != NULL){
			if(back2->piece->player != p->player){
				back++;
				backchk2 = back2->cellID;
			}
		}
		
		if(back3->piece == NULL){
			back++;
			backchk3 = back3->cellID;
		}
		if(back3->piece != NULL){
			if(back3->piece->player != p->player){
				back++;
				backchk3 = back3->cellID;
			}
		}
		
		if(back4->piece == NULL){
			back++;
			backchk4 = back4->cellID;
		}
		if(back4->piece != NULL){
			if(back4->piece->player != p->player){
				back++;
				backchk4 = back4->cellID;
			}
		}
		
		/*when the Knight is on the left edge*/
		if(front->cellID%8 == 7){
			left = 0;
		}
		
		/*when the Knight is on the right edge*/
		if(front->cellID%8 == 0){
			right = 0;
		}
	}
	
	/*add all possible moves for Knight*/
	num = fwd + back;
	
	/*if no possible moves, print error and return NULL*/
	if(num==0){
		printp(available, p);
		return NULL;
	}
	
	return NULL;
}
	
int *checkKingMoves(piece *p){
	int count = 0;
	int q[8] = { '0', '0', '0', '0', '0', '0', '0', '0' };
	/*Works when the king is on position "0"*/
	if (p->loc->cellID == 0){
		/*temperary pointer to a cell that the king can move to*/
		cell *temp = getCell(1, p->loc->board);
		/*makes sure that the cell the king is moving to has another piece*/
		if (temp->piece){
			/*makes sure that that piece is not of the same color*/
			if (temp->piece->player != p->player){
				/*enables the move*/
				q[count] = 1;
				count++;

			}
		}
		/*enables the move if there is no piece on that cell*/
		else{
			q[count] = 1;
			count++;
		}
		/*repeates the process for the other possible moves of the king*/
		temp = getCell(8, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = 8;
				count++;
			}
		}
		else{
			q[count] = 8;
			count++;
		}
		temp = getCell(9, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = 9;
				count++;
				/*insert how to display the next move*/
			}
		}
		else{
			q[count] = 9;
			count++;
		}
	}
	/*Works when the king is in position "7"*/
	else if (p->loc->cellID == 7){
		/*temperary pointer to a cell that the king can move to*/
		cell *temp = getCell(6, p->loc->board);
		/*makes sure that the cell the king is moving to has another piece*/
		if (temp->piece){
			/*makes sure that that piece is not of the same color*/
			if (temp->piece->player != p->player){
				/*enables the move*/
				q[count] = 6;
				count++;
			}
		}
		/*enables the move if there is no piece on that cell*/
		else{
			q[count] = 6;
			count++;
		}
		/*repeates the process for the other possible moves of the king*/
		temp = getCell(14, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = 14;
				count++;
			}
		}
		else{
			q[count] = 14;
			count++;
		}
		temp = getCell(15, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = 15;
				count++;
			}
		}
		else{
			q[count] = 15;
			count++;
		}
	}
	/*Works when the king is in position "56"*/
	else if (p->loc->cellID == 56){
		/*temperary pointer to a cell that the king can move to*/
		cell *temp = getCell(48, p->loc->board);
		/*makes sure that the cell the king is moving to has another piece*/
		if (temp->piece){
			/*makes sure that that piece is not of the same color*/
			if (temp->piece->player != p->player){
				/*enables the move*/
				q[count] = 48;
				count++;
			}
		}
		/*enables the move if there is no piece on that cell*/
		else{
			q[count] = 48;
			count++;
		}
		/*repeates the process for the other possible moves of the king*/
		temp = getCell(49, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = 49;
				count++;
			}
		}
		else{
			q[count] = 49;
			count++;
		}
		temp = getCell(57, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = 57;
				count++;
			}
		}
		else{
			q[count] = 57;
			count++;
		}

	}
	/*Works when the king is in position "63"*/
	else if (p->loc->cellID == 63){
		/*temperary pointer to a cell that the king can move to*/
		cell *temp = getCell(1, p->loc->board);
		/*makes sure that the cell the king is moving to has another piece*/
		if (temp->piece){
			/*makes sure that that piece is not of the same color*/
			if (temp->piece->player != p->player){
				/*enables the move*/
				q[count] = 54;
				count++;
			}
		}
		/*enables the move if there is no piece on that cell*/
		else{
			q[count] = 54;
			count++;
		}
		/*repeates the process for the other possible moves of the king*/
		temp = getCell(8, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = 55;
				count++;
			}
		}
		else{
			q[count] = 55;
			count++;
		}
		temp = getCell(9, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = 62;
				count++;
			}
		}
		else{
			q[count] = 62;
			count++;
		}
	}
	/*Works when the king is on the left most column of the board*/
	else if (p->loc->cellID % 8 == 0){
		/*temperary pointer to a cell that the king can move to*/
		cell *temp = getCell(p->loc->cellID + 1, p->loc->board);
		/*makes sure that the cell the king is moving to has another piece*/
		if (temp->piece){
			/*makes sure that that piece is not of the same color*/
			if (temp->piece->player != p->player){
				/*enables the move*/
				q[count] = p->loc->cellID + 1;
				count++;
			}
		}
		/*enables the move if there is no piece on that cell*/
		else{
			q[count] = p->loc->cellID + 1;
			count++;
		}
		/*repeates the process for the other possible moves of the king*/
		temp = getCell(p->loc->cellID + 8, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID + 8;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID + 8;
			count++;
		}
		temp = getCell(p->loc->cellID + 9, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID + 9;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID + 9;
			count++;
		}
		temp = getCell(p->loc->cellID - 8, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID - 8;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID - 8;
			count++;
		}
		temp = getCell(p->loc->cellID - 7, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID - 7;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID - 7;
			count++;
		}
	}
	/*Works when the king is in the right most column of the board*/
	else if ((p->loc->cellID + 1) % 8 == 0){
		/*temperary pointer to a cell that the king can move to*/
		cell *temp = getCell(p->loc->cellID - 1, p->loc->board);
		/*makes sure that the cell the king is moving to has another piece*/
		if (temp->piece){
			/*makes sure that that piece is not of the same color*/
			if (temp->piece->player != p->player){
				/*enables the move*/
				q[count] = p->loc->cellID - 1;
				count++;
			}
		}
		/*enables the move if there is no piece on that cell*/
		else{
			q[count] = p->loc->cellID - 1;
			count++;
		}
		/*repeates the process for the other possible moves of the king*/
		temp = getCell(p->loc->cellID + 8, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID + 8;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID + 8;
			count++;
		}
		temp = getCell(p->loc->cellID + 7, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID + 7;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID + 7;
			count++;
		}
		temp = getCell(p->loc->cellID - 8, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID - 8;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID - 8;
			count++;
		}
		temp = getCell(p->loc->cellID - 9, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID - 9;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID - 9;
			count++;
		}
	}
	/*Works when the king is on the white starting row*/
	else if (0 < p->loc->cellID && p->loc->cellID < 7){
		/*temperary pointer to a cell that the king can move to*/
		cell *temp = getCell(p->loc->cellID - 1, p->loc->board);
		/*makes sure that the cell the king is moving to has another piece*/
		if (temp->piece){
			/*makes sure that that piece is not of the same color*/
			if (temp->piece->player != p->player){
				/*enables the move*/
				q[count] = p->loc->cellID - 1;
				count++;
			}
		}
		/*enables the move if there is no piece on that cell*/
		else{
			q[count] = p->loc->cellID - 1;
			count++;
			/*Start of checking for castling on white left side*/
			if (p->hasMoved == 0){
				temp = getCell(p->loc->cellID - 2, p->loc->board);
				/*checks to see if there is a piece two spaces to the left of the king*/
				if (temp->piece == 0){
					temp = getCell(p->loc->cellID - 3, p->loc->board);
					/*checks to see if there is a piece three spaces to the left of the king*/
					if (temp->piece == 0){
						temp = getCell(p->loc->cellID - 4, p->loc->board);
						/*checks to see if there is a piece 4 spaces to the left of the king*/
						if (temp->piece){
							/*checks to see if that piece is a rook and has not moved*/
							if (temp->piece->hasMoved == 0){
								/*allows the castling*/
								q[count] = p->loc->cellID - 2;
								count++;
							}
						}
					}
				}
			}
		}
		/*repeates the process for the other possible moves of the king*/
		temp = getCell(p->loc->cellID + 8, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID + 8;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID + 8;
			count++;
		}
		temp = getCell(p->loc->cellID + 7, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID + 7;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID + 7;
			count++;
		}
		temp = getCell(p->loc->cellID + 1, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID + 1;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID + 1;
			count++;
			/*Start of checking for castling on white right side*/
			if (p->hasMoved == 0){
				temp = getCell(p->loc->cellID + 2, p->loc->board);
				/*checks to see if there is a piece 2 spaces to the right of the king*/
				if (temp->piece == 0){
					temp = getCell(p->loc->cellID + 3, p->loc->board);
					/*checks to see if there is a piece 3 spaces to the right of the king*/
					if (temp->piece){
						/*checks to see if that piece is a rook and has not moved*/
						if (temp->piece->hasMoved == 0){
							/*allows the castling*/
							q[count] = p->loc->cellID + 2;
							count++;
						}
					}
				}
			}
		}
		temp = getCell(p->loc->cellID + 9, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID + 9;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID + 9;
			count++;
		}
	}
	/*This occurs when the king is in the black starting row*/
	else if (56 < p->loc->cellID && p->loc->cellID < 63){
		/*temperary pointer to a cell that the king can move to*/
		cell *temp = getCell(p->loc->cellID - 1, p->loc->board);
		/*makes sure that the cell the king is moving to has another piece*/
		if (temp->piece){
			/*makes sure that that piece is not of the same color*/
			if (temp->piece->player != p->player){
				/*enables the move*/
				q[count] = p->loc->cellID - 1;
				count++;
			}
		}
		/*enables the move if there is no piece on that cell*/
		else{
			q[count] = p->loc->cellID - 1;
			count++;
			/*Start of checking for castling on black right side*/
			if (p->hasMoved == 0){
				temp = getCell(p->loc->cellID - 2, p->loc->board);
				/*checks to see if there is a piece two spaces to the right of the king*/
				if (temp->piece == 0){
					temp = getCell(p->loc->cellID - 3, p->loc->board);
					/*checks to see if there is a piece three spaces to the right of the king*/
					if (temp->piece == 0){
						temp = getCell(p->loc->cellID - 4, p->loc->board);
						/*checks to see if there is a piece 4 spaces to the right of the king*/
						if (temp->piece){
							/*checks to see if that piece is a rook and has not moved*/
							if (temp->piece->hasMoved == 0){
								/*allows the castling*/
								q[count] = p->loc->cellID - 2;
								count++;
							}
						}
					}
				}
			}
		}
		/*repeates the process for the other possible moves of the king*/
		temp = getCell(p->loc->cellID - 8, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID - 8;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID - 8;
			count++;
		}
		temp = getCell(p->loc->cellID - 7, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID - 7;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID - 7;
			count++;
		}
		temp = getCell(p->loc->cellID + 1, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID + 1;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID + 1;
			count++;
			/*Start of checking for castling on black left side*/
			if (p->hasMoved == 0){
				temp = getCell(p->loc->cellID + 2, p->loc->board);
				/*checks to see if there is a piece 2 spaces to the left of the king*/
				if (temp->piece == 0){
					temp = getCell(p->loc->cellID + 3, p->loc->board);
					/*checks to see if there is a piece 3 spaces to the left of the king*/
					if (temp->piece){
						/*checks to see if that piece is a rook and has not moved*/
						if (temp->piece->hasMoved == 0){
							/*allows the castling*/
							q[count] = p->loc->cellID + 2;
							count++;
						}
					}
				}
			}
		}
		temp = getCell(p->loc->cellID - 9, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID - 9;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID - 9;
			count++;
		}
	}
	else{
		/*temperary pointer to a cell that the king can move to*/
		cell *temp = getCell(p->loc->cellID - 1, p->loc->board);
		/*makes sure that the cell the king is moving to has another piece*/
		if (temp->piece){
			/*makes sure that that piece is not of the same color*/
			if (temp->piece->player != p->player){
				/*enables the move*/
				q[count] = p->loc->cellID - 1;
				count++;
			}
		}
		/*enables the move if there is no piece on that cell*/
		else{
			q[count] = p->loc->cellID - 1;
			count++;
		}
		/*repeates the process for the other possible moves of the king*/
		temp = getCell(p->loc->cellID - 8, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID - 8;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID - 8;
			count++;
		}
		temp = getCell(p->loc->cellID - 7, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID - 7;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID - 7;
			count++;
		}
		temp = getCell(p->loc->cellID + 1, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID + 1;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID + 1;
			count++;
		}
		temp = getCell(p->loc->cellID - 9, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID - 9;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID - 9;
			count++;
		}
		temp = getCell(p->loc->cellID + 7, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID + 7;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID + 7;
			count++;
		}
		temp = getCell(p->loc->cellID + 9, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID + 9;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID + 9;
			count++;
		}
		temp = getCell(p->loc->cellID + 8, p->loc->board);
		if (temp->piece){
			if (temp->piece->player != p->player){
				q[count] = p->loc->cellID + 8;
				count++;
			}
		}
		else{
			q[count] = p->loc->cellID + 8;
			count++;
		}
	}
	int *answer = malloc(sizeof(int)*(count + 2));
	int k;
	for (k = 0; k<count; k++){
		*answer = q[k];
		answer++;
	}
	printf("count is %d\n", count);
	*answer = -2;
	answer -= count;
	return answer;
}

int *checkRookMoves(piece *p){ /* Calculate rook piece's movement */
  int currentPos = p->loc->cellID;
  int moves[15] = {-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2};
  int checkPos;
  int count=0;
  
  if(currentPos%8!=0) /*If the piece is not on the left edge*/
  {
    for(checkPos=currentPos-1; checkPos%8 != 7; checkPos--)
    {
      cell *next = getCell(checkPos, p->loc->board);
      if(next->piece != NULL)
      {
        if(next->piece->player != p->player)
        {
          moves[count] = checkPos;
          count++;
        break;
        }
        else
        {
        break;
        }
      }
      moves[count] = checkPos;
      count++;
    }
  }
  if(currentPos%8!=7) /*If the piece is not on the right edge*/
  {
    for(checkPos=currentPos+1; checkPos%8 != 0; checkPos++)
    {
      cell *next = getCell(checkPos, p->loc->board);
      if(next->piece != NULL)
      {
        if(next->piece->player != p->player)
        {
          moves[count] = checkPos;
          count++;
        break;
        }
        else
        {
        break;
        }
      }
      moves[count] = checkPos;
      count++;
    }
  }
  if(currentPos > 7) /*checks if the piece is not in the bottom row*/
  {
    for(checkPos=currentPos-8; checkPos >= 0; checkPos-=8)  /*moving backwards*/
    {
      cell *next = getCell(checkPos, p->loc->board);
      if(next->piece != NULL)
      {
        if(next->piece->player != p->player)
        {
          moves[count] = checkPos;
          count++;
        break;
        }
        else
        {
        break;
        }
      }
      moves[count] = checkPos;
      count++;
    }
  }
  if(currentPos < 56) /*checks if the piece is not in the top row*/
  {
    for(checkPos=currentPos+8; checkPos <= 63; checkPos+=8)  /*moving forwards*/
    {
      cell *next = getCell(checkPos, p->loc->board);
      if(next->piece != NULL)
      {
        if(next->piece->player != p->player)
        {
          moves[count] = checkPos;
          count++;
        break;
        }
        else
        {
        break;
        }
      }
      moves[count] = checkPos;
      count++;
    }
  }
  int *ans = malloc(sizeof(int)*(count+1));
  int i=0;
  while(i <= count)
  {
    *ans = moves[i];
    ans++;
    i++;
  }
  ans -= i;
  return ans;
}

int *checkBishopMoves(piece *p){ /* Calculate bishop piece's movement */
  int currentPos = p->loc->cellID;
  int moves[14] = {-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2};
  int checkPos;
  int count=0;
  
  if(currentPos%8 != 0) /*If the piece is not on the left edge*/
  {
    for(checkPos=currentPos-9; checkPos >= 0; checkPos-=9)
    {
      cell *next = getCell(checkPos, p->loc->board);
      if(next->piece != NULL)
      {
        if(next->piece->player != p->player)
        {
          moves[count] = checkPos;
          count++;
        break;
        }
        else
        {
        break;
        }
      }
      moves[count] = checkPos;
      count++;
	  if(currentPos%8 == 0){
		  break;
	  }
    }
    for(checkPos=currentPos+7; checkPos <= 63; checkPos+=7)
    {
      cell *next = getCell(checkPos, p->loc->board);
      if(next->piece != NULL)
      {
        if(next->piece->player != p->player)
        {
          moves[count] = checkPos;
          count++;
        break;
        }
        else
        {
        break;
        }
      }
      moves[count] = checkPos;
      count++;
	  if(currentPos%8 == 0){
		  break;
	  }
    }
  }
  if(currentPos%8 != 7) /*If the piece is not on the right edge*/
  {
    for(checkPos=currentPos+9; checkPos <= 63; checkPos+=9)
    {
      cell *next = getCell(checkPos, p->loc->board);
      if(next->piece != NULL)
      {
        if(next->piece->player != p->player)
        {
          moves[count] = checkPos;
          count++;
        break;
        }
        else
        {
        break;
        }
      }
      moves[count] = checkPos;
      count++;
	  if(currentPos%8 == 7){
		  break;
	  }
    }
    for(checkPos=currentPos-7; checkPos >= 0; checkPos-=7)
    {
      cell *next = getCell(checkPos, p->loc->board);
      if(next->piece != NULL)
      {
        if(next->piece->player != p->player)
        {
          moves[count] = checkPos;
          count++;
        break;
        }
        else
        {
        break;
        }
      }
      moves[count] = checkPos;
      count++;
	  if(currentPos%8 == 7){
		  break;
	  }
    }
  }
  int *ans = malloc(sizeof(int)*(count+1));
  int i=0;
  while(i <= count)
  {
    *ans = moves[i];
    ans++;
    i++;
  }
  ans -= i;
  return ans;
}

int *checkQueenMoves(piece *p){
  int currentPos = p->loc->cellID;
  int moves[28] = {-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2};
  int checkPos;
  int count=0;
  
  /* rook moves */
  if(currentPos%8!=0) /*If the piece is not on the left edge*/
  {
    for(checkPos=currentPos-1; checkPos%8 != 7; checkPos--)
    {
      cell *next = getCell(checkPos, p->loc->board);
      if(next->piece != NULL)
      {
        if(next->piece->player != p->player)
        {
          moves[count] = checkPos;
          count++;
        break;
        }
        else
        {
        break;
        }
      }
      moves[count] = checkPos;
      count++;
    }
  }
  if(currentPos%8!=7) /*If the piece is not on the right edge*/
  {
    for(checkPos=currentPos+1; checkPos%8 != 0; checkPos++)
    {
      cell *next = getCell(checkPos, p->loc->board);
      if(next->piece != NULL)
      {
        if(next->piece->player != p->player)
        {
          moves[count] = checkPos;
          count++;
        break;
        }
        else
        {
        break;
        }
      }
      moves[count] = checkPos;
      count++;
    }
  }
  if(currentPos > 7) /*checks if the piece is not in the bottom row*/
  {
    for(checkPos=currentPos-8; checkPos >= 0; checkPos-=8)  /*moving backwards*/
    {
      cell *next = getCell(checkPos, p->loc->board);
      if(next->piece != NULL)
      {
        if(next->piece->player != p->player)
        {
          moves[count] = checkPos;
          count++;
        break;
        }
        else
        {
        break;
        }
      }
      moves[count] = checkPos;
      count++;
    }
  }
  if(currentPos < 56) /*checks if the piece is not in the top row*/
  {
    for(checkPos=currentPos+8; checkPos <= 63; checkPos+=8)  /*moving forwards*/
    {
      cell *next = getCell(checkPos, p->loc->board);
      if(next->piece != NULL)
      {
        if(next->piece->player != p->player)
        {
          moves[count] = checkPos;
          count++;
        break;
        }
        else
        {
        break;
        }
      }
      moves[count] = checkPos;
      count++;
    }
  }
  
  /* bishop moves */
  if(currentPos%8 != 0) /*If the piece is not on the left edge*/
  {
    for(checkPos=currentPos-9; checkPos >= 0; checkPos-=9)
    {
      cell *next = getCell(checkPos, p->loc->board);
      if(next->piece != NULL)
      {
        if(next->piece->player != p->player)
        {
          moves[count] = checkPos;
          count++;
        break;
        }
        else
        {
        break;
        }
      }
      moves[count] = checkPos;
      count++;
	  if(currentPos%8 == 0){
		  break;
	  }
    }
    for(checkPos=currentPos+7; checkPos <= 63; checkPos+=7)
    {
      cell *next = getCell(checkPos, p->loc->board);
      if(next->piece != NULL)
      {
        if(next->piece->player != p->player)
        {
          moves[count] = checkPos;
          count++;
        break;
        }
        else
        {
        break;
        }
      }
      moves[count] = checkPos;
      count++;
	  if(currentPos%8 == 0){
		  break;
	  }
    }
  }
  if(currentPos%8 != 7) /*If the piece is not on the right edge*/
  {
    for(checkPos=currentPos+9; checkPos <= 63; checkPos+=9)
    {
      cell *next = getCell(checkPos, p->loc->board);
      if(next->piece != NULL)
      {
        if(next->piece->player != p->player)
        {
          moves[count] = checkPos;
          count++;
        break;
        }
        else
        {
        break;
        }
      }
      moves[count] = checkPos;
      count++;
	  if(currentPos%8 == 7){
		  break;
	  }
    }
    for(checkPos=currentPos-7; checkPos >= 0; checkPos-=7)
    {
      cell *next = getCell(checkPos, p->loc->board);
      if(next->piece != NULL)
      {
        if(next->piece->player != p->player)
        {
          moves[count] = checkPos;
          count++;
        break;
        }
        else
        {
        break;
        }
      }
      moves[count] = checkPos;
      count++;
	  if(currentPos%8 == 7){
		  break;
	  }
    }
  }
  int *ans = malloc(sizeof(int)*(count+1));
  int i=0;
  while(i <= count)
  {
    *ans = moves[i];
    ans++;
    i++;
  }
  ans -= i;
  return ans;
}

/* also handles captures. possible return values:
 * 0 if move is valid
 * -1 if move is invalid
 * -2 if no available moves
 * 1 for a pawn promotion
 * 2 for kingside castle
 * 3 for queenside castle
 */
int movePiece(piece *p, cell *target){ 
	assert(p);
	assert(target);
	assert(target->cellID <= 63);
	assert(target->cellID >= 0);
	int *avail = checkAvailMoves(p);
	if (avail == NULL || (avail != NULL && *avail == -2)){
		return -2;
	}
	int ans;
	
	if (target->board->turn % 2 == 0){ /* before a white move, wipe all row 5 epFlags */
		int i;
		for (i = 24; i<=31; i++){
			cell *tmpi = getCell(i, target->board);
			if (tmpi->piece != NULL){
				tmpi->piece->epFlag = 0;
			}
		}
	}
	else{ /* before a black move, wipe all row 4 epFlags */
		int i;
		for (i = 32; i<=39; i++){
			cell *tmpi = getCell(i, target->board);
			if (tmpi->piece != NULL){
				tmpi->piece->epFlag = 0;
			}
		}
	}
	
	switch (p->type){
		case pawn:
			ans = movePawn(p, target, avail);
			if (ans < 0){
				return ans;
			}
			break;
		case knight:
			ans = moveKnight(p, target, avail);
			if (ans < 0){
				return ans;
			}
			break;
		case king:
			ans = moveKing(p, target, avail);
			if (ans < 0){
				return ans;
			}
			break;
		case queen:
			ans = moveQueen(p, target, avail);
			if (ans < 0){
				return ans;
			}
			break;		
		case rook:
			ans = moveRook(p, target, avail);
			if (ans < 0){
				return ans;
			}
			break;
		case bishop:
			ans = moveBishop(p, target, avail);
			if (ans < 0){
				return ans;
			}
			break;
	}
	if (ans >= 0)
		target->board->turn += 1;
	return ans;
}

int movePawn(piece *p, cell *target, int *avail){
	assert(target);
	int valid = -1; /* -1 is invalid, 0 is valid, 1 is promotion */
	while (*avail != -2){ /* this avail pointer comes from checkAvailMoves, recall that -2 is our null terminator */
		if (target->cellID == *avail){ /* if a match is found, the move is valid */
			valid = 0;
			break;
		}
		avail++;
	}
	if (valid == -1){ /* returns invalid if target doesn't equal any of the available moves */
		return valid;
	}
	if (target->piece != NULL){ /* basic capturing */
		replacePiece(getCell(-1, target->board), target->piece); /* sends the piece inside the target cell to cell -1 */
	}
	if (p->epFlag == 1 && target->piece == NULL){ /* en passant capturing */
		cell *epUp = getCell(target->cellID+8, target->board);
		cell *epDown = getCell(target->cellID-8, target->board);
		if (epUp != NULL && epUp->piece != NULL && epUp->piece->type == pawn && epUp->piece->player != p->player){
			replacePiece(getCell(-1, target->board), epUp->piece);
			updatePrintPiece(epUp);
			p->epFlag = 0;
		}
		else if (epDown != NULL && epDown->piece != NULL && epDown->piece->type == pawn && epDown->piece->player != p->player){
			replacePiece(getCell(-1, target->board), epDown->piece);
			updatePrintPiece(epDown);
			p->epFlag = 0;
		}
	}
	
	replacePiece(target, p); /* moves the piece to the target location */
	
	if (p->player == white && target->cellID == p->prev->cellID + 16){ /* if a pawn jumps and there are enemy pawns next to its destination, the enemy pawns can en passant next turn */
		if (target->cellID % 8 != 0){
			cell *tmpLeft = getCell(target->cellID - 1, target->board);
			if (tmpLeft->piece != NULL){
				if (tmpLeft->piece->type == pawn && tmpLeft->piece->player != p->player){
					tmpLeft->piece->epFlag = 1;
					p->epFlag = 1;
				}
			}
		}
		if (target->cellID != 7 || target->cellID != 15 || target->cellID != 23 || target->cellID != 31 || target->cellID != 39 || target->cellID != 47 || target->cellID != 55 || target->cellID != 63){
			cell *tmpRight = getCell(target->cellID + 1, target->board);
			if (tmpRight->piece != NULL){
				if (tmpRight->piece->type == pawn && tmpRight->piece->player != p->player){
					tmpRight->piece->epFlag = 1;
					p->epFlag = 1;
				}
			}
		}
	}
	else if (p->player == black && target->cellID == p->prev->cellID - 16){ /* if a pawn jumps and there are enemy pawns next to its destination, the enemy pawns can en passant next turn. En passant flag will be available on both the capturer and the captive */
		if (target->cellID % 8 != 0){
			cell *tmpLeft = getCell(target->cellID - 1, target->board);
			if (tmpLeft->piece != NULL){
				if (tmpLeft->piece->type == pawn && tmpLeft->piece->player != p->player){
					tmpLeft->piece->epFlag = 1;
					p->epFlag = 1;
				}
			}
		}
		if (target->cellID != 7 || target->cellID != 15 || target->cellID != 23 || target->cellID != 31 || target->cellID != 39 || target->cellID != 47 || target->cellID != 55 || target->cellID != 63){
			cell *tmpRight = getCell(target->cellID + 1, target->board);
			if (tmpRight->piece != NULL){
				if (tmpRight->piece->type == pawn && tmpRight->piece->player != p->player){
					tmpRight->piece->epFlag = 1;
					p->epFlag = 1;
				}
			}
		}
	}
	/* update the character displayed on the board for the current and previous position */
	updatePrintPiece(target);
	updatePrintPiece(p->prev);
	if (target->cellID < 8 || target->cellID > 55){
		valid = 1; /* pawn is to be promoted */
	}
	p->hasMoved = true;
	return valid;
}

int moveKnight(piece *p, cell *target, int *avail){
	  assert(target);
	int valid = -1; /* -1 is invalid, 0 is valid,*/
	while (*avail != -2){
		if (target->cellID == *avail){
			valid = 0;
			break;
		}
		avail++;
	}
	if (valid == -1){
		return valid;
	}
	if (target->piece != NULL){ /* capturing */
		replacePiece(getCell(-1, target->board), target->piece);
	}

	replacePiece(target, p);
	updatePrintPiece(target);
	updatePrintPiece(p->prev);
	p->hasMoved = false;
	return valid;
}

int moveKing(piece *p, cell *target, int *avail){
	
}

int moveQueen(piece *p, cell *target, int *avail){
	  assert(target);
	int valid = -1; /* -1 is invalid, 0 is valid,*/
	while (*avail != -2){
		if (target->cellID == *avail){
			valid = 0;
			break;
		}
		avail++;
	}
	if (valid == -1){
		return valid;
	}
	if (target->piece != NULL){ /* capturing */
		replacePiece(getCell(-1, target->board), target->piece);
	}

	replacePiece(target, p);
	updatePrintPiece(target);
	updatePrintPiece(p->prev);
	p->hasMoved = false;
	return valid;
}

int moveRook(piece *p, cell *target, int *avail){
  assert(target);
	int valid = -1; /* -1 is invalid, 0 is valid,*/
	while (*avail != -2){
		if (target->cellID == *avail){
			valid = 0;
			break;
		}
		avail++;
	}
	if (valid == -1){
		return valid;
	}
	if (target->piece != NULL){ /* capturing */
		replacePiece(getCell(-1, target->board), target->piece);
	}

	replacePiece(target, p);
	updatePrintPiece(target);
	updatePrintPiece(p->prev);
	p->hasMoved = false;
	return valid;
}

int moveBishop(piece *p, cell *target, int *avail){
	  assert(target);
	int valid = -1; /* -1 is invalid, 0 is valid,*/
	while (*avail != -2){
		if (target->cellID == *avail){
			valid = 0;
			break;
		}
		avail++;
	}
	if (valid == -1){
		return valid;
	}
	if (target->piece != NULL){ /* capturing */
		replacePiece(getCell(-1, target->board), target->piece);
	}

	replacePiece(target, p);
	updatePrintPiece(target);
	updatePrintPiece(p->prev);
	p->hasMoved = false;
	return valid;
}

int pawnPromotion(piece *p){ /* if undo is implemented, reverting back to pawn would be handled in the undo move function, not here */
	printf("Pawn in cell ");
	printCell(p->loc->cellID);
	printf(" promoted! Please select the piece to promote to:\n");
	printf("1: Queen\n");
	printf("2: Knight\n");
	printf("3: Rook\n");
	printf("4: Bishop\n");
	int tmp = 0;
	while (tmp < 1){
		scanf("%d", &tmp);
		switch(tmp){
			case 1:
				p->type = queen;
				break;
			case 2:
				p->type = knight;
				break;
			case 3:
				p->type = rook;
				break;
			case 4:
				p->type = bishop;
				break;
			default:
				printe(selection);
				tmp = 0;
				break;
		}
	}
	updatePrintPiece(p->loc);
	return tmp;
}

/* returns positive if white has favorable cost, negative if black has favorable cost */
int getCost(piece *p){
	return cost[p->type]*(p->player == white ? 1 : -1);
}
