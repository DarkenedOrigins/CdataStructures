//my program does not use the choose function since the factorial values get too big
//instead i use a method that uses the previous term and multiplies it 
//this is basically a decomposion of the choose function 
//since the first term is 1 and then the next is the row number
//u can multiply the previous term by (n-k+1)/k 
//where n is the row number 
//k is the positin in the row starting with zero 
//thats why u must start with 1 and compute the second term and onward 
//in my program 1<=k<=n
//i didnt directly use row_index because its too long to type
//i=k
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int row_index;

  printf("Enter the row index : ");
  scanf("%d",&row_index);

  // Your code starts from here
int n,count,i;//initialize interger values b count and i
n=row_index;	//set n equal to row_index
count=n;	//set count equal to n and thereby row index
unsigned long sum=1;	//make a unsigned long sum and have it equal 1
printf("1 ");	//print 1 since every row starts with one
for (i=1; i <= count; i++){	//this loops n number of time since a row has n+1 values and we already printed 1
				//k is position in row and n is row number
	sum = (sum * n)/i;	//the next value in a row is the previous value times (n-(k-1))/k where k starts at zero
				//this is why we started after 1 since we cant divide by zero so we start k at 1
				//  then we print the value 
	printf("%lu ",sum);
	n--; 	//decrement n since we are doing this consecutivly its like u reduce n as u increase i

	}

printf("\n");	//this is so the row is on its own line 



  return 0;
}
