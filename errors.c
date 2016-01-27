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
#include "errors.h"
#include "defs.h"


/*print error function*/
void printe(int code){
	switch(code){
		case 0:
			printf("Invalid move. Please try again.\n\n");
			break;
		case 1:
			printf("Unknown command. Please try again.\n\n");
			break;
		case 2:
			printf("Invalid selection. Please try again.\n\n");
			break;
		default:
			printf("Unknown error has occured. Program terminating...\n\n");
			exit(1);
	}
}
/*print error function with specific piece location; function name has been changed to printp since C doesn't support overloading*/
void printp(int code, piece *p){
	if (code!=3){
		printf("Unknown error has occured. Program terminating...\n");
		exit(1);
	}
	switch(p->type){
		case pawn:
			printf("No available moves for Pawn at");
			printLoc(p);
			break;
		case knight:
			printf("No available moves for Knight at");
			printLoc(p);
			break;
		case king:
			printf("No available moves for King at");
			printLoc(p);
			break;
		case queen:
			printf("No available moves for Queen at");
			printLoc(p);
			break;
		case rook:
			printf("No available moves for Rook at");
			printLoc(p);
			break;
		case bishop:
			printf("No available moves for Bishop at");
			printLoc(p);
			break;
		default:
			printf("Unexpected piece type in printp function");
			exit(2);
	}
}