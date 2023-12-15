#ifndef TNNS_H
#define TNNS_H
#include "SDL2/SDL.h"
#include "more/struct1.h"//vect

//default world generation
#define GEN_DEFAULT_P 0.6
#define GEN_DEFAULT_OFFS 2

//controls
#define K_QUIT	SDLK_0
#define K_GRID	SDLK_g
#define K_UP	SDLK_w
#define K_LEFT	SDLK_a
#define K_DOWN	SDLK_s
#define K_RIGHT	SDLK_d
#define K_CAMERA	SDLK_LSHIFT
#define K_TURNCAMERA	SDLK_BACKSLASH
#define K_ZOOMIN	SDLK_z
#define K_ZOOMOUT	SDLK_x


//color constants
#define BG_R 0x6F
#define BG_G 0xFF
#define BG_B 0x7F
#define GRID_R 0x94
#define GRID_G 0x94
#define GRID_B 0x49
#define GRID_A 0x4F

#define ASPECT_RATIO 4
#define SPRITE_BASE 16
#define SPRITE_SIZE SPRITE_BASE*ASPECT_RATIO
#define SPRITES_WIDTH 20
#define SPRITES_HEIGHT 12
#define WINDOW_WIDTH SPRITE_SIZE*SPRITES_WIDTH +SPRITES_WIDTH-2
#define WINDOW_HEIGHT SPRITE_SIZE*SPRITES_HEIGHT +SPRITES_HEIGHT-2

#define TERRAIN_WIDTH SPRITES_WIDTH
#define TERRAIN_HEIGHT SPRITES_HEIGHT
#define TERRAIN_BORDER 48*ASPECT_RATIO

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3


typedef struct {
	int zoom;
	int sprite_size;
	int grid_on;
	int facing;
} Var;
typedef struct {
	int camera;
	int up,left,down,right;
} Keys;


// gen.c
vect *generate_terrain(int*,float,int);

// draw.c
void draw(SDL_Renderer*, Var*, vect, vect, SDL_Texture*, int, SDL_Texture*, vect*);

#endif
