#include "SDL2/SDL.h"
#include "tnns.h"
#include <stdlib.h>//free,atoi.f
#include <string.h>//strcmp
#include <time.h>

#ifdef main//avoid WinMain error
#undef main//on windows
#endif
int main(int ac, char **av){
//RNG init
srand(time(NULL));
//SDL init
SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_NOPARACHUTE);
SDL_Window *window =SDL_CreateWindow("tnns",
		SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
SDL_Renderer *renderer =SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

//inline arguments parsing
float p; int offs;
if (ac>1) p =atof(av[1]); else p =GEN_DEFAULT_P;
if (ac>2) offs =atoi(av[2]); else offs =GEN_DEFAULT_OFFS;
if (offs !=-1) offs *=ASPECT_RATIO;
//other variables
Ctxt_game* gc =(Ctxt_game*)malloc(sizeof(Ctxt_game));{
  vect plpos =(vect){(TERRAIN_WIDTH-16*ASPECT_RATIO)/2,
	 		 (TERRAIN_HEIGHT-24*ASPECT_RATIO)/2};
*gc =(Ctxt_game){SOUTH, plpos};}
Keys keys =(Keys){0,0,0,0,0};

// loading sprites
Ctxt_disp* dc =(Ctxt_disp*)malloc(sizeof(Ctxt_disp));{
//  character
SDL_Surface *s_char =SDL_LoadBMP("ass/char_16x24-sprites.bmp");
SDL_SetColorKey(s_char,SDL_TRUE,SDL_MapRGB(s_char->format,0x6F,0xFF,0x7F));
SDL_Texture *t_char =SDL_CreateTextureFromSurface(renderer, s_char);
SDL_FreeSurface(s_char);
//  bush
SDL_Surface *sprite1 =SDL_LoadBMP("ass/bush_16.bmp");
SDL_SetColorKey(sprite1,SDL_TRUE,SDL_MapRGB(sprite1->format,0x6F,0xFF,0x7F));
SDL_Texture *t_sprite1 =SDL_CreateTextureFromSurface(renderer, sprite1);
SDL_FreeSurface(sprite1);
//  tree
SDL_Surface *spriteTree =SDL_LoadBMP("ass/tree_40x48.bmp");
SDL_SetColorKey(spriteTree,SDL_TRUE,SDL_MapRGB(spriteTree->format,0x6F,0xFF,0x7F));
SDL_Texture *t_spriteTree =SDL_CreateTextureFromSurface(renderer,spriteTree);
SDL_FreeSurface(spriteTree);
vect camera =(vect){0,0};
*dc =(Ctxt_disp){ASPECT_RATIO, 0, camera, t_char, t_sprite1, t_spriteTree};}

//terrain generation
Ctxt_map* mc =(Ctxt_map*)malloc(sizeof(Ctxt_map));
mc->t_sprite_v =generate_terrain(&(mc->nt), p, offs);


int terminate =0;
SDL_Event e;
while(!terminate){

// event handling
while(SDL_PollEvent(&e)){
if (e.type ==SDL_QUIT)
	terminate++;
else if (e.type ==SDL_KEYDOWN) switch(e.key.keysym.sym){
	case K_QUIT: terminate++;	break;
	case K_GRID: dc->grid_on =(!dc->grid_on)?1:0;	break;
	case K_UP:     keys.up =1;
		if(!keys.camera) gc->facing =NORTH;	break;
	case K_LEFT:   keys.left =1;
		if(!keys.camera) gc->facing =WEST;	break;
	case K_DOWN:   keys.down =1;
		if(!keys.camera) gc->facing =SOUTH;	break;
	case K_RIGHT:  keys.right =1;
		if(!keys.camera) gc->facing =EAST;	break;
	case K_CAMERA: keys.camera =1;	break;
	case K_ZOOMIN:	if (dc->zoom>1) dc->zoom--; break;
	case K_ZOOMOUT:	if (dc->zoom<8) dc->zoom++; break;
	default:	break;}
else if (e.type ==SDL_KEYUP) switch(e.key.keysym.sym){
	case K_UP:     keys.up =0;	break;
	case K_LEFT:   keys.left =0;	break;
	case K_DOWN:   keys.down =0;	break;
	case K_RIGHT:  keys.right =0;	break;
	case K_CAMERA: keys.camera =0;
		dc->camera =(vect){0,0};	break;
	default:	break;}}

// actions handling
if (keys.camera){ //camera movement
	if(keys.up &&
		gc->plpos.y+dc->camera.y-(WINDOW_HEIGHT-16*ASPECT_RATIO)/2
			>-TERRAIN_BORDER)
		dc->camera.y-=2*dc->zoom;
	if(keys.left &&
		gc->plpos.x+dc->camera.x-(WINDOW_WIDTH-16*ASPECT_RATIO)/2
			>-TERRAIN_BORDER)
		dc->camera.x-=2*dc->zoom;
	if(keys.down &&
		gc->plpos.y+dc->camera.y-(WINDOW_HEIGHT-16*ASPECT_RATIO)/2
			<TERRAIN_HEIGHT+TERRAIN_BORDER-WINDOW_HEIGHT)
		dc->camera.y+=2*dc->zoom;
	if(keys.right &&
		gc->plpos.x+dc->camera.x-(WINDOW_WIDTH-16*ASPECT_RATIO)/2
			<TERRAIN_WIDTH+TERRAIN_BORDER-WINDOW_WIDTH)
		dc->camera.x+=2*dc->zoom;}
else { //normal movement
       //with collision detection
	if (keys.up && gc->plpos.y>-8*ASPECT_RATIO)
		gc->plpos.y-=1*dc->zoom;
	if (keys.left && gc->plpos.x>0)
		gc->plpos.x-=1*dc->zoom;
	if (keys.down && gc->plpos.y<TERRAIN_HEIGHT-24*ASPECT_RATIO-1)
		gc->plpos.y+=1*dc->zoom;
	if (keys.right && gc->plpos.x<TERRAIN_WIDTH-16*ASPECT_RATIO-1)
		gc->plpos.x+=1*dc->zoom;}

// displaying
draw(renderer, dc, mc, gc);
SDL_RenderPresent(renderer);

}

free(gc);
free(mc->t_sprite_v);
free(mc);
SDL_DestroyTexture(dc->t_tree);
SDL_DestroyTexture(dc->t_sprite);
SDL_DestroyTexture(dc->t_char);
free(dc);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();	return 0;}
