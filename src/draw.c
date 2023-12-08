#include "SDL2/SDL.h"
#include "tnns.h"
#include "more/struct1.h"//vect
#include <math.h>//abs

void draw(SDL_Renderer* renderer, Var *var, vect camera, SDL_Texture* t_char,
		int nt, SDL_Texture* t_sprite, vect* t_sprite_v){
//background color
SDL_SetRenderDrawColor(renderer, BG_R,BG_G,BG_B, 0xFF);
SDL_RenderClear(renderer);
//grid (if on)
if (var->grid_on) {
	SDL_SetRenderDrawColor(renderer, GRID_R,GRID_G,GRID_B,GRID_A);
	{int x;
		if (camera.x<0) x=abs(camera.x);
		else x=SPRITE_SIZE+1-camera.x%(SPRITE_SIZE+1);
	int beg;
		if (camera.y<0) beg=abs(camera.y);
		else beg=0;
	int end;
		if (camera.y+WINDOW_HEIGHT>TERRAIN_HEIGHT*(SPRITE_SIZE+1))
			end=TERRAIN_HEIGHT*(SPRITE_SIZE+1)-camera.y;
		else end=WINDOW_HEIGHT-1;
	for(; camera.x+x<=TERRAIN_WIDTH*(SPRITE_SIZE+1) && x<WINDOW_WIDTH;
			x+=SPRITE_SIZE+1)
		SDL_RenderDrawLine(renderer, x,beg, x,end);}
	{int y;
		if (camera.y<0) y=abs(camera.y);
		else y=SPRITE_SIZE+1-camera.y%(SPRITE_SIZE+1);
	int beg;
		if (camera.x<0) beg=abs(camera.x);
		else beg=0;
	int end;
		if (camera.x+WINDOW_WIDTH>TERRAIN_WIDTH*(SPRITE_SIZE+1))
			end=TERRAIN_WIDTH*(SPRITE_SIZE+1)-camera.x;
		else end=WINDOW_WIDTH-1;
	for(; camera.y+y<=TERRAIN_HEIGHT*(SPRITE_SIZE+1) && y<WINDOW_HEIGHT;
			y+=SPRITE_SIZE+1)
		SDL_RenderDrawLine(renderer, beg,y, end,y);}}
//bushes
for (int i=0; i<nt; i++)
	if (t_sprite_v[i].x <camera.x+WINDOW_WIDTH
		&& t_sprite_v[i].x >=camera.x-SPRITE_SIZE
		&& t_sprite_v[i].y <camera.y+WINDOW_HEIGHT
		&& t_sprite_v[i].y >=camera.y-SPRITE_SIZE){
	SDL_Rect draw_r =(SDL_Rect){t_sprite_v[i].x -camera.x,
				t_sprite_v[i].y -camera.y,
				SPRITE_SIZE,SPRITE_SIZE};
	SDL_RenderCopy(renderer, t_sprite, NULL, &draw_r);}
//character
SDL_Rect r_char =(SDL_Rect){(WINDOW_WIDTH-(16*ASPECT_RATIO))/2,
		(WINDOW_HEIGHT-(24*ASPECT_RATIO))/2,
		 16*ASPECT_RATIO,24*ASPECT_RATIO};
SDL_Rect r_sprite =(SDL_Rect){var->facing*16,0,16,24};
SDL_RenderCopy(renderer, t_char, &r_sprite, &r_char);
	return;}
