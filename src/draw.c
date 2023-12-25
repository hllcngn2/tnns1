#include "SDL2/SDL.h"
#include "tnns.h"
#include "more/struct1.h"//vect
#include <math.h>//abs

vect get_camera_offset(vect camera, vect plpos);
void fill_background_color(SDL_Renderer* renderer);
void draw_grid(SDL_Renderer* renderer, vect up_left);
void draw_bushes(SDL_Renderer* renderer, Ctxt_map* mc, Ctxt_disp* dc,
		vect up_right);
void draw_character(SDL_Renderer* renderer, vect up_left, vect plpos,
		int facing, SDL_Texture* t_char);

// TODO use ASPECT RATIO only at the moment of drawing
// so implement zoom


void draw(SDL_Renderer* renderer, Ctxt_disp* dc, Ctxt_map* mc, Ctxt_game* gc){
fill_background_color(renderer);
vect up_left =get_camera_offset(dc->camera, gc->plpos);
if (dc->grid_on) draw_grid(renderer, up_left);
draw_bushes(renderer, mc, dc, up_left);
draw_character(renderer, up_left, gc->plpos, gc->facing, dc->t_char);
return;}



vect get_camera_offset(vect camera, vect plpos){
int x =plpos.x+camera.x-(WINDOW_WIDTH-16*ASPECT_RATIO)/2;
int y =plpos.y+camera.y-(WINDOW_HEIGHT-24*ASPECT_RATIO)/2;
if (x<-TERRAIN_BORDER) x=-TERRAIN_BORDER;
else if (x+WINDOW_WIDTH>TERRAIN_WIDTH+TERRAIN_BORDER)
	x =TERRAIN_WIDTH+TERRAIN_BORDER-WINDOW_WIDTH;
if (y<-TERRAIN_BORDER) y=-TERRAIN_BORDER;
else if (y+WINDOW_HEIGHT>TERRAIN_HEIGHT+TERRAIN_BORDER)
	y =TERRAIN_HEIGHT+TERRAIN_BORDER-WINDOW_HEIGHT;
return (vect){x,y};}


void fill_background_color(SDL_Renderer* renderer){
SDL_SetRenderDrawColor(renderer, BG_R,BG_G,BG_B, 0xFF);
SDL_RenderClear(renderer);	return;}


void draw_grid(SDL_Renderer* renderer, vect up_left){
{int x;		if (up_left.x<0) x=abs(up_left.x);	//V
		//else x=SPRITE_SIZE-(up_left.x%SPRITE_SIZE);	// ?
		else x=SPRITE_SIZE-8%SPRITE_SIZE;//BASE)*ASPECT_RATIO;	// ?
int beg;	if (up_left.y<0) beg=abs(up_left.y);	//V v
		else beg=0;
int end;	if (up_left.y+WINDOW_HEIGHT>TERRAIN_HEIGHT)
			end=TERRAIN_HEIGHT-up_left.y;
		else end=WINDOW_HEIGHT-1;		//V ^
SDL_SetRenderDrawColor(renderer, GRID_R,GRID_G,GRID_B,GRID_A);
for(; up_left.x+x<=TERRAIN_WIDTH && x<WINDOW_WIDTH;		// ?
		x+=SPRITE_SIZE)
	SDL_RenderDrawLine(renderer, x,beg, x,end);}	// V
/*
{int y;		if (up_left.y<0) y =abs(up_left.y);
		else y =SPRITE_SIZE-(up_left.y%SPRITE_SIZE);
int beg;	if (up_left.x<0) beg=abs(up_left.x);
		else beg=0;
int end;	if (up_left.x+WINDOW_WIDTH>TERRAIN_WIDTH)
			end=TERRAIN_WIDTH-up_left.x;
		else end=WINDOW_WIDTH-1;
for(; up_left.y+y<=TERRAIN_HEIGHT && y<WINDOW_HEIGHT;
		y+=SPRITE_SIZE)
	SDL_RenderDrawLine(renderer, beg,y, end,y);}
*/
	return;}


void draw_bushes(SDL_Renderer* renderer, Ctxt_map* mc, Ctxt_disp* dc,
			vect up_left){
  int		nt =mc->nt;
  vect*		t_sprite_v =mc->t_sprite_v;
for (int i=0; i<nt; i++)
	if (t_sprite_v[i].x <up_left.x+WINDOW_WIDTH
		&& t_sprite_v[i].x >=up_left.x-SPRITE_SIZE
		&& t_sprite_v[i].y <up_left.y+WINDOW_HEIGHT
		&& t_sprite_v[i].y >=up_left.y-SPRITE_SIZE){
	SDL_Rect draw_r =(SDL_Rect){t_sprite_v[i].x -up_left.x,
				t_sprite_v[i].y -up_left.y,
				SPRITE_SIZE,SPRITE_SIZE};
	SDL_RenderCopy(renderer, dc->t_sprite, NULL, &draw_r);}
	return;}


void draw_character(SDL_Renderer* renderer, vect up_left, vect plpos,
		int facing, SDL_Texture* t_char){
SDL_Rect r_sprite =(SDL_Rect){facing*16,0,16,24};
SDL_Rect r_char =(SDL_Rect){	plpos.x-up_left.x,
				plpos.y-up_left.y,
			16*ASPECT_RATIO,24*ASPECT_RATIO};
SDL_RenderCopy(renderer, t_char, &r_sprite, &r_char);
	return;}
