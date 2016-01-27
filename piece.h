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

#ifndef PIECE_H_INCLUDED_
#define PIECE_H_INCLUDED_
#include "cell.h"

typedef struct cell cell;
struct piece{
	enum player { black, white } player;
	enum type {
			pawn,
			knight,
			king,
			queen,
			rook,
			bishop } type;
	enum hasMoved { false, true } hasMoved;
	int castleFlag;
	int epFlag;
	cell *loc;
	cell *prev;
};

struct piece *createPiece(enum player player, enum type type, cell *cell);
void deletePiece(struct piece *p);
void printLoc(struct piece *p);
int *checkAvailMoves(struct piece *p);
int *checkPawnMoves(struct piece *p);
int *checkKnightMoves(struct piece *p);
int *checkKingMoves(struct piece *p);
int *checkQueenMoves(struct piece *p);
int *checkRookMoves(struct piece *p);
int *checkBishopMoves(struct piece *p);

#endif