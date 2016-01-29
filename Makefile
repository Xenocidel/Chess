#variables
DESIGN = Chess
LIBS = libErrors
CC     = gcc
CFLAGS = -ansi -Wall -c
LFLAGS = -Wall
AR     = ar rc
RANLIB = ranlib
DEBUG  = -g -DDEBUG

#targets
install: Chess
test: MovesTest
all: clean Chess ChessDebug MovesTest
clean:
	rm -f *.o *.a Chess ChessDebug MovesTest

#object files
main.o:
	$(CC) $(CFLAGS) main.c -o main.o

main_DEBUG.o:
	$(CC) $(CFLAGS) $(DEBUG) main.c -o main.o
	
errors.o:
	$(CC) $(CFLAGS) errors.c -o errors.o
	
piece.o:
	$(CC) $(CFLAGS) piece.c -o piece.o
	
piece_DEBUG.o:
	$(CC) $(CFLAGS) $(DEBUG) piece.c -o piece_DEBUG.o
	
cell.o:
	$(CC) $(CFLAGS) cell.c -o cell.o
	
cell_DEBUG.o:
	$(CC) $(CFLAGS) $(DEBUG) cell.c -o cell_DEBUG.o
	
board.o:
	$(CC) $(CFLAGS) board.c -o board.o
	
board_DEBUG.o:
	$(CC) $(CFLAGS) $(DEBUG) board.c -o board_DEBUG.o
	
moves_test.o:
	$(CC) $(CFLAGS) $(DEBUG) moves_test.c -o moves_test.o

gameDisplay.o:
	$(CC) $(CFLAGS) gameDisplay.c -o gameDisplay.o
	
gameDisplay_DEBUG.o:
	$(CC) $(CFLAGS) $(DEBUG) gameDisplay.c -o gameDisplay_DEBUG.o
	
#libraries
libChess.a: errors.o piece.o cell.o board.o gameDisplay.o
	$(AR) libChess.a errors.o piece.o cell.o board.o gameDisplay.o
	$(RANLIB) libChess.a
	
libChessDEBUG.a: errors.o piece_DEBUG.o cell_DEBUG.o board_DEBUG.o gameDisplay_DEBUG.o
	$(AR) libChessDEBUG.a errors.o piece_DEBUG.o cell_DEBUG.o board_DEBUG.o gameDisplay_DEBUG.o
	$(RANLIB) libChessDEBUG.a
	
#executables
Chess: main.o libChess.a
	$(CC) $(LFLAGS) main.o -lChess -L. -o Chess

ChessDebug: main_DEBUG.o libChessDEBUG.a
	$(CC) $(LFLAGS) $(DEBUG) main.o -lChessDEBUG -L. -o ChessDebug
	
MovesTest: moves_test.o libChessDEBUG.a
	$(CC) $(LFLAGS) $(DEBUG) moves_test.o -lChessDEBUG -L. -o MovesTest