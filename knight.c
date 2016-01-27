case knight:
{
	int num = 0;
	int fwd, back, left, right = 0;
	int frontchk, frontchk2, frontchk3, frontchk4 = -1; /* the "forward" movements */
	int backchk, backchk2, backchk3, backchk4 = -1; /* the "back" movements */
	int movecapturechk = -1 // knight can capture (?) 
	
	if(p->player == white){
		/* available moves for the knight, not including edge detection */
		cell *front  = getCell((p->loc->cellID)+6, p->loc->board);
		cell *front2 = getCell((p->loc->cellID)+10, p->loc->board);
		cell *front3 = getCell((p->loc->cellID)+15, p->loc->board);
		cell *front4 = getCell((p->loc->cellID)+17, p->loc->board);
		
		cell *back  = getCell((p->loc->cellID)-6, p->loc->board);
		cell *back2 = getCell((p->loc->cellID)-10, p->loc->board);
		cell *back3 = getCell((p->loc->cellID)-15, p->loc->board);
		cell *back4 = getCell((p->loc->cellID)-17, p->loc->board);
		
		/*basic "forward" movement of Knight */
		if(front->piece == NULL){
			fwd++;
			frontchk = front->cellID;
		}
		if(front2->piece == NULL){
			fwd++;
			frontchk2 = front2->cellID;
		}
		if(front3->piece == NULL){
			fwd++;
			frontchk3 = front3->cellID;
		}
		if(front4->piece == NULL){
			fwd++;
			frontchk4 = front4->cellID;
		}
		
		/*basic "back" movement of Knight*/
		if(back->piece == NULL){
			back++;
			backchk = back->cellID;
		}
		if(back2->piece == NULL){
			back++;
			backchk2 = back2->cellID;
		}
		if(back3->piece == NULL){
			back++;
			backchk3 = back3->cellID;
		}
		if(back4->piece == NULL){
			back++
			backchk4 = back4->cellID;
		}
		
		/*when the Knight is on the left edge*/
		if(front->cellID%8 == 0){
			left = 0;
		}
		
		/*when the Knight is on the right edge*/
		if(front->cellID&8 = 7){
			right = 0;
		}		
	}
	else{
		cell *front  = getCell((p->loc->cellID)-6, p->loc->board);
		cell *front2 = getCell((p->loc->cellID)-10, p->loc->board);
		cell *front3 = getCell((p->loc->cellID)-15, p->loc->board);
		cell *front4 = getCell((p->loc->cellID)-17, p->loc->board);
		
		cell *back  = getCell((p->loc->cellID)+6, p->loc->board);
		cell *back2 = getCell((p->loc->cellID)+10, p->loc->board);
		cell *back3 = getCell((p->loc->cellID)+15, p->loc->board);
		cell *back4 = getCell((p->loc->cellID)+17, p->loc->board);		
		
		/*basic "forward" movement of Knight */
		if(front->piece == NULL){
			fwd++;
			frontchk = front->cellID;
		}
		if(front2->piece == NULL){
			fwd++;
			frontchk2 = front2->cellID;
		}
		if(front3->piece == NULL){
			fwd++;
			frontchk3 = front3->cellID;
		}
		if(front4->piece == NULL){
			fwd++;
			frontchk4 = front4->cellID;
		}
		
		/*basic "back" movement of Knight*/
		if(back->piece == NULL){
			back++;
			backchk = back->cellID;
		}
		if(back2->piece == NULL){
			back++;
			backchk2 = back2->cellID;
		}
		if(back3->piece == NULL){
			back++;
			backchk3 = back3->cellID;
		}
		if(back4->piece == NULL){
			back++
			backchk4 = back4->cellID;
		}
		
		/*when the Knight is on the left edge*/
		if(front->cellID%8 == 7){
			left = 0;
		}
		
		/*when the Knight is on the right edge*/
		if(front->cellID%8 == 0){
			right = 0;
		}
	}
	
	/*add all possible moves for Knight*/
	num = fwd + back;
	
	/*if no possible moves, print error and return NULL*/
	if(num==0){
		printp(available, p);
		return NULL;
	}
}	
	return NULL;
	
	// Assume knight is at a position. All possible moves (assuming still in board) would be:
	// currentPos + 6, currentPos - 6, currentPos + 10, currentPos - 10, currentPos + 15, currentPos - 15, currentPos + 17, currentPos - 17
		
	// implement a way to check if the space which the knight moves is still in the board or not
		


	
