#include "SDL2/SDL.h"
#include "tnns.h"
#include <stdlib.h>//malloc
#include <math.h>//abs
#include "more/rngbrush.h"

//TODO: change rects into vects

SDL_Rect *generate_terrain(int *nb, float p,int offs){
unsigned int n =TERRAIN_WIDTH*TERRAIN_HEIGHT*p;
SDL_Rect *ter =(SDL_Rect*)malloc(sizeof(SDL_Rect)*n);
switch(offs){

case -1: // random
for (int i=0; i<n; i++)
ter[i] =(SDL_Rect){rn(WINDOW_WIDTH-SPRITE_SIZE),
	rn(WINDOW_HEIGHT-SPRITE_SIZE), SPRITE_SIZE,SPRITE_SIZE};
	break;

default: // on grid with an offset (or not)
int i1 =0,i2 =0;
for (int i=0; i<n; i++){
i1 =rn(SPRITES_WIDTH); i2 =rn(SPRITES_HEIGHT);
ter[i] =(SDL_Rect){SPRITE_SIZE*i1+i1 +rr(-(offs),offs),
	SPRITE_SIZE*i2+i2 +rr(-(offs),offs), SPRITE_SIZE,SPRITE_SIZE};}
	break;
//actual probabilities
//Perlin noise
//1-2 bushed a tile
//different sizes of bush
}

// sorting the array
// 1) deleting overlapping sprites
for (int i=0; i<n; i++)
	for (int j=i+1; j<n; j++)
		if (ter[j].x && abs(ter[i].x-ter[j].x) <5*ASPECT_RATIO
				&& abs(ter[i].y-ter[j].y) <5*ASPECT_RATIO)
			ter[j].w =0;
int m =0; for (int i=0; i<n; i++) if (ter[i].w) m++;
SDL_Rect *final_ter =(SDL_Rect*)malloc(sizeof(SDL_Rect)*m);
for (int i=0, j=m; i<n; i++){
	if (ter[i].w){ j--;
		final_ter[j] =ter[i];}}
// 2) ordering sprites for display


free(ter);
*nb =m;
return final_ter;}
