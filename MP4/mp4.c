#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double abs_double(double y)
{
    //Change this to return the absolute value of y i.e |y|
	y=y*y;
	y=sqrt(y);	//|y|=sqrt(y^2)
	return y;
}

double fx_val(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the value of the polynomial at the value x
	double f;
	f= a*pow(x,4)+b*pow(x,3)+c*pow(x,2)+d*x+e; //this just does the poly 
    return f;
}

double fx_dval(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the value of the derivative of the polynomial at the value x
    	double f;
	f=4*a*pow(x,3)+3*b*pow(x,2)+2*c*x+d; //computes derivitive
	return f;
}

double fx_ddval(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the value of the double derivative of the polynomial at the value x
	double f;
	f=12*a*pow(x,2)+6*b*x+2*c; //computes second derivitive
    return f;
}


double newrfind_halley(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the root found starting from the initial point x using Halley's method
	double f,g,h,j,k; //initializes values
	f=fx_val(a,b,c,d,e,x);
	if (f==0){
		printf("Root found: %f\n",x);	//checks if at the initial x there is a zero
		return 1;
	}
	while (f!=0 && j<10000){
		f= fx_val(a,b,c,d,e,x);
		g= fx_dval(a,b,c,d,e,x);	//computes the function and its derivitives 
		h= fx_ddval(a,b,c,d,e,x);
		k=x;
		x=x-( ( 2*f*g  ) / ( (g*g)*2-f*h  ) );	//calculates the next x 

		if(x-k <= 0.000001 && x-k>=0 || k-x <= 0.000001 && k-x >= 0 ) {
			printf("Root found: %f \n",x); //checks if consecutive x's are very close together this means root convergence
    			return 1;	//returns 1 if a root is found
		}

		f=fx_val(a,b,c,d,e,x);
		j++;	//j checks for how many times the loop has run
	}
	if (j==10000){
		return 0;	//if the loop exited due to j then root has not been found an a zero is returned
	}
		printf("Root found: %f \n",x);
    return 1;
}

int rootbound(double a, double b, double c, double d, double e, double r, double l)
{
    //Change this to return the upper bound on the number of roots of the polynomial in the interval (l, r)

	double q,w,t,y,i,j;
	q=4*a*l+b;
	w=6*l*l*a+3*b*l+c;		//this block just gets the coifficents and the first coifficent is A
	t=4*a*l*l*l+3*b*l*l+2*c*l+d;
	y=a*pow(l,4)+b*l*l*l+c*l*l+d*l+e;


	i=0;

	if ( q>0 && a<0 || a>0 && q<0  ) 
		i++;
	if ( q>0 && w<0 || w>0 && q<0  )
		i++;
	if (w>0 && t<0 || t>0 && w<0 )			//this block checks for sign changes and counts them in i
		i++;
	if (t>0 && y<0 || y>0 && t<0 )
		i ++;
	if (t>0 && y<0 || y>0 && t<0 )
		i ++;

	q=4*a*r+b;
	w=6*r*r*a+3*b*l+c;
	t=4*a*r*r*r+3*b*r*r+2*c*r+d;			//this block gets the coifficents for R and first coif is A
	y=a*pow(r,4)+b*r*r*r+c*r*r+d*l+e;
	j=0;


	if ( q>0 && a<0 || a>0 && q<0  )
		j++;
	if ( q>0 && w<0 || w>0 && q<0  )
		j++;
	if (w>0 && t<0 || t>0 && w<0 )			//this checks sign changes 
		j++;
	if (t>0 && y<0 || y>0 && t<0 )
		j++;
	if (t>0 && y<0 || y>0 && t<0 )
		j++;


	return abs_double(i-j);	//does the sign change minus and takes the absolute value of it
}

int main(int argc, char **argv)
{
	double a, b, c, d, e, l, r;
	FILE *in;

	if (argv[1] == NULL) {
		printf("You need an input file.\n");
		return -1;
	}
	in = fopen(argv[1], "r");
	if (in == NULL)
		return -1;
	fscanf(in, "%lf", &a);
	fscanf(in, "%lf", &b);
	fscanf(in, "%lf", &c);
	fscanf(in, "%lf", &d);
	fscanf(in, "%lf", &e);
	fscanf(in, "%lf", &l);
	fscanf(in, "%lf", &r);


    //The values are read into the variable a, b, c, d, e, l and r.
    //You have to find the bound on the number of roots using rootbound function.
    //If it is > 0 try to find the roots using newrfind function.
    //You may use the fval, fdval and fddval funtions accordingly in implementing the halleys's method.

	int i;
	double x;
	i=rootbound(a,b,c,d,e,r,l); //checks how many roots there are in the interval
	if (i==0){
		printf("The polynomial has no roots in the given interval.\n");
		return 0;//if there are no roots prints that ^
	}
//this for loop goes over the given interval searching for roots using the healy method
	for (x=l;x<=r;x=x+0.5){
		i=newrfind_halley(a,b,c,d,e,x);  //returns zero if no root is found
		if (i==0){
			printf("No roots found.\n");
		}	//prints that ^ if no root is found
	}



    fclose(in);

    return 0;
}
