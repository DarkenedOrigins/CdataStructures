#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  	int j;
	for( j=0;j<9;j++){
		if ( sudoku[i][j] == val){
			return 1;
		}
	}
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  	int i;
	for( i=0;i<9;i++){
		if ( sudoku[i][j] == val){
			return 1;
		}
	}

  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
	int I=(i/3)*3;
	int J=(j/3)*3;
	int a,b;
	for( a=0;a<3;a++){
		for( b=0;b<3;b++){
			if( sudoku[I+a][J+b] == val){
				return 1;
			}
		}
	}
   return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  	int a;
	a= is_val_in_row(val, i, sudoku) + is_val_in_col(val, j, sudoku) + is_val_in_3x3_zone(val, i, j, sudoku);
	if(a != 0) return 0;
  return 1;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  	int i,j,num;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if (sudoku[i][j]<=0 || sudoku[i][j]>9){
				goto LABEL;
			}
		}
	}
	if(i==9 && j==9) return 1;
	LABEL: 
	for(num=1;num<=9;num++){
		if( is_val_valid(num, i, j, sudoku) ){
			sudoku[i][j]=num;
			if(solve_sudoku(sudoku)){
				return 1;
			}
			sudoku[i][j] = 0;
		}
	}
  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





