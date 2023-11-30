#include "SDL2/SDL.h"
#include "tnns.h"
#include "more/struct1.h"
#include <math.h>//abs

//- fix the camera
	//field of view
//- position & distances are also scaled to the zoom
void draw(SDL_Renderer* renderer, Var *var, vect camera, SDL_Texture* t_char,
		int nt, SDL_Texture* t_sprite, vect* t_sprite_v){
SDL_SetRenderDrawColor(renderer, BG_R,BG_G,BG_B, 0xFF);
SDL_RenderClear(renderer);
for (int i=0; i<nt; i++)
	if (t_sprite_v[i].x <camera.x+WINDOW_WIDTH
		&& t_sprite_v[i].x >=camera.x-SPRITE_SIZE
		&& t_sprite_v[i].y <camera.y+WINDOW_HEIGHT
		&& t_sprite_v[i].y >=camera.y-SPRITE_SIZE){
	SDL_Rect draw_r =(SDL_Rect){t_sprite_v[i].x -camera.x,
				t_sprite_v[i].y -camera.y,
				SPRITE_SIZE,SPRITE_SIZE};
	SDL_RenderCopy(renderer, t_sprite, NULL, &draw_r);}
//vect plpos =(vect){SPRITE_SIZE*9+8,SPRITE_SIZE*5+4+8*ASPECT_RATIO};
//vect pos_char =(vect){(WINDOW_WIDTH-(16*ASPECT_RATIO))/2,
//		(WINDOW_HEIGHT-(24*ASPECT_RATIO)/2};
//SDL_Rect r_char =(SDL_Rect){plpos.x,plpos.y,16*ASPECT_RATIO,24*ASPECT_RATIO};
SDL_Rect r_char =(SDL_Rect){(WINDOW_WIDTH-(16*ASPECT_RATIO))/2,
		(WINDOW_HEIGHT-(24*ASPECT_RATIO))/2,
		 16*ASPECT_RATIO,24*ASPECT_RATIO};
SDL_RenderCopy(renderer, t_char, NULL, &r_char);
	return;}


//TODO: delete this function
void zoom_rects(int zoom, SDL_Rect *r_char, int nt, SDL_Rect* t_sprite_r){
r_char->w =16*zoom; r_char->h =24*zoom;
for (int i=0; i<nt; i++){
	t_sprite_r[i].w =SPRITE_BASE*zoom;
	t_sprite_r[i].h =SPRITE_BASE*zoom;}
return;}

//TODO: make camera have absolute coordinates
void draw_grid(SDL_Renderer* renderer, vect camera){
SDL_SetRenderDrawColor(renderer, GRID_R,GRID_G,GRID_B,GRID_A);
for (int x=0; x<WINDOW_WIDTH; x+=SPRITE_SIZE+1){
	int xx =x +camera.x%SPRITE_SIZE;
	SDL_RenderDrawLine(renderer, xx,0, xx,WINDOW_HEIGHT-1);}
for (int y=0; y<WINDOW_HEIGHT; y+=SPRITE_SIZE+1){
	int yy =y +camera.y%SPRITE_SIZE;
	SDL_RenderDrawLine(renderer, 0,yy, WINDOW_WIDTH-1,yy);}
return;}
/*
void draw_grid_old(SDL_Renderer* renderer, vect camera, SDL_Texture* t_grid){
int x,y;
if (camera.x>0) x= -(camera.x %(SPRITE_SIZE+2));
else		x= -(SPRITE_SIZE+2 +camera.x%(SPRITE_SIZE+2));
if (camera.y>0) y= -(camera.y %(SPRITE_SIZE+2));
else		y= -(SPRITE_SIZE+2 +camera.y%(SPRITE_SIZE+2));
SDL_Rect t_grid_r =(SDL_Rect){x,y, T_GRID_W,T_GRID_H};
SDL_RenderCopy(renderer, t_grid, NULL, &t_grid_r);
	return;}
*/
