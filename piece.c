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
			if (epleft->piece != NULL){
				if (epleft->piece->epFlag == 1){ /*en passant capture left */
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
				if (epright->piece->epFlag == 1){ /*en passant capture right */
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
		cell *epleft = getCell((p->loc->cellID)+1, p->loc->board);
		cell *epright = getCell((p->loc->cellID)-1, p->loc->board);
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
				if (epleft->piece->epFlag == 1){ /*en passant capture left */
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
				if (epright->piece->epFlag == 1){ /*en passant capture right */
					num++;
					eprightchk = right->cellID;	/*not epright because pawn captures diagonally */
				}
			}
		}
	}
		
	/*if no available moves, print error and return null*/
	if (num==0){
		printp(available, p);
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
	
int *checkKingMoves(struct piece *p){
	int count;
	char q[8] = { '0', '0', '0', '0', '0', '0', '0', '0' };
	count = 0;
	cell *temp;
	/*Works when the king is on position "0"*/
	if (p->loc->cellID == 0){
		/*temperary pointer to a cell that the king can move to*/
		temp = getCell(1, p->loc->board);
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
		temp = getCell(6, p->loc->board);
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
		temp = getCell(48, p->loc->board);
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
	/*Works when the king is in position "62"*/
	else if (p->loc->cellID == 62){
		/*temperary pointer to a cell that the king can move to*/
		temp = getCell(1, p->loc->board);
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
		temp = getCell(p->loc->cellID + 1, p->loc->board);
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
		temp = getCell(p->loc->cellID - 1, p->loc->board);
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
		temp = getCell(p->loc->cellID - 1, p->loc->board);
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
		temp = getCell(p->loc->cellID - 1, p->loc->board);
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
		temp = getCell(p->loc->cellID - 1, p->loc->board);
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
	int *answer = malloc(sizeof(int)*count + 1);
	int k;
	for (k = 0; k<count; k++){
		*answer = q[k];
		answer++;
	}
	*answer = -2;
	answer -= count;
	free(temp);
	return answer;
}

int *checkRookMoves(piece *p)
    {
        int fwd, rght, lft, bck, num= 0;
        int frontchk,frontchk2,frontchk3,frontchk4,frontchk5,frontchk6,frontchk7 = -1;
        int leftchk,leftchk2,leftchk3,leftchk4,leftchk5,leftchk6,leftchk7 = -1;
        int rightchk,rightchk2,rightchk3,rightchk4,rightchk5,rightchk6,rightchk7 = -1;
        int backchk,backchk2,backchk3,backchk4,backchk5,backchk6,backchk7 = -1;
        /*int obs;*/
        if (p->player == white)
        {
            /*the available moves for a Rook, not including edge detection.*/
            cell *front = getCell((p->loc->cellID)+8, p->loc->board);
            cell *front2 = getCell((p->loc->cellID)+16, p->loc->board);
            cell *front3 = getCell((p->loc->cellID)+24, p->loc->board);
            cell *front4 = getCell((p->loc->cellID)+32, p->loc->board);
            cell *front5 = getCell((p->loc->cellID)+40, p->loc->board);
            cell *front6 = getCell((p->loc->cellID)+48, p->loc->board);
            cell *front7 = getCell((p->loc->cellID)+56, p->loc->board);
            cell *right = getCell((p->loc->cellID)+1, p->loc->board);
            cell *right2 = getCell((p->loc->cellID)+2, p->loc->board);
            cell *right3 = getCell((p->loc->cellID)+3, p->loc->board);
            cell *right4 = getCell((p->loc->cellID)+4, p->loc->board);
            cell *right5 = getCell((p->loc->cellID)+5, p->loc->board);
            cell *right6 = getCell((p->loc->cellID)+6, p->loc->board);
            cell *right7 = getCell((p->loc->cellID)+7, p->loc->board);
            cell *left = getCell((p->loc->cellID)-1, p->loc->board);
            cell *left2 = getCell((p->loc->cellID)-2, p->loc->board);
            cell *left3 = getCell((p->loc->cellID)-3, p->loc->board);
            cell *left4 = getCell((p->loc->cellID)-4, p->loc->board);
            cell *left5 = getCell((p->loc->cellID)-5, p->loc->board);
            cell *left6 = getCell((p->loc->cellID)-6, p->loc->board);
            cell *left7 = getCell((p->loc->cellID)-7, p->loc->board);
            cell *back = getCell((p->loc->cellID)-8, p->loc->board);
            cell *back2 = getCell((p->loc->cellID)-16, p->loc->board);
            cell *back3 = getCell((p->loc->cellID)-24, p->loc->board);
            cell *back4 = getCell((p->loc->cellID)-32, p->loc->board);
            cell *back5 = getCell((p->loc->cellID)-40, p->loc->board);
            cell *back6 = getCell((p->loc->cellID)-48, p->loc->board);
            cell *back7 = getCell((p->loc->cellID)-56, p->loc->board);


            /*basic forward movement of Rook*/
            if (front->piece == NULL)
            {
                fwd++;
                frontchk = front->cellID;
            }
            if (front2->piece == NULL)
            {
                fwd++;
                frontchk2 = front2->cellID;
            }
            if (front3->piece == NULL)
            {
                fwd++;
                frontchk3 = front3->cellID;
            }
            if (front4->piece == NULL)
            {
                fwd++;
                frontchk4 = front4->cellID;
            }
            if (front5->piece == NULL)
            {
                fwd++;
                frontchk5 = front5->cellID;
            }
            if (front6->piece == NULL)
            {
                fwd++;
                frontchk6 = front6->cellID;
            }
            if (front7->piece == NULL)
            {
                fwd++;
                frontchk7 = front7->cellID;
            }

            /*basic right movement of the Rook*/
            if (right->piece == NULL)
            {
                rght++;
                rightchk = right->cellID;
            }
            if (right2->piece == NULL)
            {
                rght++;
                rightchk2 = right2->cellID;
            }
            if (right3->piece == NULL)
            {
                rght++;
                rightchk3 = right3->cellID;
            }
            if (right4->piece == NULL)
            {
                rght++;
                rightchk4 = right4->cellID;
            }
            if (right5->piece == NULL)
            {
                rght++;
                rightchk5 = right5->cellID;
            }
            if (right6->piece == NULL)
            {
                rght++;
                rightchk6 = right6->cellID;
            }
            if (right7->piece == NULL)
            {
                rght++;
                rightchk7 = right7->cellID;
            }

            /*basic left movement of the Rook*/
            if (left->piece == NULL)
            {
                lft++;
                leftchk = left->cellID;
            }
            if (left2->piece == NULL)
            {
                lft++;
                leftchk2 = left2->cellID;
            }
            if (left3->piece == NULL)
            {
                lft++;
                leftchk3 = left3->cellID;
            }
            if (left4->piece == NULL)
            {
                lft++;
                leftchk4 = left4->cellID;
            }
            if (left5->piece == NULL)
            {
                lft++;
                leftchk5 = left5->cellID;
            }
            if (left6->piece == NULL)
            {
                lft++;
                leftchk6 = left6->cellID;
            }
            if (left7->piece == NULL)
            {
                lft++;
                leftchk7 = left7->cellID;
            }

            /*basic backwards movement of the rook*/
            if (back->piece == NULL)
            {
                bck++;
                backchk = back->cellID;
            }
            if (back2->piece == NULL)
            {
                bck++;
                backchk2 = back2->cellID;
            }
            if (back3->piece == NULL)
            {
                bck++;
                backchk3 = back3->cellID;
            }
            if (back4->piece == NULL)
            {
                bck++;
                backchk4 = back4->cellID;
            }
            if (back5->piece == NULL)
            {
                bck++;
                backchk5 = back5->cellID;
            }
            if (back6->piece == NULL)
            {
                bck++;
                backchk6 = back6->cellID;
            }
            if (back7->piece == NULL)
            {
                bck++;
                backchk7 = back7->cellID;
            }

            /*when the rook is on the left edge*/
            if (front->cellID%8 == 0)
            {
                lft = 0;
            }

            /*when the rook is on the right edge*/
            if (front->cellID%8 == 7)
            {
                rght = 0;
            }

        }
        else
        {
            cell *front = getCell((p-> loc -> cellID)-8, p -> loc -> board);
            cell *front2 = getCell((p -> loc -> cellID)-16, p -> loc -> board);
            cell *front3 = getCell((p -> loc -> cellID)-24, p -> loc -> board);
            cell *front4 = getCell((p -> loc -> cellID)-32, p -> loc -> board);
            cell *front5 = getCell((p -> loc -> cellID)-40, p -> loc -> board);
            cell *front6 = getCell((p -> loc -> cellID)-48, p -> loc -> board);
            cell *front7 = getCell((p -> loc -> cellID)-56, p -> loc -> board);
            cell *right = getCell((p -> loc -> cellID)-1, p -> loc -> board);
            cell *right2 = getCell((p -> loc -> cellID)-2, p -> loc -> board);
            cell *right3 = getCell((p -> loc -> cellID)-3, p -> loc -> board);
            cell *right4 = getCell((p -> loc -> cellID)-4, p -> loc -> board);
            cell *right5 = getCell((p -> loc -> cellID)-5, p -> loc -> board);
            cell *right6 = getCell((p -> loc -> cellID)-6, p -> loc -> board);
            cell *right7 = getCell((p -> loc -> cellID)-7, p -> loc -> board);
            cell *left = getCell((p -> loc -> cellID)+1, p -> loc -> board);
            cell *left2 = getCell((p -> loc -> cellID)+2, p -> loc -> board);
            cell *left3 = getCell((p -> loc -> cellID)+3, p -> loc -> board);
            cell *left4 = getCell((p -> loc -> cellID)+4, p -> loc -> board);
            cell *left5 = getCell((p -> loc -> cellID)+5, p -> loc -> board);
            cell *left6 = getCell((p -> loc -> cellID)+6, p -> loc -> board);
            cell *left7 = getCell((p -> loc -> cellID)+7, p -> loc -> board);
            cell *back = getCell((p->loc->cellID)+8, p->loc->board);
            cell *back2 = getCell((p->loc->cellID)+16, p->loc->board);
            cell *back3 = getCell((p->loc->cellID)+24, p->loc->board);
            cell *back4 = getCell((p->loc->cellID)+32, p->loc->board);
            cell *back5 = getCell((p->loc->cellID)+40, p->loc->board);
            cell *back6 = getCell((p->loc->cellID)+48, p->loc->board);
            cell *back7 = getCell((p->loc->cellID)+56, p->loc->board);

/*basic forward movement of Rook*/
            if (front->piece == NULL)
            {
                fwd++;
                frontchk = front->cellID;
            }
            if (front2->piece == NULL)
            {
                fwd++;
                frontchk2 = front2->cellID;
            }
            if (front3->piece == NULL)
            {
                fwd++;
                frontchk3 = front3->cellID;
            }
            if (front4->piece == NULL)
            {
                fwd++;
                frontchk4 = front4->cellID;
            }
            if (front5->piece == NULL)
            {
                fwd++;
                frontchk5 = front5->cellID;
            }
            if (front6->piece == NULL)
            {
                fwd++;
                frontchk6 = front6->cellID;
            }
            if (front7->piece == NULL)
            {
                fwd++;
                frontchk7 = front7->cellID;
            }

/*basic right movement of the Rook*/
            if (right->piece == NULL)
            {
                rght++;
                rightchk = right->cellID;
            }
            if (right2->piece == NULL)
            {
                rght++;
                rightchk2 = right2->cellID;
            }
            if (right3->piece == NULL)
            {
                rght++;
                rightchk3 = right3->cellID;
            }
            if (right4->piece == NULL)
            {
                rght++;
                rightchk4 = right4->cellID;
            }
            if (right5->piece == NULL)
            {
                rght++;
                rightchk5 = right5->cellID;
            }
            if (right6->piece == NULL)
            {
                rght++;
                rightchk6 = right6->cellID;
            }
            if (right7->piece == NULL)
            {
                rght++;
                rightchk7 = right7->cellID;
            }

/*basic left movement of the Rook*/
            if (left->piece == NULL)
            {
                lft++;
                leftchk = left->cellID;
            }
            if (left2->piece == NULL)
            {
                lft++;
                leftchk2 = left2->cellID;
            }
            if (left3->piece == NULL)
            {
                lft++;
                leftchk3 = left3->cellID;
            }
            if (left4->piece == NULL)
            {
                lft++;
                leftchk4 = left4->cellID;
            }
            if (left5->piece == NULL)
            {
                lft++;
                leftchk5 = left5->cellID;
            }
            if (left6->piece == NULL)
            {
                lft++;
                leftchk6 = left6->cellID;
            }
            if (left7->piece == NULL)
            {
                lft++;
                leftchk7 = left7->cellID;
            }
            
/*basic backwards movement of the rook*/
            if (back->piece == NULL)
            {
                bck++;
                backchk = back->cellID;
            }
            if (back2->piece == NULL)
            {
                bck++;
                backchk2 = back2->cellID;
            }
            if (back3->piece == NULL)
            {
                bck++;
                backchk3 = back3->cellID;
            }
            if (back4->piece == NULL)
            {
                bck++;
                backchk4 = back4->cellID;
            }
            if (back5->piece == NULL)
            {
                bck++;
                backchk5 = back5->cellID;
            }
            if (back6->piece == NULL)
            {
                bck++;
                backchk6 = back6->cellID;
            }
            if (back7->piece == NULL)
            {
                bck++;
                backchk7 = back7->cellID;
            }

/*when the rook is on the left edge*/
            if (front->cellID%8 == 7)
            {
                lft = 0;
            }

/*when the rook is on the right edge*/
            if (front->cellID%8 == 0)
            {
                rght = 0;
            }

        }

        /*adding all the # of available moves for the rook*/
        num = fwd + rght + lft;
        /* if no available moves, print error and return null*/
        if (num==0)
        {
            printp(available, p);
            return NULL;
        }
  int *ans;
  ans = malloc(sizeof(int) * (num+1));
	int i;
	for (i=num; i>0; i--){
		if ((frontchk+frontchk2+frontchk3+frontchk4+frontchk5+frontchk6+frontchk7) > 0){
			*ans = (frontchk+frontchk2+frontchk3+frontchk4+frontchk5+frontchk6+frontchk7);
			frontchk = -2;
			ans++;
		}
		if ((leftchk+leftchk2+leftchk3+leftchk4+leftchk5+leftchk6+leftchk7) > 0){
			*ans = (leftchk+leftchk2+leftchk3+leftchk4+leftchk5+leftchk6+leftchk7);
			leftchk = -2;
			ans++;
		}
		if ((rightchk+rightchk2+rightchk3+rightchk4+rightchk5+rightchk6+rightchk7) > 0){
			*ans = (rightchk+rightchk2+rightchk3+rightchk4+rightchk5+rightchk6+rightchk7);
			rightchk = -2;
			ans++;
		}
		if ((backchk+backchk2+backchk3+backchk4+backchk5+backchk6+backchk7) > 0){
			*ans = (backchk+backchk2+backchk3+backchk4+backchk5+backchk6+backchk7);
			backchk = -2;
			ans++;
	    }
     }
        *ans = -2;
	      /*ans -= num;*/
        return ans;
    }


int *checkBishopMoves(piece *p){ /* Calculate bishop piece's movement */
	int num;
	int upLeftchk = -1;  /* Bishop can move up and left (cell+7) */
	int upRightchk = -1; /* Bishop can move up and right (cell+9) */
	int dnLeftchk = -1;  /* Bishop can move down and left (cell-9) */
	int dnRightchk = -1; /* Bishop can move down and right (cell-7) */
	int currentPos = p->loc->cellID; /* Holds piece's location */
	int rowStart = -1; /* Values of first & last cells of a row */
	int currentStart = -1;
	int rowEnd = -1;
	int currentEnd = -1;
	int moveArray[20]; /* Holds values of cells that bishop can legally move to */
	int entry = 0; /* Keeps track of position in MoveArray */
	
	/* Determine start & end of row bishop is on. Sets certain variables to zero */
	/* if there will be no moves the bishop can make in a certain direction.     */
	if(currentPos%8 == 0){ /* Checks if bishop is on left edge of board */
		upLeftchk = 0;		 
		dnLeftchk = 0;
		if(currentPos == 0){ /* Bottom left corner */
			dnRightchk = 0;
		}
		if(currentPos == 56){ /* Top left conrer */
			upRightchk = 0;
		}
		currentStart = currentPos;
		currentEnd = currentStart + 7;
	}
	if(currentPos == 7  || currentPos == 15 || currentPos == 23 || currentPos == 31 ||
	   currentPos == 39 || currentPos == 47 || currentPos == 55 || currentPos == 63 ){ 
	   /* Bishop on right edge */
		upRightchk = 0;
		dnRightchk = 0;
		if(currentPos == 7){ /* Bottom right corner */
			dnLeftchk = 0;
		}
		if(currentPos == 63){ /* Top right corner */
			upLeftchk = 0;
		}
		currentEnd = currentPos;
		currentStart = currentEnd-7;
	}
	else{ /* If piece is not on the edge of the board */
		int n;
		n = currentPos%8;
		currentStart = currentPos-n;
		currentEnd = currentStart + 7;
	}
	assert(currentStart >= 0 && currentEnd <= 63);
	
	int mult = 1; /* For calculating position additional rows up or down */
	rowStart = currentStart;
	rowEnd = currentEnd;
	while(upLeftchk){ /* Determines how many spaces up+left piece could move */
		rowStart += 8;
		rowEnd += 8;
		if(rowStart > 56 || rowEnd > 63){
		upLeftchk = 0;
		rowEnd = currentPos+7*mult;
		}
		if(currentPos+7*mult<rowEnd){
			num++;
			assert(currentPos+7*mult<=63 && currentPos+7*mult>=0);
			cell *read = getCell(currentPos+7*mult, p->loc->board);
			if(read->piece != NULL){ /* Calculated space is occupied */
				if(p->player == read->piece->player){ /* Can't capture own piece */
					num--;
					rowEnd = currentPos+7*mult;
				}
				upLeftchk = 0;
			}
		}
		else if(currentPos+7*mult == rowEnd){
			upLeftchk = 0;
		}
		if(currentPos+7*mult != rowEnd){
			moveArray[entry] = currentPos+7*mult;
			entry++;
		}
		if(currentPos+7*mult == rowStart){
			  upLeftchk = 0;
		}
		mult++;
		if(mult >= 7){
			upLeftchk = 0;
		}
	}
	mult = 1;
	rowStart = currentStart;
	rowEnd = currentEnd;
	while(upRightchk){ /* Determines how many spaces up+right piece could move */
		rowStart += 8;
		rowEnd += 8;
		if(rowStart > 56 || rowEnd > 63){
			upRightchk = 0;
			rowStart = currentPos+9*mult-8;
			rowEnd = -100;
		}
		if(currentPos+9*mult<rowEnd){
			num++;
			assert(currentPos+9*mult<=63 && currentPos+9*mult>=0);
			cell *read = getCell(currentPos+9*mult, p->loc->board);
			if(read->piece != NULL){ /* Calculated space is occupied */
				if(p->player == read->piece->player){ /* Can't capture own piece */
					num--;
					rowStart = currentPos+9*mult-8;
				}
				upRightchk = 0;
			}
		}
		else if(currentPos+9*mult == rowStart+8){
			upRightchk = 0;
		}
		if(currentPos+9*mult != rowStart+8){
			moveArray[entry] = currentPos+9*mult;
			entry++;
		}
		if(currentPos+9*mult == rowEnd){
			upRightchk = 0;
		}
		mult++;
		if(mult >= 7){
			upRightchk = 0;
		}
	}
	mult = 1;
	rowStart = currentStart;
	rowEnd = currentEnd;
	while(dnLeftchk){ /* Determines how many spaces down+left piece could move */
		rowStart -= 8;
		rowEnd -= 8;
		if(rowStart < 0 || rowEnd < 7){
			dnLeftchk = 0;
			rowStart = 63;
			rowEnd = currentPos-9*mult+8;
		}
		if(currentPos-9*mult>=rowStart){
			num++;
		assert(currentPos-9*mult<=63 && currentPos-9*mult>=0);
			cell *read = getCell(currentPos-9*mult, p->loc->board);
			if(read->piece != NULL){ /* Calculated space is occupied */
				if(p->player == read->piece->player){ /* Can't capture own piece */
					num--;
					rowEnd = currentPos-9*mult+8;
				}
				dnLeftchk = 0;
			}
		}
		else if(currentPos-9*mult == rowEnd-8){
			dnLeftchk = 0;
		}
		if(currentPos-9*mult != rowEnd-8){
			moveArray[entry] = currentPos-9*mult;
			entry++;
		}	
		if(currentPos-9*mult == rowStart){
			dnLeftchk = 0;
		}
		mult++;
		if(mult >= 7){
			dnLeftchk = 0;
		}
	}
	mult = 1;
	rowStart = currentStart;
	rowEnd = currentEnd;
	while(dnRightchk){ /* Determines how many spaces down+right piece could move */
		rowStart -= 8;
		rowEnd -= 8;
		if(rowStart < 0 || rowEnd < 7){
			dnRightchk = 0;
			rowStart = currentPos-7*mult;
			mult = 1;
		}
		if(currentPos-7*mult<=rowEnd){
			num++;
			assert(currentPos-7*mult<=63 && currentPos-7*mult>=0);
			cell *read = getCell(currentPos-7*mult, p->loc->board);
			if(read->piece != NULL){ /* Calculated space is occupied */
				if(p->player == read->piece->player){ /* Can't capture own piece */
					num--;
					rowStart = currentPos-7*mult;
				}
				dnRightchk = 0;
			}
		}
		else if(currentPos-7*mult == rowStart){
			dnRightchk = 0;
		}
		if(currentPos-7*mult != rowStart){
			moveArray[entry] = currentPos-7*mult;
			entry++;
		}
		if(currentPos-7*mult == rowEnd){
			dnRightchk = 0;
		}
		mult++;
		if(mult >= 7){
			dnRightchk = 0;
		}
	}
	
	if(num == 0){ /* No available moves, error message */
		printp(available, p);
		return NULL;
	}
	/* Below transfers moves list to pointer from array */
	int *ans = malloc(sizeof(int)*num);
	int i;
	for(i=0; i<num; i++){
		/* printf("%d\n", moveArray[i]); /* Debug */
		*(ans+i) = moveArray[i];
		moveArray[i] = 0;
	}
	*(ans+i) = -2;
	return ans; /* Returns pointer to list of available moves */
	/* free(ans); Probably needs to be freed after moves are displayed to player */
}

int *checkQueenMoves(piece *p){

	int i;
	int num=0;
	cell *piecelocation = getCell((p->loc->cellID), p->loc->board);
        int movearray[64];
        int entry =0;
		
		if (piecelocation->cellID < 56)
		{
			for (i=1;i<8;i++)		/*upward motion from non-top row starting position*/
			{		
				cell *front = getCell((p->loc->cellID)+(8*i), p->loc->board);
				if (front->cellID < 64)
				{
					if (front->piece == NULL)
					{
						num++;
						movearray[entry] = front->cellID;
						entry++;
					}					
					if (front->piece != NULL)
					{
						if (front->piece->player != p->player)
						{
							num++;
							movearray[entry] = front->cellID;
							entry++;
							break;
						}						
						else 
						{
							break;
						}
					}
				}
        else{
          break;
        }
			}
		}

		if (piecelocation->cellID > 7)		/*downward motion from non-bottom row starting position*/
		{
			for (i=1; i<8;i++)
			{
				cell *back = getCell((p->loc->cellID)-(8*i), p->loc->board);
				if (back->cellID >=0)
				{
					if (back->piece == NULL)
					{
						num++;
						movearray[entry] = back->cellID;
						entry++;
					}
					if (back->piece != NULL)
					{
						if (back->piece->player != p->player)
						{
							num++;
							movearray[entry] = back->cellID;
							entry++;
							break;
						}
						else 
						{
							break;
						}
					}
				}
        else{
          break;
        }
			}
		}

		if (((piecelocation->cellID-7)%8) != 0)		/*rightward motion from non-rightside column*/
		{	
			for (i=1; i<8; i++)
			{
				cell *right = getCell((p->loc->cellID)+i, p->loc->board);
				if (right->piece == NULL)
				{
					num++;
					movearray[entry] = right->cellID;
					entry++;
				}
				if(right->piece != NULL)
				{
					if (right->piece->player != p->player)
					{
						num++;
						movearray[entry] = right->cellID;
						entry++;
						break;
					}
					else 
					{
						break;
					}
				}
        			if ((right->cellID-7)%8 == 0)
				{
          				break;
			        }
			}
		}

		if ((piecelocation->cellID%8) != 0)		/*leftward motion from non-rightside column*/
		{
			for (i=1;i<8;i++)
			{
				cell *left = getCell((p->loc->cellID)-i, p->loc->board);
				if (left->piece == NULL)
				{
					num++;
					movearray[entry] = left->cellID;
					entry++;
				}
				if(left->piece != NULL)
				{
					if (left->piece->player != p->player)
					{
						num++;
						movearray[entry] = left->cellID;
						entry++;
						break;
					}
					else 
					{
						break;
					{
				}
			}
		}

		if (((piecelocation->cellID-7)%8) != 0 && piecelocation->cellID < 56)		/*upright diagonal motion*/
		{
			for (i=1; i<8; i++)
			{
				cell *upright = getCell((p->loc->cellID)+(9*i), p->loc->board);
				if (upright->piece == NULL)
				{
					num++;
					movearray[entry] = upright->cellID;
					entry++;
				}
				if (upright->piece != NULL)
				{
					if (upright->piece->player != p->player)
					{
						num++;
						movearray[entry] = upright->cellID;
						entry++;
						break;
					}
					else 
					{
						break;
					}
				}
          			if (((upright->cellID-7)%8) != 0 || upright->cellID < 56)
				{
			            break;
          			}
			}
		}
   
		if (((piecelocation->cellID-7)%8) != 0 && piecelocation->cellID > 7)		/*downright diagonal motion*/
		{
			for (i=1; i<8; i++)
			{
				cell *downright = getCell((p->loc->cellID)-(7*i), p->loc->board);
				if (downright->piece == NULL)
				{
					num++;
					movearray[entry] = downright->cellID;
					entry++;
				}
				if (downright->piece != NULL)
				{
					if (downright->piece->player != p->player)
					{
						num++;
						movearray[entry] = downright->cellID;
						entry++;
						break;
					}
					else 
					{
						break;
					}
				}
			        if (((downright->cellID-7)%8) != 0 || downright->cellID < 7)
				{
           				break;
          			}
			}
		}
			
		if ((piecelocation->cellID%8) != 0 && piecelocation->cellID < 56)		/*upleft diagonal motion*/
		{
			for (i=1; i<8; i++)
			{
				cell *upleft = getCell((p->loc->cellID)+(7*i), p->loc->board);
				if (upleft->piece == NULL)
				{
					num++;
					movearray[entry] = upleft->cellID;
					entry++;
				}
				if (upleft->piece != NULL)
				{
					if (upleft->piece->player != p->player)
					{
						num++;
						movearray[entry] = upleft->cellID;
						entry++;
						break;
					}
					else 
					{
						break;
					}
				}
			        if ((upleft->cellID%8) != 0 || upleft->cellID < 56)
				{
		            		break;
          			}
			}
		}
   
		if ((piecelocation->cellID%8) != 0 && piecelocation->cellID < 56)		/*downleft diagonal motion*/
		{
			for (i=1; i<8; i++)
			{
				cell *downleft = getCell((p->loc->cellID)+(7*i), p->loc->board);
				if (downleft->piece == NULL)
				{
					num++;
					movearray[entry] = downleft->cellID;
					entry++;
				}
				if (downleft->piece != NULL)
				{
					if (downleft->piece->player != p->player)
					{
						num++;
						movearray[entry] = downleft->cellID;
						entry++;
						break;
					}
					else 
					{
						break;
					}
				}
			        if ((downleft->cellID%8) != 0 || downleft->cellID < 7)
				{
           				 break;
        			}
			}
		}
	if(num == 0)	/* No available moves*/
	{ 
		printp(available, p);
		return NULL;
	}
  int *ans=malloc(sizeof(int)*num);
	for (i=0;i<num;i++)
	{
		*(ans+i) = movearray[i];
		movearray[i] =0 ;
	}
	*(ans+i) = -2;
  return ans;
  /*free(ans);*/
}
}
}


int movePiece(piece *p, cell *target){ /* also handles captures. returns 0 if move is valid, -1 if move is invalid, -2 if no available moves, 1 for a pawn promotion */
	assert(p);
	assert(target);
	assert(target->cellID <= 63);
	assert(target->cellID >= 0);
	int *avail = checkAvailMoves(p);
	if (avail == NULL){
		return -2
	}
	switch (p->type){
		case pawn: return movePawn(p, target, avail);
		break;
		case knight: return moveKnight(p, target, avail);
		break;
		case king: return moveKing(p, target, avail);
		break;
		case queen: return moveQueen(p, target, avail);
		break;
		case rook: return moveRook(p, target, avail);
		break;
		case bishop:return moveBishop(p, target, avail);
		break;
	}
	return -1;
}

int movePawn(piece *p, cell *target, int *avail){
	assert(target);
	int valid = -1; /* -1 is invalid, 0 is valid, 1 is promotion */
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
	if (target->cellID < 8 || target->cellID > 55){
		valid = 1; /* pawn is to be promoted */
	}
	return valid;
}

int moveKnight(piece *p, cell *target, int *avail){
	
}

int moveKing(piece *p, cell *target, int *avail){
	
}

int moveQueen(piece *p, cell *target, int *avail){
	
}

int moveRook(piece *p, cell *target, int *avail){
	
}

int moveBishop(piece *p, cell *target, int *avail){
	
}
