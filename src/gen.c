#include "tnns.h"

void generate_terrain(Ctxt_map* mc, Texture* textable, float p,int offs){
unsigned int n =SPRITES_WIDTH*SPRITES_HEIGHT*p;

vect* ter =malloc(sizeof(vect)*n);
int*  id  =malloc(sizeof(int)*n);
switch(offs){
case -1: // random
for (int i=0; i<n; i++){
	ter[i] =(vect){rand()%(TERRAIN_WIDTH-SPRITE_SIZE),
			rand()%(TERRAIN_HEIGHT-SPRITE_SIZE)};
	id[i] =rand()%2;}
	break;
default: // on the grid with an offset
for (int i=0; i<n; i++){
	int i1 =rand()%(SPRITES_WIDTH), i2 =rand()%(SPRITES_HEIGHT);
	ter[i] =(vect){SPRITE_SIZE*i1 +rand()%(offs*2)-offs,
		SPRITE_SIZE*i2 +rand()%(offs*2)-offs};
	id[i] =rand()%2;}
	break;}

// sorting the array
// 1) deleting overlapping sprites
for (int i=0; i<n; i++)
	for (int j=i+1; j<n; j++)
		if (abs(ter[i].x-ter[j].x) <5*ASPECT_RATIO
		&& abs(ter[i].y-ter[j].y) <5*ASPECT_RATIO)
			ter[j].x =-100;
int m =0; for (int i=0; i<n; i++) if (ter[i].x!=-100) m++;
vect* final_ter =malloc(sizeof(vect)*m);
int*  final_id  =malloc(sizeof(int)*m);
for (int i=0, j=m; i<n; i++){
	if (ter[i].x!=-100){ j--;
		final_ter[j] =ter[i];
		final_id[j]  =id[i];}}
// 2) ordering sprites for display


// creating instances
for (int i=0;i<m;i++)
	addinst(&(mc->instlist), &(textable[id[i]+1]),
			final_ter[i].x,final_ter[i].y);
free(ter);	free(id);
mc->nt =m;	return;}
