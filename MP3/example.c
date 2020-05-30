#include <stdio.h>
int main(){
int x,c,i;
printf("enter number of rows of astricks u want\n");
scanf("%d",&i);
for (x=1;x<=i;x++){
	c=x;
	while (c>0){
		printf("*");
		c--;
	}
	printf("\n");
	//one last time 
}
printf("\n");
return 0;
}
