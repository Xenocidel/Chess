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
 * Created on 2016-01-06
 *
 */

#ifndef GAMEDISPLAY_H_INCLUDED_
#define GAMEDISPLAY_H_INCLUDED_

#include "board.h"
#include "piece.h"

void updateGameDisplay(board *board);
void updateMessage(board *board);
void printMessage();
void handleInput(board *board);
int toID(char *loc);
int moveSwitch(piece *piece, int destCell);
void checkAvailMovesSwitch(piece *piece);

void createMoveLog();
void writeMoveLog(int turn, piece *piece, int capture, int promo, int castle, int check);
const char * returnCell(int cellID);
void loadGame(char *fname, board *board);

#endif