#include "sparsemat.h"
#include <stdio.h>
#include <stdlib.h>


sp_tuples * load_tuples(char* input_file)
{
    FILE *fp;
    int rows, columns, row, col, ret;
    double val;
    int nz = 0;
    char str[1000];
    fp = fopen(input_file , "r");
    sp_tuples *tuple_setup=(sp_tuples*) malloc(sizeof(sp_tuples));
    fgets(str, 1000, fp);
    int read = sscanf(str, "%d %d", &rows, &columns);
    if (read != 2){
      fclose(fp);
      return NULL;
    }
    tuple_setup->m = rows;
    tuple_setup->n = columns;
    tuple_setup->tuples_head = NULL;

    while (1){
        ret = fscanf(fp, "%d %d %lf", &row, &col, &val);
        if (ret != 3) break;
        // printf("data:%d %d %lf\n", row, col, val);
        set_tuples(tuple_setup, row, col, val);
    }

    sp_tuples_node *node = tuple_setup->tuples_head;
    while (node != NULL){
        nz+=1;
        node = node->next;
    }

    tuple_setup->nz = nz;
    fclose(fp);
    return tuple_setup;
    return NULL;
}

double gv_tuples(sp_tuples * mat_t,int row,int col)
//this function return -1 if coordinates given are out of bounds, zero if it isnt in the link list but if it is it returns the value;
{
	if ( row<0 || row>mat_t->m || col<0 || col> mat_t->n) return -1;
	sp_tuples_node *current = mat_t->tuples_head;
	while (current != NULL){
		if(current->row==row && current->col == col) return current->value;
		if(current->row > row && current->col > col)return 0;
		current=current->next;
	}
	return 0;
}

void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    sp_tuples_node *node = mat_t->tuples_head;
    sp_tuples_node *prev_node = NULL;
    sp_tuples_node *new_node = NULL;

    if (value != 0.0) {
      //Create node for inserting
      new_node = (sp_tuples_node*) malloc(1*sizeof(sp_tuples_node));
      new_node->value = value;
      new_node->row = row;
      new_node->col = col;
    }

    if (node == NULL) {
        //Empty list
        new_node->next = NULL;
        mat_t->tuples_head = new_node;
        return;
    }

    while (node != NULL) {
        if (node->row == row && node->col == col){
            //Node already exists
            if (value == 0.0){
                //Delete node
                if (prev_node != NULL) {
                    prev_node->next = node->next;
                } else {
                    mat_t->tuples_head = node->next;
                }
                free(node);
                return;
            } else {
                //Node needs to be updated
                node->value = value;
                return;
            }
        }

        if ( (node->row > row) || (node->row == row && node->col > col) ) {
            //Insert new_node
            if (value != 0.0) {
              new_node->next = node;
              if (prev_node == NULL){
                  //Deal with insertion at head
                  mat_t->tuples_head = new_node;
              } else {
                  prev_node->next = new_node;
              }
              return;
            }
        }

        prev_node = node;
        node = node->next;
    }

    //Insert at tail
    if (value != 0.0) {
      prev_node->next = new_node;
      new_node->next = NULL;
    }
    return;
}

void save_tuples(char * file_name, sp_tuples * mat_t)
{
  FILE *fp;
  fp = fopen(file_name, "w");
  sp_tuples_node *node = mat_t->tuples_head;
  fprintf(fp, "%d %d\n", mat_t->m, mat_t->n);
  while (node != NULL){
      fprintf(fp, "%d %d %lf\n", node->row, node->col, node->value);
      node = node->next;
  }
  fclose(fp);
	return;
}

sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB)
{
	if(matA->m != matB->m || matA->n != matB->n ) return NULL;
	sp_tuples_node *CurrentNode;
	CurrentNode = matA->tuples_head;
	sp_tuples *matC = malloc(sizeof(sp_tuples)*1);
	matC->m = matA->m;
	matC->n=matA->n;
	matC->tuples_head=NULL;
	double val;
	while( CurrentNode != NULL){
		set_tuples(matC, CurrentNode->row, CurrentNode->col, CurrentNode->value);
		CurrentNode=CurrentNode->next;
	}
	CurrentNode=matB->tuples_head;
	while( CurrentNode != NULL ){
		val = CurrentNode->value + gv_tuples(matC,CurrentNode->row,CurrentNode->col);
		set_tuples(matC, CurrentNode->row, CurrentNode->col, val);
		CurrentNode = CurrentNode->next;
	}
	CurrentNode=matC->tuples_head;
	int count=0;
	while(CurrentNode != NULL ){
		count++;
		CurrentNode=CurrentNode->next;
	}
	matC->nz=count;
	return matC;
}

sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB)
{
	if( matA->n != matB->m)return NULL; //checks if mat is valid input
	sp_tuples_node *MatrixA_Node, *MatrixB_Node, *MatC_Node;
	MatrixA_Node=matA->tuples_head;
	MatrixB_Node = matB->tuples_head;
	sp_tuples *matC;
	matC=(sp_tuples*)malloc(sizeof(sp_tuples)*1);//creats matrix C
	matC->m = matA->m;
	matC->n = matB->n;
	matC->tuples_head = NULL;
	int rowA,colA,count=0;
	double val=0;
	while( MatrixA_Node != NULL){
		rowA=MatrixA_Node->row;
		colA=MatrixA_Node->col;
		while(MatrixB_Node != NULL ){
			if(MatrixB_Node->row == colA){
			val = gv_tuples(matC,rowA,MatrixB_Node->col) + MatrixB_Node->value * MatrixA_Node->value;
			set_tuples(matC,rowA,MatrixB_Node->col,val);
			}
			MatrixB_Node = MatrixB_Node->next;
		}
		MatrixA_Node = MatrixA_Node->next;
		MatrixB_Node=matB->tuples_head;
	}
	MatC_Node = matC->tuples_head;
	while( MatC_Node != NULL){
		count++;
		MatC_Node = MatC_Node->next;
	}
	matC->nz = count;
	return matC;
}

void destroy_tuples(sp_tuples * mat_t)
{
	sp_tuples_node *temp, *current;
	current = mat_t->tuples_head;
	while(current != NULL){
		temp = current->next;
		free(current);
		current=temp;
	}
	free(mat_t);
	return;
}
