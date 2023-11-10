#include "rngbrush.h"
#include <stdlib.h>//srand
#include <time.h>//time (srand seed)

void	rng_init(void){
srand((unsigned int)time(NULL));
return;}

//random numbers
int	rn(int max){ //0 to max non inclusive
if (max ==0) return 0;
int n; //max++;
do { n =rand() /(RAND_MAX /max+1);
} while (n >max);
return n;}

int	rr(int min, int max){ //min to max inclusive
if (min ==max) return min;
int n;
if (min >max) {
	n =min;
	min =max;
	max =n; }
n =rn(max-min) +min;
return n;}

void	ryx(rect r, int *y,int *x){ //inclusive of boundaries
*y =rr(r.y,r.h);
*x =rr(r.x,r.w);
return;}
		//would work too
		//? vect{y,x} =vect
		//vect {&y &x structure
		//{y,x} ={1,2}
		//rect struct
	//rvect


//random characters
char	ra(void){
char c;
c =(char)rr((int)'a',(int)'z');
return c;}

char	ra1(void){
char c;
c =(char)rr((int)'0',(int)('9'+26));
if (c >'9') c +='a'-'9'-1;
return c;}
