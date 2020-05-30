int out_of_bounds(int r, int c, int boardRowSize, int boardColSize);//this is to use the out of bounds function in the count function
/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
	// Check boundary conditions as we go!
  	int neighbors=0;
	int r, c;
	
	for(r=-1;r<=1;r++){
  		for(c=-1;c<=1;c++){
  			if (!out_of_bounds(row+r, col+c, boardRowSize, boardColSize) && !(r==0 && c==0 ) ){		
			neighbors += board[(r+row)*boardColSize+(c+col)];
			}
		}
 	}
	return neighbors;
}


int out_of_bounds(int r, int c, int boardRowSize, int boardColSize){
	// Helper function to check if r and c are in bounds
	// returns 1 if they are out of bounds, 0 otherwise
	if ( (r<0 || r>boardRowSize-1) || (c<0 || c>boardColSize-1) ){
		return 1;
	} else {
		return 0;
	}
}




/*
 * Update the game board to the next step.
 * Input:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */

// https://wiki.illinois.edu/wiki/display/ece220/SP17+MP6+-+Game+Of+Life
//Any live cell with fewer than two live neighbours dies, as if caused by under-population.
//Any live cell with two or three live neighbours lives on to the next generation.
//Any live cell with more than three live neighbours dies, as if by over-population.
//Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

void updateBoard(int* board, int boardRowSize, int boardColSize) {
	//Make a copy of the board element wise
	int max = boardRowSize*boardColSize;
	int boardCopy[max];
	for (int i=0; i<max; i++){
		boardCopy[i] = board[i];
	}
  	// Now we can modify the original board by looking at the copy.
	int count;
	for (int i=0; i<boardRowSize; i++){
		for (int j=0; j<boardColSize; j++){
			count = countLiveNeighbor(boardCopy, boardRowSize, boardColSize, i, j);
			if (count<2 || count>3){
				board[i*boardColSize+j] = 0; 
			} else if (count==3){
				board[i*boardColSize+j] = 1;
			}
		}
	}
  
}



/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */
int aliveStable(int* board, int boardRowSize, int boardColSize){
  	// Now we can modify the original board by looking at the copy.
	int count;
	for (int i=0; i<boardRowSize; i++){
		for (int j=0; j<boardColSize; j++){
			count = countLiveNeighbor(board, boardRowSize, boardColSize, i, j);
			if (count<2 || count>3){
				if (board[i*boardColSize+j] != 0)
					return 0; 
			} else if (count==3){
				if (board[i*boardColSize+j] != 1)
					return 0;
			}
		}
	}
	return 1;
}
