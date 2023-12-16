#include "SDL2/SDL.h"
#include "tnns.h"
#include "more/struct1.h"//vect
#include <math.h>//abs

void get_offsets(vect camera, vect plpos, vect* up_left);
void fill_background_color(SDL_Renderer* renderer);
void draw_grid(SDL_Renderer* renderer, vect camera);
void draw_bushes(SDL_Renderer* renderer, Ctxt_map* mc, Ctxt_disp* dc,
		vect up_right);
void draw_character(SDL_Renderer* renderer, vect up_left, vect plpos,
		int facing, SDL_Texture* t_char);



void draw(SDL_Renderer* renderer, Ctxt_disp* dc, Ctxt_map* mc, Ctxt_game* gc){
vect up_left; get_offsets(dc->camera, gc->plpos, &up_left);
fill_background_color(renderer);
//if (dc->grid_on) draw_grid(renderer, dc->camera);
draw_bushes(renderer, mc, dc, up_left);
draw_character(renderer, up_left, gc->plpos, gc->facing, dc->t_char);
return;}



void get_offsets(vect camera, vect plpos,
		vect* up_left){
int x =plpos.x+camera.x-(WINDOW_WIDTH-16*ASPECT_RATIO)/2;
int y =plpos.y+camera.y-(WINDOW_HEIGHT-24*ASPECT_RATIO)/2;
if (x<-TERRAIN_BORDER) x =-TERRAIN_BORDER;
else if (x+WINDOW_WIDTH>TERRAIN_WIDTH+TERRAIN_BORDER)
	x =TERRAIN_WIDTH+TERRAIN_BORDER-WINDOW_WIDTH;
if (y<-TERRAIN_BORDER) y =-TERRAIN_BORDER;
else if (y+WINDOW_HEIGHT>TERRAIN_HEIGHT+TERRAIN_BORDER)
	y =TERRAIN_HEIGHT+TERRAIN_BORDER-WINDOW_HEIGHT;
*up_left =(vect){x,y};	return;}

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

void draw_bushes(SDL_Renderer* renderer, Ctxt_map* mc, Ctxt_disp* dc,
			vect up_right){
//vect		camera =dc->camera;
  int		nt =mc->nt;
  vect*		t_sprite_v =mc->t_sprite_v;
for (int i=0; i<nt; i++)
	if (t_sprite_v[i].x <up_right.x+WINDOW_WIDTH
		&& t_sprite_v[i].x >=up_right.x-SPRITE_SIZE
		&& t_sprite_v[i].y <up_right.y+WINDOW_HEIGHT
		&& t_sprite_v[i].y >=up_right.y-SPRITE_SIZE){
	SDL_Rect draw_r =(SDL_Rect){t_sprite_v[i].x -up_right.x,
				t_sprite_v[i].y -up_right.y,
				SPRITE_SIZE,SPRITE_SIZE};
	SDL_RenderCopy(renderer, dc->t_sprite, NULL, &draw_r);}
return;}

void draw_character(SDL_Renderer* renderer, vect up_left, vect plpos,
		int facing, SDL_Texture* t_char){
SDL_Rect r_sprite =(SDL_Rect){facing*16,0,16,24};
SDL_Rect r_char =(SDL_Rect){	plpos.x-up_left.x,
				plpos.y-up_left.y,
			16*ASPECT_RATIO,24*ASPECT_RATIO};
SDL_RenderCopy(renderer, t_char, &r_sprite, &r_char);	return;}
