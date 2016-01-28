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

#ifndef CELL_H_INCLUDED_
#define CELL_H_INCLUDED_
#include "piece.h"
#include "board.h"

typedef struct piece piece;
typedef struct board board;
struct cell{
	char printPiece;
	int cellID;		/*range from -1 to 63. -1 for captured pieces.*/
	piece *piece;
	board *board;
} ;

struct cell *createCell(int cellID, board *board);
void replacePiece(struct cell *cell, piece *p);
void deleteCell(struct cell *cell);	/*deletes all pieces as well*/
void deleteAllCells(board *board); /*used at program shutdown, delete board separately*/
void updatePrintPiece(struct cell *cell);

#endif