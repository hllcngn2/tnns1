#include "SDL2/SDL.h"
#include "tnns.h"
#include "more/struct1.h"//vect
#include <math.h>//abs

void fill_background_color(SDL_Renderer* renderer);
void draw_grid(SDL_Renderer* renderer, vect camera);
void draw_bushes(SDL_Renderer* renderer, vect camera,
		Ctxt_map* mc, Ctxt_disp* dc);
void draw_character(SDL_Renderer* renderer, int facing,
		SDL_Texture* t_char);



void draw(SDL_Renderer* renderer, Ctxt_disp* dc, Ctxt_map* mc, Ctxt_game* gc){
//get camera offsets
//camera = offset from plpos
//calculate upper left corner
//relative to terrain

fill_background_color(renderer);
if (dc->grid_on) draw_grid(renderer, gc->camera);
draw_bushes(renderer, gc->camera, mc, dc);
draw_character(renderer, gc->facing, dc->t_char);
return;}



void fill_background_color(SDL_Renderer* renderer){
SDL_SetRenderDrawColor(renderer, BG_R,BG_G,BG_B, 0xFF);
SDL_RenderClear(renderer);	return;}

void draw_grid(SDL_Renderer* renderer, vect camera){
{int x;		if (camera.x<0) x=abs(camera.x);
		else x=SPRITE_SIZE+1-camera.x%(SPRITE_SIZE+1);
int beg;	if (camera.y<0) beg=abs(camera.y);
		else beg=0;
int end;	if (camera.y+WINDOW_HEIGHT>TERRAIN_HEIGHT*(SPRITE_SIZE+1))
			end=TERRAIN_HEIGHT*(SPRITE_SIZE+1)-camera.y;
		else end=WINDOW_HEIGHT-1;
SDL_SetRenderDrawColor(renderer, GRID_R,GRID_G,GRID_B,GRID_A);
for(; camera.x+x<=TERRAIN_WIDTH*(SPRITE_SIZE+1) && x<WINDOW_WIDTH;
		x+=SPRITE_SIZE+1)
	SDL_RenderDrawLine(renderer, x,beg, x,end);}
{int y;		if (camera.y<0) y=abs(camera.y);
		else y=SPRITE_SIZE+1-camera.y%(SPRITE_SIZE+1);
int beg;	if (camera.x<0) beg=abs(camera.x);
		else beg=0;
int end;	if (camera.x+WINDOW_WIDTH>TERRAIN_WIDTH*(SPRITE_SIZE+1))
			end=TERRAIN_WIDTH*(SPRITE_SIZE+1)-camera.x;
		else end=WINDOW_WIDTH-1;
for(; camera.y+y<=TERRAIN_HEIGHT*(SPRITE_SIZE+1) && y<WINDOW_HEIGHT;
		y+=SPRITE_SIZE+1)
	SDL_RenderDrawLine(renderer, beg,y, end,y);}	return;}

void draw_bushes(SDL_Renderer* renderer, vect camera,
		Ctxt_map* mc, Ctxt_disp* dc){
  SDL_Texture*	t_sprite =dc->t_sprite;
  int		nt =mc->nt;
  vect*		t_sprite_v =mc->t_sprite_v;
for (int i=0; i<nt; i++)
	if (t_sprite_v[i].x <camera.x+WINDOW_WIDTH
		&& t_sprite_v[i].x >=camera.x-SPRITE_SIZE
		&& t_sprite_v[i].y <camera.y+WINDOW_HEIGHT
		&& t_sprite_v[i].y >=camera.y-SPRITE_SIZE){
	SDL_Rect draw_r =(SDL_Rect){t_sprite_v[i].x -camera.x,
				t_sprite_v[i].y -camera.y,
				SPRITE_SIZE,SPRITE_SIZE};
	SDL_RenderCopy(renderer, t_sprite, NULL, &draw_r);}
return;}

void draw_character(SDL_Renderer* renderer, int facing,
		SDL_Texture* t_char){
SDL_Rect r_sprite =(SDL_Rect){facing*16,0,16,24};
SDL_Rect r_char =(SDL_Rect){(WINDOW_WIDTH-(16*ASPECT_RATIO))/2,
		(WINDOW_HEIGHT-(24*ASPECT_RATIO))/2,
		 16*ASPECT_RATIO,24*ASPECT_RATIO};
SDL_RenderCopy(renderer, t_char, &r_sprite, &r_char);	return;}
