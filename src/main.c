#include <stdio.h>
#include <string.h>//strcmp
#include <stdlib.h>//malloc/free,atoi/f
#include "SDL2/SDL.h"
#include "tnns.h"
#include "more/struct1.h"
#include "more/rngbrush.h"

#ifdef main//avoid WinMain error
#undef main//on windows
#endif
int main(int ac, char **av) {
float p; int offs;
if (ac>1) p =atof(av[1]); else p =GEN_DEFAULT_P;
if (ac>2) offs =atoi(av[2]); else offs =GEN_DEFAULT_OFFS;
if (offs !=-1) offs *=ASPECT_RATIO;

rng_init();
SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_NOPARACHUTE);
SDL_Window *window =SDL_CreateWindow("tnns",
		SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
SDL_Renderer *renderer =SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

// loading grid
SDL_Texture *t_grid =SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, T_GRID_W, T_GRID_H);
SDL_SetTextureBlendMode(t_grid, SDL_BLENDMODE_BLEND);
SDL_SetRenderTarget(renderer, t_grid);
SDL_SetRenderDrawColor(renderer, GRID_R,GRID_G,GRID_B,GRID_A);
for (int x=SPRITE_SIZE; x<T_GRID_W; x+=SPRITE_SIZE+1)
	SDL_RenderDrawLine(renderer, x,0, x,T_GRID_H-1);
for (int y=SPRITE_SIZE; y<T_GRID_H; y+=SPRITE_SIZE+1)
	SDL_RenderDrawLine(renderer, 0,y, T_GRID_W-1,y);
int grid_on =0;
SDL_SetRenderTarget(renderer, NULL);

//TODO: remove rects
// loading sprites
SDL_Surface *s_char =SDL_LoadBMP("ass/char_16x24-front.bmp");
SDL_SetColorKey(s_char,SDL_TRUE,SDL_MapRGB(s_char->format,0x6F,0xFF,0x7F));
SDL_Texture *t_char =SDL_CreateTextureFromSurface(renderer, s_char);
SDL_FreeSurface(s_char);
vect plpos =(vect){SPRITE_SIZE*9+8,SPRITE_SIZE*5+4+8*ASPECT_RATIO};
SDL_Rect r_char =(SDL_Rect){plpos.x,plpos.y,16*ASPECT_RATIO,24*ASPECT_RATIO};
//
SDL_Surface *sprite1 =SDL_LoadBMP("ass/bush_16.bmp");
SDL_SetColorKey(sprite1,SDL_TRUE,SDL_MapRGB(sprite1->format,0x6F,0xFF,0x7F));
SDL_Texture *t_sprite1 =SDL_CreateTextureFromSurface(renderer, sprite1);
SDL_FreeSurface(sprite1);
int nb =0;
SDL_Rect *t_sprite_r =generate_terrain(&nb, p, offs);

Var var =(Var){ASPECT_RATIO,SPRITE_SIZE};
Keys keys =(Keys){0,0,0,0,0};
vect camera =(vect){0,0}; //must start on a tile edge for the grid to fit


SDL_SetRenderDrawColor(renderer, BG_R,BG_G,BG_B, 0xFF);
int terminate =0;
SDL_Event e;
while(!terminate){

// event handling
while(SDL_PollEvent(&e)){
if (e.type ==SDL_QUIT) terminate++;
if (e.type ==SDL_KEYDOWN) switch(e.key.keysym.sym){
case K_QUIT: terminate++;	break;
case K_GRID: grid_on =(!grid_on)?1:0;	break;
case K_UP:     keys.up =1;	break;
case K_LEFT:   keys.left =1;	break;
case K_DOWN:   keys.down =1;	break;
case K_RIGHT:  keys.right =1;	break;
case K_CAMERA: keys.camera =1;
//	if (!keys.camera){ keys.up =0; keys.left =0;
//		keys.down =0; keys.right =0;}
	break;
case K_ZOOMIN:	if (var.zoom>1){
		var.zoom--;
		zoom_rects(var.zoom, &r_char, nb, t_sprite_r);}	break;
case K_ZOOMOUT:	if (var.zoom<8){
		var.zoom++;
		zoom_rects(var.zoom, &r_char, nb, t_sprite_r);}	break;
default:	break;}
if (e.type ==SDL_KEYUP) switch(e.key.keysym.sym){
case K_UP:     keys.up =0;	break;
case K_LEFT:   keys.left =0;	break;
case K_DOWN:   keys.down =0;	break;
case K_RIGHT:  keys.right =0;	break;
case K_CAMERA: keys.camera =0;
	camera =(vect){0,0};	break;
default:	break;}}

// actions handling
if (keys.camera){
	if (keys.up && camera.y>-TERRAIN_BORDER)
		camera.y-=2*var.zoom;
	if (keys.left && camera.x>-TERRAIN_BORDER)
		camera.x-=2*var.zoom;
	if (keys.down && camera.y<TERRAIN_BORDER)//TH = 20!
		camera.y+=2*var.zoom;
	if (keys.right && camera.x<TERRAIN_BORDER)//to fix
		camera.x+=2*var.zoom;}

//field of view
//pixel map with a given ratio to convert
//keep in mem only the rects' coord in this system
// displaying
draw(renderer, &var, camera, t_char, &r_char, nb, t_sprite1, t_sprite_r);
if (grid_on) draw_grid(renderer, camera, t_grid);
SDL_RenderPresent(renderer);
}

free(t_sprite_r);
SDL_DestroyTexture(t_sprite1);
SDL_DestroyTexture(t_char);
SDL_DestroyTexture(t_grid);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();	return 0;}
