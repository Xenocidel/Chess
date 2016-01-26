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
	int num=0;				/*number of available moves*/
	switch(p->type){
		case pawn:
		{	/*this bracket is to allow variable declarations within the case*/
			int frontchk = -1;      /*pawn can move forward*/
			int leftchk = -1;       /*pawn can capture diagonally left*/
			int rightchk = -1;      /*pawn can capture diagonally right*/
			int front2chk = -1;     /*pawn can move 2 spaces forward if it hasn't moved before*/
			int epleftchk = -1;         /*pawn can en passant left*/
			int eprightchk = -1;		/*pawn can en passant right*/
			
			if (p->player == white){	/*the else block reverses direction of the pawn*/
				cell *front = getCell((p->loc->cellID)+8, p->loc->board);
				cell *front2 = getCell((p->loc->cellID)+16, p->loc->board);
				cell *left = getCell((p->loc->cellID)+7, p->loc->board);
				cell *right = getCell((p->loc->cellID)+9, p->loc->board);
				/*DEBUG MESSAGES*/
				printf("DEBUG: white pawn cell locs:\n");
				printf("DEBUG: front: %d\n", front->cellID);
				printf("DEBUG: front2: %d\n", front2->cellID);
				printf("DEBUG: left: %d\n", left->cellID);
				printf("DEBUG: right: %d\n", right->cellID);
				
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
					if (!p->epFlag){
						if (left->piece != NULL){ /*if piece exists*/
							if (left->piece->player != p->player){ /*if its the opponent piece*/
								num++;
								leftchk = left->cellID;
							}
						}
					}
					/*en passant left capture*/
					else{
						cell *epleft = p->loc-1;
						if (epleft->piece != NULL){ /*if piece exists*/
							if (epleft->piece->player != p->player){ /*if its the opponent piece*/
								num++;
								epleftchk = epleft->cellID;
							}
						}
					}
				}
				
				if ((right->cellID)%8 != 0){ /*runs when not on right edge*/
					/*standard right diagonal capture*/
					if (!p->epFlag){
						if (right->piece != NULL){ /*if piece exists*/
							if (right->piece->player != p->player){ /*if its the opponent piece*/
								num++;
								rightchk = right->cellID;
							}
						}
					}
					/*en passant right capture*/
					else{
						cell *epright = p->loc+1;
						if (epright->piece != NULL){ /*if piece exists*/
							if (epright->piece->player != p->player){ /*if its the opponent piece*/
								num++;
								eprightchk = epright->cellID;
							}
						}
					}
				}
			}
			else{
				cell *front = getCell((p->loc->cellID)-8, p->loc->board);
				cell *front2 = getCell((p->loc->cellID)-16, p->loc->board);
				cell *left = getCell((p->loc->cellID)-9, p->loc->board);
				cell *right = getCell((p->loc->cellID)-7, p->loc->board);
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
					if (!p->epFlag){
						if (left->piece != NULL){ /*if piece exists*/
							if (left->piece->player != p->player){ /*if its the opponent piece*/
								num++;
								leftchk = left->cellID;
							}
						}
					}
					/*en passant left capture*/
					else{
						cell *epleft = p->loc-1;
						if (epleft->piece != NULL){ /*if piece exists*/
							if (epleft->piece->player != p->player){ /*if its the opponent piece*/
								num++;
								epleftchk = epleft->cellID;
							}
						}
					}
				}
				
				if ((right->cellID)%8 != 0){ /*runs when not on right edge*/
					/*standard right diagonal capture*/
					if (!p->epFlag){
						if (right->piece != NULL){ /*if piece exists*/
							if (right->piece->player != p->player){ /*if its the opponent piece*/
								num++;
								rightchk = right->cellID;
							}
						}
					}
					/*en passant right capture*/
					else{
						cell *epright = p->loc+1;
						if (epright->piece != NULL){ /*if piece exists*/
							if (epright->piece->player != p->player){ /*if its the opponent piece*/
								num++;
								eprightchk = epright->cellID;
							}
						}
					}
				}
			}
				
			/*if no available moves, print error and return null*/
			if (num==0){
				printp(available, p);
				return NULL;
			}
			/*DEBUG MESSAGE*/
			printf("DEBUG: %d available moves calculated\n", num);
			/*compile all available moves*/
			int *ans;
			ans = malloc(sizeof(int) * (num+1));
			int i;
			for (i=num; i>0; i--){
				if (frontchk > 0){
					*ans = frontchk;
					printf("DEBUG: frontchk (%d) stored in address %p\n", *ans, ans);
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
					printf("DEBUG: front2chk (%d) stored in address %p\n", *ans, ans);
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
			break; /*end of pawn*/
		}
	}
	
	return NULL;
}