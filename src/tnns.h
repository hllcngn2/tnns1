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


//colors constants
#define BG_R 0x6F
#define BG_G 0xFF
#define BG_B 0x7F
#define GRID_R 0x94
#define GRID_G 0x94
#define GRID_B 0x49
#define GRID_A 0x4F

//default sizes
// sprites
#define SPRITE_BASE 16
#define ASPECT_RATIO 4
#define SPRITE_SIZE SPRITE_BASE*ASPECT_RATIO
// terrain
#define SPRITES_WIDTH 30
#define SPRITES_HEIGHT 20
#define TERRAIN_BORDER 48*ASPECT_RATIO
#define TERRAIN_WIDTH SPRITES_WIDTH*SPRITE_SIZE
#define TERRAIN_HEIGHT SPRITES_HEIGHT*SPRITE_SIZE
// window
#define WINDOW_SPRITES_WIDTH 20
#define WINDOW_SPRITES_HEIGHT 12
#define WINDOW_WIDTH WINDOW_SPRITES_WIDTH*SPRITE_SIZE
#define WINDOW_HEIGHT WINDOW_SPRITES_HEIGHT*SPRITE_SIZE

//keywords
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3


typedef struct {
	int facing;
	vect plpos;
} Ctxt_game;
typedef struct {
	int nt;
	vect* t_sprite_v;
} Ctxt_map;
typedef struct {
	int zoom;
	int grid_on;
	vect camera;
	SDL_Texture
		*t_char,
		*t_sprite,
		*t_tree;
} Ctxt_disp;
typedef struct {
	int camera;
	int up,left,down,right;
} Keys;


// gen.c
vect *generate_terrain(int*,float,int);

// draw.c
void draw(SDL_Renderer*, Ctxt_disp*, Ctxt_map*, Ctxt_game*);

#endif
