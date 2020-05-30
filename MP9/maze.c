#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
/*	maze_t *maze;
	int i,j,width,height;
	FILE *in_file;
	in_file = fopen(fileName, "r");
	fscanf(in_file, "%d %d", &height, &width);
	maze->width = width;
	maze->height = height;
	//allocates memory in the heap for the 2d array
	maze->cells = malloc(height*sizeof(char));
	for (i=0;i<height;i++){
		maze->cells[i] = malloc(width*sizeof(char) );
	}
	//fill array with values
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			fscanf(in_file, "%c",&maze->cells[i][j]);
			if(maze->cells[i][j] == 'S'){
				maze->startRow = i;
				maze->startColumn = j;
			}
			if (maze->cells[i][j] == 'E'){
				maze->endRow=i;
				maze->endColumn=j;
			}
		}
	}
	fclose(in_file);
    return maze;*/
	char str[100];
    int i, j;
    FILE *fp;
    int rows, columns;
    fp = fopen(fileName , "r");
    maze_t *maze=(maze_t*) malloc(1*sizeof(maze_t));
    fgets(str, 100, fp);
    int read = sscanf(str, "%d%d", &rows, &columns);
	//printf("Started reading file\n");
    if (read != 2){
      //printf("%d\n", read);
      fclose(fp);
      return NULL;
    }
    maze->height = rows;
    maze->width = columns;
    //printf("rows:%d  columns:%d\n", rows, columns);

    char **cells;
    cells = (char **) malloc(rows*sizeof(char*));

    for (i=0; i<rows; i++){
      cells[i] = malloc(columns*sizeof(char));
      fgets(cells[i], 100, fp);
      //puts(cells[i]);
    }
   for(i=0;i<maze->height;i++){
		for(j=0;j<maze->width;j++){
			if(cells[i][j] == 'S'){
				maze->startRow = i;
				maze->startColumn = j;
			}
			if (cells[i][j] == 'E'){
				maze->endRow=i;
				maze->endColumn=j;
			}
		}
	}

    //printf("-----\n");
    maze->cells = cells;
    //printMaze(maze);
    fclose(fp);
    return maze;
}

/* destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
	int i;
	for(i=maze->height-1;i>=0;i--){
		free(maze->cells[i]);
	}
	free(maze->cells);
	free(maze);
	
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    	int rows = maze->height;
	int cols = maze->width;
	int i,j;
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			printf("%c",maze->cells[i][j]);
		}
		printf("\n");
	}
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int first = 1;
int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
	if(maze->cells[row][col] == START && !first)return 0;
	first = 0;
	
	//check if this is with in bounds
    if( (col<0 || col>=maze->width) || (row<0 || row>=maze->height) ) return 0;
	//if at end return 1
	if(maze->cells[row][col] == 'E') return 1;
	//check if you are within a wall on previous visited
	if( (maze->cells[row][col] != ' ') && (maze->cells[row][col] != 'S') ) return 0;
	//mark current path
	if (maze->cells[row][col] != 'S') maze->cells[row][col]='.';
	//go left
	if(solveMazeManhattanDFS(maze,col-1,row)==1)return 1;
	//go right
	if(solveMazeManhattanDFS(maze,col+1,row)==1)return 1;
	//go down
	if(solveMazeManhattanDFS(maze,col,row+1)==1)return 1;
	//go up
	if(solveMazeManhattanDFS(maze,col,row-1)==1)return 1;
	if (maze->cells[row][col] != 'S')maze->cells[row][col]='~';
    return 0;
}
