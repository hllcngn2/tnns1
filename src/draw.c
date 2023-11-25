#include "SDL2/SDL.h"
#include "tnns.h"
#include "more/struct1.h"
#include <math.h>//abs

//TODO: draw using vects (generate rects on the fly)
//- fix the camera
	//field of view
//- position & distances are also scaled to the zoom
void draw(SDL_Renderer* renderer, Var *var, vect camera,
		SDL_Texture* t_char, SDL_Rect *r_char,
		int nt, SDL_Texture* t_sprite, vect* t_sprite_v){
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
SDL_RenderCopy(renderer, t_char, NULL, r_char);
	return;}
void draw_rects(SDL_Renderer* renderer, Var *var, vect camera,
		SDL_Texture* t_char, SDL_Rect *r_char,
		int nt, SDL_Texture* t_sprite, SDL_Rect* t_sprite_r){
SDL_RenderClear(renderer);
for (int i=0; i<nt; i++)
	if (t_sprite_r[i].x <camera.x+WINDOW_WIDTH
		&& t_sprite_r[i].x >=camera.x-SPRITE_SIZE
		&& t_sprite_r[i].y <camera.y+WINDOW_HEIGHT
		&& t_sprite_r[i].y >=camera.y-SPRITE_SIZE){
	SDL_Rect draw_r =t_sprite_r[i];
	draw_r.x -=camera.x;
	draw_r.y -=camera.y;
	SDL_RenderCopy(renderer, t_sprite, NULL, &draw_r);}
SDL_RenderCopy(renderer, t_char, NULL, r_char);
	return;}

//TODO: delete this function
void zoom_rects(int zoom, SDL_Rect *r_char, int nt, SDL_Rect* t_sprite_r){
r_char->w =16*zoom; r_char->h =24*zoom;
for (int i=0; i<nt; i++){
	t_sprite_r[i].w =SPRITE_BASE*zoom;
	t_sprite_r[i].h =SPRITE_BASE*zoom;}
return;}

void draw_grid(SDL_Renderer* renderer, vect camera, SDL_Texture* t_grid){
int x,y;
if (camera.x>0) x= -(camera.x %(SPRITE_SIZE+2));
else		x= -(SPRITE_SIZE+2 +camera.x%(SPRITE_SIZE+2));
if (camera.y>0) y= -(camera.y %(SPRITE_SIZE+2));
else		y= -(SPRITE_SIZE+2 +camera.y%(SPRITE_SIZE+2));
SDL_Rect t_grid_r =(SDL_Rect){x,y, T_GRID_W,T_GRID_H};
SDL_RenderCopy(renderer, t_grid, NULL, &t_grid_r);
	return;}
