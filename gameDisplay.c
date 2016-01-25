#include "gameDisplay.h"
void updateBoard(){
	printf("    a   b   c   d   e   f   g   h\n");
	printf("  +---+---+---+---+---+---+---+---+n");
	printf("8 | %c | %c | %c | %c | %c | %c | %c | %c | 8\n", CELL56.printPiece, CELL57.printPiece, CELL58.printPiece, CELL59.printPiece, CELL60.printPiece, CELL61.printPiece, CELL62.printPiece, CELL63.printPiece);
	printf("  +---+---+---+---+---+---+---+---+n");
	printf("7 | %c | %c | %c | %c | %c | %c | %c | %c | 7\n", CELL48.printPiece, CELL49.printPiece, CELL50.printPiece, CELL51.printPiece, CELL52.printPiece, CELL53.printPiece, CELL54.printPiece, CELL55.printPiece);
	printf("  +---+---+---+---+---+---+---+---+n");
	printf("6 | %c | %c | %c | %c | %c | %c | %c | %c | 6\n", CELL40.printPiece, CELL41.printPiece, CELL42.printPiece, CELL43.printPiece, CELL44.printPiece, CELL45.printPiece, CELL46.printPiece, CELL47.printPiece);
	printf("  +---+---+---+---+---+---+---+---+n");
	printf("5 | %c | %c | %c | %c | %c | %c | %c | %c | 5\n", CELL32.printPiece, CELL33.printPiece, CELL34.printPiece, CELL35.printPiece, CELL36.printPiece, CELL37.printPiece, CELL38.printPiece, CELL39.printPiece);
	printf("  +---+---+---+---+---+---+---+---+n");
	printf("4 | %c | %c | %c | %c | %c | %c | %c | %c | 4\n", CELL24.printPiece, CELL25.printPiece, CELL26.printPiece, CELL27.printPiece, CELL28.printPiece, CELL29.printPiece, CELL30.printPiece, CELL31.printPiece);
	printf("  +---+---+---+---+---+---+---+---+n");
	printf("3 | %c | %c | %c | %c | %c | %c | %c | %c | 3\n", CELL16.printPiece, CELL17.printPiece, CELL18.printPiece, CELL19.printPiece, CELL20.printPiece, CELL21.printPiece, CELL22.printPiece, CELL23.printPiece);
	printf("  +---+---+---+---+---+---+---+---+n");
	printf("2 | %c | %c | %c | %c | %c | %c | %c | %c | 2\n", CELL8.printPiece, CELL9.printPiece, CELL10.printPiece, CELL11.printPiece, CELL12.printPiece, CELL13.printPiece, CELL14.printPiece, CELL15.printPiece);
	printf("  +---+---+---+---+---+---+---+---+n");
	printf("1 | %c | %c | %c | %c | %c | %c | %c | %c | 1\n", CELL0.printPiece, CELL1.printPiece, CELL2.printPiece, CELL3.printPiece, CELL4.printPiece, CELL5.printPiece, CELL6.printPiece, CELL7.printPiece);
	printf("  +---+---+---+---+---+---+---+---+n");
	printf("    a   b   c   d   e   f   g   h\n");
}

void handleInput(char *argv[]){
	
}
