#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "piece.h"
#include "cell.h"
#include "defs.h"
#include "errors.h"
#include "board.h"

/*The tentative source code for the Rook piece, currently without the Advanced Technique (Castling).
The rook's number of moves is currently still a WIP, as this code still counts the NULL cells
that are past a piece in the Rook's path. Need to find a easy fix.*/
case Rook:
    {
        int fwd, rght, lft = 0;
        int frontchk,frontchk2,frontchk3,frontchk4,frontchk5,frontchk6,frontchk7, = -1;
        int leftchk,leftchk2,leftchk3,leftchk4,leftchk5,leftchk6,leftchk7, = -1;
        int rightchk,rightchk2,rightchk3,rightchk4,rightchk5,rightchk6,rightchk7 = -1;
        if (p->player == white)
        {
            /*the available moves for a Rook, not including edge detection.*/
            cell *front = getCell((p->loc->cellID)+8, p->loc->board);
            cell *front2 = getCell((p->loc->cellID)+16, p->loc->board);
            cell *front3 = getCell((p->loc->cellID)+24, p->loc->board);
            cell *front4 = getCell((p->loc->cellID)+32, p->loc->board);
            cell *front5 = getCell((p->loc->CellID)+40, p->loc->board);
            cell *front6 = getCell((p->loc->cellID)+48, p->loc->board);
            cell *front7 = getCell((p->loc->cellID)+56, p->loc->board);
            cell *right = getCell((p->loc->cellID)+1, p->loc->board);
            cell *right2 = getCell((p->loc->cellID)+2, p->loc->board);
            cell *right3 = getCell((p->loc->cellID)+3, p->loc->board);
            cell *right4 = getCell((p->loc->cellID)+4, p->loc->board);
            cell *right5 = getCell((p->loc->cellID)+5, p->loc->board);
            cell *right6 = getCell((p->loc->cellID)+6, p->loc->board);
            cell *right7 = getCell((p->loc->cellID)+7, p->loc->board);
            cell *left = getCell((p->loc->cellID)-1, p->loc->board);
            cell *left2 = getCell((p->loc->cellID)-2, p->loc->board);
            cell *left3 = getCell((p->loc->cellID)-3, p->loc->board);
            cell *left4 = getCell((p->loc->cellID)-4, p->loc->board);
            cell *left5 = getCell((p->loc->cellID)-5, p->loc->board);
            cell *left6 = getCell((p->loc->cellID)-6, p->loc->board);
            cell *left7 = getCell((p->loc->cellID)-7, p->loc->board);

            /*basic forward movement of Rook*/
            if (front->piece == NULL)
            {
                fwd++;
                frontchk = front->cellID;
            }
            if (front2->piece == NULL)
            {
                fwd++;
                frontchk2 = front2->cellID;
            }
            if (front3->piece == NULL)
            {
                fwd++;
                frontchk3 = front3->cellID;
            }
            if (front4->piece == NULL)
            {
                fwd++;
                frontchk4 = front4->cellID;
            }
            if (front5->piece == NULL)
            {
                fwd++;
                frontchk5 = front5->cellID;
            }
            if (front6->piece == NULL)
            {
                fwd++;
                frontchk6 = front6->cellID;
            }
            if (front7->piece == NULL)
            {
                fwd++;
                frontchk7 = front7->cellID;
            }

            /*basic right movement of the Rook*/
            if (right->piece == NULL)
            {
                rght++;
                rightchk = right->cellID;
            }
            if (right2->piece == NULL)
            {
                rght++;
                rightchk2 = right2->cellID;
            }
            if (right3->piece == NULL)
            {
                rght++;
                rightchk3 = right3->cellID;
            }
            if (right4->piece == NULL)
            {
                rght++;
                rightchk4 = right4->cellID;
            }
            if (right5->piece == NULL)
            {
                rght++;
                rightchk5 = right5->cellID;
            }
            if (right6->piece == NULL)
            {
                rght++;
                rightchk6 = right6->cellID;
            }
            if (right7->piece == NULL)
            {
                rght++;
                rightchk7 = right7->cellID;
            }

            /*basic left movement of the Rook*/
            if (left->piece == NULL)
            {
                lft++;
                leftchk = left->cellID;
            }
            if (left2->piece == NULL)
            {
                lft++;
                leftchk2 = left2->cellID;
            }
            if (left3->piece == NULL)
            {
                lft++;
                leftchk3 = left3->cellID;
            }
            if (left4->piece == NULL)
            {
                lft++;
                leftchk4 = left4->cellID;
            }
            if (left5->piece == NULL)
            {
                lft++;
                leftchk5 = left5->cellID;
            }
            if (left6->piece == NULL)
            {
                lft++;
                leftchk6 = left6->cellID;
            }
            if (left7->piece == NULL)
            {
                lft++;
                leftchk7 = left7->cellID;
            }

            /*when the rook is on the left edge*/
            if (front->cellID%8 == 0)
            {
                lft = 0;
            }

            /*when the rook is on the right edge*/
            if (front->cellID%8 == 7)
            {
                rght = 0;
            }

        }
        else
        {
            cell *front = getCell((p-> loc -> cellID)-8, p -> loc -> board);
            cell *front2 = getCell((p -> loc -> cellID)-16, p -> loc -> board);
            cell *front3 = getCell((p -> loc -> cellID)-24, p -> loc -> board);
            cell *front4 = getCell((p -> loc -> cellID)-32, p -> loc -> board);
            cell *front5 = getCell((p -> loc -> CellID)-40, p -> loc -> board);
            cell *front6 = getCell((p -> loc -> cellID)-48, p -> loc -> board);
            cell *front7 = getCell((p -> loc -> cellID)-56, p -> loc -> board);
            cell *right = getCell((p -> loc -> cellID)-1, p -> loc -> board);
            cell *right2 = getCell((p -> loc -> cellID)-2, p -> loc -> board);
            cell *right3 = getCell((p -> loc -> cellID)-3, p -> loc -> board);
            cell *right4 = getCell((p -> loc -> cellID)-4, p -> loc -> board);
            cell *right5 = getCell((p -> loc -> cellID)-5, p -> loc -> board);
            cell *right6 = getCell((p -> loc -> cellID)-6, p -> loc -> board);
            cell *right7 = getCell((p -> loc -> cellID)-7, p -> loc -> board);
            cell *left = getCell((p -> loc -> cellID)+1, p -> loc -> board);
            cell *left2 = getCell((p -> loc -> cellID)+2, p -> loc -> board);
            cell *left3 = getCell((p -> loc -> cellID)+3, p -> loc -> board);
            cell *left4 = getCell((p -> loc -> cellID)+4, p -> loc -> board);
            cell *left5 = getCell((p -> loc -> cellID)+5, p -> loc -> board);
            cell *left6 = getCell((p -> loc -> cellID)+6, p -> loc -> board);
            cell *left7 = getCell((p -> loc -> cellID)+7, p -> loc -> board);

            /*basic forward movement of Rook*/
            if (front->piece == NULL)
            {
                fwd++;
                frontchk = front->cellID;
            }
            if (front2->piece == NULL)
            {
                fwd++;
                frontchk2 = front2->cellID;
            }
            if (front3->piece == NULL)
            {
                fwd++;
                frontchk3 = front3->cellID;
            }
            if (front4->piece == NULL)
            {
                fwd++;
                frontchk4 = front4->cellID;
            }
            if (front5->piece == NULL)
            {
                fwd++;
                frontchk5 = front5->cellID;
            }
            if (front6->piece == NULL)
            {
                fwd++;
                frontchk6 = front6->cellID;
            }
            if (front7->piece == NULL)
            {
                fwd++;
                frontchk7 = front7->cellID;
            }

            /*basic right movement of the Rook*/
            if (right->piece == NULL)
            {
                rght++;
                rightchk = right->cellID;
            }
            if (right2->piece == NULL)
            {
                rght++;
                rightchk2 = right2->cellID;
            }
            if (right3->piece == NULL)
            {
                rght++;
                rightchk3 = right3->cellID;
            }
            if (right4->piece == NULL)
            {
                rght++;
                rightchk4 = right4->cellID;
            }
            if (right5->piece == NULL)
            {
                rght++;
                rightchk5 = right5->cellID;
            }
            if (right6->piece == NULL)
            {
                rght++;
                rightchk6 = right6->cellID;
            }
            if (right7->piece == NULL)
            {
                rght++;
                rightchk7 = right7->cellID;
            }

/*basic left movement of the Rook*/
            if (left->piece == NULL)
            {
                lft++;
                leftchk = left->cellID;
            }
            if (left2->piece == NULL)
            {
                lft++;
                leftchk2 = left2->cellID;
            }
            if (left3->piece == NULL)
            {
                lft++;
                leftchk3 = left3->cellID;
            }
            if (left4->piece == NULL)
            {
                lft++;
                leftchk4 = left4->cellID;
            }
            if (left5->piece == NULL)
            {
                lft++;
                leftchk5 = left5->cellID;
            }
            if (left6->piece == NULL)
            {
                lft++;
                leftchk6 = left6->cellID;
            }
            if (left7->piece == NULL)
            {
                lft++;
                leftchk7 = left7->cellID;
            }

            /*when the rook is on the left edge*/
            if (front->cellID%8 == 7)
            {
                lft = 0;
            }

            /*when the rook is on the right edge*/
            if (front->cellID%8 == 0)
            {
                rght = 0;
            }

        }

        /*adding all the # of available moves for the rook*/
        num = fwd + rght + lft;
        /* if no available moves, print error and return null*/
        if (num==0)
        {
            printp(available, p);
            return NULL;
        }
    }
    return NULL;
