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

#ifndef BOARD_H_INCLUDED_
#define BOARD_H_INCLUDED_
#include "cell.h"

#define MINUS1 board->minus1
#define CELL0  board->cell0
#define CELL1  board->cell1
#define CELL2  board->cell2
#define CELL3  board->cell3
#define CELL4  board->cell4
#define CELL5  board->cell5
#define CELL6  board->cell6
#define CELL7  board->cell7
#define CELL8  board->cell8
#define CELL9  board->cell9
#define CELL10 board->cell10
#define CELL11 board->cell11
#define CELL12 board->cell12
#define CELL13 board->cell13
#define CELL14 board->cell14
#define CELL15 board->cell15
#define CELL16 board->cell16
#define CELL17 board->cell17
#define CELL18 board->cell18
#define CELL19 board->cell19
#define CELL20 board->cell20
#define CELL21 board->cell21
#define CELL22 board->cell22
#define CELL23 board->cell23
#define CELL24 board->cell24
#define CELL25 board->cell25
#define CELL26 board->cell26
#define CELL27 board->cell27
#define CELL28 board->cell28
#define CELL29 board->cell29
#define CELL30 board->cell30
#define CELL31 board->cell31
#define CELL32 board->cell32
#define CELL33 board->cell33
#define CELL34 board->cell34
#define CELL35 board->cell35
#define CELL36 board->cell36
#define CELL37 board->cell37
#define CELL38 board->cell38
#define CELL39 board->cell39
#define CELL40 board->cell40
#define CELL41 board->cell41
#define CELL42 board->cell42
#define CELL43 board->cell43
#define CELL44 board->cell44
#define CELL45 board->cell45
#define CELL46 board->cell46
#define CELL47 board->cell47
#define CELL48 board->cell48
#define CELL49 board->cell49
#define CELL50 board->cell50
#define CELL51 board->cell51
#define CELL52 board->cell52
#define CELL53 board->cell53
#define CELL54 board->cell54
#define CELL55 board->cell55
#define CELL56 board->cell56
#define CELL57 board->cell57
#define CELL58 board->cell58
#define CELL59 board->cell59
#define CELL60 board->cell60
#define CELL61 board->cell61
#define CELL62 board->cell62
#define CELL63 board->cell63

struct board{
	struct cell *minus1;
	struct cell *cell0 ;
	struct cell *cell1 ;
	struct cell *cell2 ;
	struct cell *cell3 ;
	struct cell *cell4 ;
	struct cell *cell5 ;
	struct cell *cell6 ;
	struct cell *cell7 ;
	struct cell *cell8 ;
	struct cell *cell9 ;
	struct cell *cell10;
	struct cell *cell11;
	struct cell *cell12;
	struct cell *cell13;
	struct cell *cell14;
	struct cell *cell15;
	struct cell *cell16;
	struct cell *cell17;
	struct cell *cell18;
	struct cell *cell19;
	struct cell *cell20;
	struct cell *cell21;
	struct cell *cell22;
	struct cell *cell23;
	struct cell *cell24;
	struct cell *cell25;
	struct cell *cell26;
	struct cell *cell27;
	struct cell *cell28;
	struct cell *cell29;
	struct cell *cell30;
	struct cell *cell31;
	struct cell *cell32;
	struct cell *cell33;
	struct cell *cell34;
	struct cell *cell35;
	struct cell *cell36;
	struct cell *cell37;
	struct cell *cell38;
	struct cell *cell39;
	struct cell *cell40;
	struct cell *cell41;
	struct cell *cell42;
	struct cell *cell43;
	struct cell *cell44;
	struct cell *cell45;
	struct cell *cell46;
	struct cell *cell47;
	struct cell *cell48;
	struct cell *cell49;
	struct cell *cell50;
	struct cell *cell51;
	struct cell *cell52;
	struct cell *cell53;
	struct cell *cell54;
	struct cell *cell55;
	struct cell *cell56;
	struct cell *cell57;
	struct cell *cell58;
	struct cell *cell59;
	struct cell *cell60;
	struct cell *cell61;
	struct cell *cell62;
	struct cell *cell63;
} ;

struct cell *getCell(int cellID, struct board *board);
struct board *createNewGame();
struct board *createBoard();
void updateBoard();
void deleteBoard(struct board *board);

#endif