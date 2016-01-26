#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "board.h"
#include "cell.h"
/*Hello*/
void deleteBoard(board *board){
	assert(board);
	free(board);
}

cell *getCell(int cellID, board *board){
	switch(cellID){
		case -1: return MINUS1;
		case 0 : return CELL0 ;
		case 1 : return CELL1 ;
		case 2 : return CELL2 ;
		case 3 : return CELL3 ;
		case 4 : return CELL4 ;
		case 5 : return CELL5 ;
		case 6 : return CELL6 ;
		case 7 : return CELL7 ;
		case 8 : return CELL8 ;
		case 9 : return CELL9 ;
		case 10: return CELL10;
		case 11: return CELL11;
		case 12: return CELL12;
		case 13: return CELL13;
		case 14: return CELL14;
		case 15: return CELL15;
		case 16: return CELL16;
		case 17: return CELL17;
		case 18: return CELL18;
		case 19: return CELL19;
		case 20: return CELL20;
		case 21: return CELL21;
		case 22: return CELL22;
		case 23: return CELL23;
		case 24: return CELL24;
		case 25: return CELL25;
		case 26: return CELL26;
		case 27: return CELL27;
		case 28: return CELL28;
		case 29: return CELL29;
		case 30: return CELL30;
		case 31: return CELL31;
		case 32: return CELL32;
		case 33: return CELL33;
		case 34: return CELL34;
		case 35: return CELL35;
		case 36: return CELL36;
		case 37: return CELL37;
		case 38: return CELL38;
		case 39: return CELL39;
		case 40: return CELL40;
		case 41: return CELL41;
		case 42: return CELL42;
		case 43: return CELL43;
		case 44: return CELL44;
		case 45: return CELL45;
		case 46: return CELL46;
		case 47: return CELL47;
		case 48: return CELL48;
		case 49: return CELL49;
		case 50: return CELL50;
		case 51: return CELL51;
		case 52: return CELL52;
		case 53: return CELL53;
		case 54: return CELL54;
		case 55: return CELL55;
		case 56: return CELL56;
		case 57: return CELL57;
		case 58: return CELL58;
		case 59: return CELL59;
		case 60: return CELL60;
		case 61: return CELL61;
		case 62: return CELL62;
		case 63: return CELL63;
		default: return NULL;
	}
}

board *createNewGame(){		/*creates an empty board*/
	board *ans = malloc(sizeof(board));
	ans->minus1 = createCell(-1, ans);
	ans->cell0  = createCell(0 , ans);
	ans->cell1  = createCell(1 , ans);
	ans->cell2  = createCell(2 , ans);
	ans->cell3  = createCell(3 , ans);
	ans->cell4  = createCell(4 , ans);
	ans->cell5  = createCell(5 , ans);
	ans->cell6  = createCell(6 , ans);
	ans->cell7  = createCell(7 , ans);
	ans->cell8  = createCell(8 , ans);
	ans->cell9  = createCell(9 , ans);
	ans->cell10 = createCell(10, ans);
	ans->cell11 = createCell(11, ans);
	ans->cell12 = createCell(12, ans);
	ans->cell13 = createCell(13, ans);
	ans->cell14 = createCell(14, ans);
	ans->cell15 = createCell(15, ans);
	ans->cell16 = createCell(16, ans);
	ans->cell17 = createCell(17, ans);
	ans->cell18 = createCell(18, ans);
	ans->cell19 = createCell(19, ans);
	ans->cell20 = createCell(20, ans);
	ans->cell21 = createCell(21, ans);
	ans->cell22 = createCell(22, ans);
	ans->cell23 = createCell(23, ans);
	ans->cell24 = createCell(24, ans);
	ans->cell25 = createCell(25, ans);
	ans->cell26 = createCell(26, ans);
	ans->cell27 = createCell(27, ans);
	ans->cell28 = createCell(28, ans);
	ans->cell29 = createCell(29, ans);
	ans->cell30 = createCell(30, ans);
	ans->cell31 = createCell(31, ans);
	ans->cell32 = createCell(32, ans);
	ans->cell33 = createCell(33, ans);
	ans->cell34 = createCell(34, ans);
	ans->cell35 = createCell(35, ans);
	ans->cell36 = createCell(36, ans);
	ans->cell37 = createCell(37, ans);
	ans->cell38 = createCell(38, ans);
	ans->cell39 = createCell(39, ans);
	ans->cell40 = createCell(40, ans);
	ans->cell41 = createCell(41, ans);
	ans->cell42 = createCell(42, ans);
	ans->cell43 = createCell(43, ans);
	ans->cell44 = createCell(44, ans);
	ans->cell45 = createCell(45, ans);
	ans->cell46 = createCell(46, ans);
	ans->cell47 = createCell(47, ans);
	ans->cell48 = createCell(48, ans);
	ans->cell49 = createCell(49, ans);
	ans->cell50 = createCell(50, ans);
	ans->cell51 = createCell(51, ans);
	ans->cell52 = createCell(52, ans);
	ans->cell53 = createCell(53, ans);
	ans->cell54 = createCell(54, ans);
	ans->cell55 = createCell(55, ans);
	ans->cell56 = createCell(56, ans);
	ans->cell57 = createCell(57, ans);
	ans->cell58 = createCell(58, ans);
	ans->cell59 = createCell(59, ans);
	ans->cell60 = createCell(60, ans);
	ans->cell61 = createCell(61, ans);
	ans->cell62 = createCell(62, ans);
	ans->cell63 = createCell(63, ans);
	return ans;
}

void updateBoard(){
	
}