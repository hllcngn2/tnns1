#include "SDL2/SDL.h"
#include "tnns.h"
#include "more/rngbrush.h"//rng_init
#include <stdlib.h>//free,atoi.f
#include <string.h>//strcmp
#include "more/struct1.h"//vect

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

// loading sprites
//  character
SDL_Surface *s_char =SDL_LoadBMP("ass/char_16x24-front.bmp");
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

//inline arguments parsing
float p; int offs;
if (ac>1) p =atof(av[1]); else p =GEN_DEFAULT_P;
if (ac>2) offs =atoi(av[2]); else offs =GEN_DEFAULT_OFFS;
if (offs !=-1) offs *=ASPECT_RATIO;
//other variables
Var var =(Var){ASPECT_RATIO,SPRITE_SIZE,0};
Keys keys =(Keys){0,0,0,0,0};
vect camera =(vect){0,0};
//vect pos =(vect){(WINDOW_WIDTH-16)/2,W}
//vect plpos =(vect){SPRITE_SIZE*9+8,SPRITE_SIZE*5+4+8*ASPECT_RATIO};

//terrain generation
int nb =0;
vect *t_sprite_v =generate_terrain(&nb, p, offs); //<


int terminate =0;
SDL_Event e;
while(!terminate){

// event handling
while(SDL_PollEvent(&e)){
if (e.type ==SDL_QUIT)
	terminate++;
else if (e.type ==SDL_KEYDOWN) switch(e.key.keysym.sym){
	case K_QUIT: terminate++;	break;
	case K_GRID: var.grid_on =(!var.grid_on)?1:0;	break;
	case K_UP:     keys.up =1;	break;
	case K_LEFT:   keys.left =1;	break;
	case K_DOWN:   keys.down =1;	break;
	case K_RIGHT:  keys.right =1;	break;
	case K_CAMERA: keys.camera =1;
	//	if (!keys.camera){ keys.up =0; keys.left =0;
	//		keys.down =0; keys.right =0;}
		break;
	case K_ZOOMIN:	if (var.zoom>1) var.zoom--; break;
	case K_ZOOMOUT:	if (var.zoom<8) var.zoom++; break;
	default:	break;}
else if (e.type ==SDL_KEYUP) switch(e.key.keysym.sym){
	case K_UP:     keys.up =0;	break;
	case K_LEFT:   keys.left =0;	break;
	case K_DOWN:   keys.down =0;	break;
	case K_RIGHT:  keys.right =0;	break;
	case K_CAMERA: keys.camera =0;
		camera =(vect){0,0};	break;
		       //camera to center on the character again
	default:	break;}}

// actions handling
if (keys.camera){ //camera movement
       //don't move the character with the camera
	if (keys.up && camera.y>-TERRAIN_BORDER)
		camera.y-=2*var.zoom;
	if (keys.left && camera.x>-TERRAIN_BORDER)
		camera.x-=2*var.zoom;
	if (keys.down && camera.y<TERRAIN_BORDER)//TH = 20!
		camera.y+=2*var.zoom;
	if (keys.right && camera.x<TERRAIN_BORDER)//to fix
		camera.x+=2*var.zoom;}
else { //normal movement
       //with collision detection
       //+ possibility to move freely at the edges of terrain
	if (keys.up && camera.y>-TERRAIN_BORDER)
		camera.y-=1*var.zoom;
	if (keys.left && camera.x>-TERRAIN_BORDER)
		camera.x-=1*var.zoom;
	if (keys.down && camera.y<TERRAIN_BORDER)//TH = 20!
		camera.y+=1*var.zoom;
	if (keys.right && camera.x<TERRAIN_BORDER)//to fix
		camera.x+=1*var.zoom;}

// displaying
draw(renderer, &var, camera, t_char, nb, t_sprite1, t_sprite_v);
SDL_RenderPresent(renderer);

}

free(t_sprite_v);
SDL_DestroyTexture(t_spriteTree);
SDL_DestroyTexture(t_sprite1);
SDL_DestroyTexture(t_char);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();	return 0;}
