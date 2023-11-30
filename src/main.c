#include "SDL2/SDL.h"
#include <stdlib.h>//free,atoi.f
#include <string.h>//strcmp
#include "more/struct1.h"//vect
#include "more/rngbrush.h"//rng_init
#include "tnns.h"

#ifdef main//avoid WinMain error
#undef main//on windows
#endif
int main(int ac, char **av){

//RNG init
rng_init();
//SDL init
SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_NOPARACHUTE);
SDL_Window *window =SDL_CreateWindow("tnns",
		SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
SDL_Renderer *renderer =SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

//TODO: draw grid on the fly
/*
//making grid texture
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
*/

// loading sprites
SDL_Surface *s_char =SDL_LoadBMP("ass/char_16x24-front.bmp");
SDL_SetColorKey(s_char,SDL_TRUE,SDL_MapRGB(s_char->format,0x6F,0xFF,0x7F));
SDL_Texture *t_char =SDL_CreateTextureFromSurface(renderer, s_char);
SDL_FreeSurface(s_char);
//
SDL_Surface *sprite1 =SDL_LoadBMP("ass/bush_16.bmp");
SDL_SetColorKey(sprite1,SDL_TRUE,SDL_MapRGB(sprite1->format,0x6F,0xFF,0x7F));
SDL_Texture *t_sprite1 =SDL_CreateTextureFromSurface(renderer, sprite1);
SDL_FreeSurface(sprite1);
//
SDL_Surface *spriteTree =SDL_LoadBMP("ass/tree_40x48.bmp");
SDL_SetColorKey(spriteTree,SDL_TRUE,SDL_MapRGB(spriteTree->format,0x6F,0xFF,0x7F));
SDL_Texture *t_spriteTree =SDL_CreateTextureFromSurface(renderer,spriteTree);
SDL_FreeSurface(spriteTree);

//inline arguments parsing
float p; int offs;
if (ac>1) p =atof(av[1]); else p =GEN_DEFAULT_P;
if (ac>2) offs =atoi(av[2]); else offs =GEN_DEFAULT_OFFS;
if (offs !=-1) offs *=ASPECT_RATIO;
//other variables initialization
int grid_on =0;
Var var =(Var){ASPECT_RATIO,SPRITE_SIZE};
Keys keys =(Keys){0,0,0,0,0};

//vect pos =(vect){(WINDOW_WIDTH-16)/2,W}
//vect plpos =(vect){SPRITE_SIZE*9+8,SPRITE_SIZE*5+4+8*ASPECT_RATIO};
vect camera =(vect){0,0}; //must start on a tile edge for the grid to fit

//terrain generation
int nb =0;
vect *t_sprite_v =generate_terrain(&nb, p, offs); //<

int terminate =0;
SDL_Event e;
while(!terminate){

// event handling
while(SDL_PollEvent(&e)){
if (e.type ==SDL_QUIT) terminate++;
else if (e.type ==SDL_KEYDOWN) switch(e.key.keysym.sym){
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
		var.zoom--;}
		//zoom_rects(var.zoom, &r_char, nb, t_sprite_r);}
		break;
case K_ZOOMOUT:	if (var.zoom<8){
		var.zoom++;}
		//zoom_rects(var.zoom, &r_char, nb, t_sprite_r);}
		break;
default:	break;}
else if (e.type ==SDL_KEYUP) switch(e.key.keysym.sym){
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

//else if (keys.up){

//field of view
//pixel map with a given ratio to convert
//keep in mem only the rects' coord in this system
// displaying
draw(renderer, &var, camera, t_char, nb, t_sprite1, t_sprite_v);
if (grid_on) draw_grid(renderer, camera);
SDL_RenderPresent(renderer);
}

//free(t_sprite_r);
free(t_sprite_v);
SDL_DestroyTexture(t_sprite1);
SDL_DestroyTexture(t_char);
//SDL_DestroyTexture(t_grid);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();	return 0;}
