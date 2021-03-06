#variable
VPATH = ./src: ./inc: ./obj: ./test:
CFLAGS = -ansi -Wall -c
CC     = gcc
INCLUDE = -I inc
DESIGN = Chess
LIBS = libErrors
LFLAGS = -Wall
AR     = ar rc
RANLIB = ranlib
DEBUG  = -g -DDEBUG
BINDIR = bin

#source/header files
FILE_SOURCE := ai.c board.c cell.c errors.c gameDisplay.c main.c moves_test.c piece.c
HEADERS := ai.h board.h cell.h defs.h errors.h gameDisplay.h piece.h

FILE_OBJECTS := $(FILE_SOURCE:.c=.o)
#targets
install: $(BINDIR)/Chess
test: $(BINDIR)/MovesTest
headers: HEADERS
all: clean $(BINDIR)/Chess $(BINDIR)/MovesTest
clean:
	rm -f *.o *.a $(BINDIR)/Chess $(BINDIR)/MovesTest

#object files

main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c src/main.c

main_DEBUG.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(DEBUG) -c src/main.c
	
errors.o: errors.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c src/errors.c
	
piece.o: piece.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c src/piece.c

piece_DEBUG.o: piece.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(DEBUG) -c src/piece.c
	
cell.o: cell.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c src/cell.c
	
cell_DEBUG.o: cell.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(DEBUG) -c src/cell.c
	
board.o: board.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c src/board.c
	
board_DEBUG.o: board.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(DEBUG) -c src/board.c
	
moves_test.o: moves_test.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(DEBUG) -c test/moves_test.c

gameDisplay.o: gameDisplay.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c src/gameDisplay.c

gameDisplay_DEBUG.o: gameDisplay.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(DEBUG) -c src/gameDisplay.c
	
ai.o: ai.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c src/ai.c

ai_DEBUG.o: ai.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) $(DEBUG) -c src/ai.c
	
#libraries
libChess.a: errors.o piece.o cell.o board.o gameDisplay.o ai.o
	$(AR) libChess.a errors.o piece.o cell.o board.o gameDisplay.o ai.o
	$(RANLIB) libChess.a
	
#executables
$(BINDIR)/Chess: $(FILE_OBJECTS) main.o libChess.a
	$(CC) $(LFLAGS) $(INCLUDE) main.o -lChess -L. -o $(BINDIR)/Chess

$(BINDIR)/MovesTest: $(FILE_OBJECTS) moves_test.o libChess.a
	$(CC) $(LFLAGS) $(INCLUDE) $(DEBUG) moves_test.o -lChess -L. -o $(BINDIR)/MovesTest