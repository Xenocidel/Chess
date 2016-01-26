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