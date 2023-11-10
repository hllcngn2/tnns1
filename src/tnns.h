#ifndef TNNS_H
#define TNNS_H
#include "SDL2/SDL.h"
#include "more/struct1.h"

#define GEN_DEFAULT_P 0.35
#define GEN_DEFAULT_OFFS 7

#define K_QUIT	SDLK_0
#define K_GRID	SDLK_g
#define K_UP	SDLK_w
#define K_LEFT	SDLK_a
#define K_DOWN	SDLK_s
#define K_RIGHT	SDLK_d
#define K_CAMERA SDLK_LSHIFT
#define K_TURNCAMERA SDLK_BACKSLASH
#define K_ZOOMIN SDLK_z
#define K_ZOOMOUT SDLK_x

#define BG_R 0x6F
#define BG_G 0xFF
#define BG_B 0x7F
#define GRID_R 0xFF
#define GRID_G 0xFF
#define GRID_B 0xFF
#define GRID_A 0x7F

//TODO: fix this part
//- add specific sprites base sizes
#define ASPECT_RATIO 1
#define SPRITE_BASE 16
#define SPRITE_SIZE SPRITE_BASE*ASPECT_RATIO
#define SPRITES_WIDTH 20
#define SPRITES_HEIGHT 12
#define WINDOW_WIDTH SPRITE_SIZE*SPRITES_WIDTH +SPRITES_WIDTH-2
#define WINDOW_HEIGHT SPRITE_SIZE*SPRITES_HEIGHT +SPRITES_HEIGHT-2
#define T_GRID_W WINDOW_WIDTH+SPRITE_SIZE+2
#define T_GRID_H WINDOW_HEIGHT+SPRITE_SIZE+2

//TODO: make TERRAIN into a fixed pixel map
#define TERRAIN_WIDTH SPRITES_WIDTH
#define TERRAIN_HEIGHT SPRITES_HEIGHT
#define TERRAIN_BORDER 48*ASPECT_RATIO

// player
//first name
//family name
/*
typedef struct {
} Tile;
typedef Tile** Terrain;
*/

typedef struct {
	int zoom;
	int sprite_size;
} Var;

typedef struct {
	int camera;
	int up,left,down,right;
} Keys;
/*
typedef struct {
	SDL_Rect *r_char;
	SDL_Rect **t_sprite_r;
	SDL_Texture *t_char, *t_sprite1;
}mystruct;
*/

SDL_Rect *generate_terrain(int*,float,int);

void draw_grid(SDL_Renderer*, vect, SDL_Texture*);
void draw(SDL_Renderer*, Var*, vect, SDL_Texture*, SDL_Rect*, int, SDL_Texture*, SDL_Rect*);
void zoom_rects(int, SDL_Rect*, int, SDL_Rect*);

#endif