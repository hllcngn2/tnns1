#pragma once
#include "SDL2/SDL.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdio.h>


//default world generation
#define GEN_DEFAULT_P	 0.6
#define GEN_DEFAULT_OFFS 2
#define N_SPRITE	 3

//controls
#define K_UP		SDLK_w
#define K_LEFT		SDLK_a
#define K_DOWN		SDLK_s
#define K_RIGHT		SDLK_d
#define K_QUIT		SDLK_EQUALS
#define K_GRID		SDLK_g
#define K_CAMERA	SDLK_LSHIFT
#define K_TURNCAMERA	SDLK_BACKSLASH
#define K_ZOOMIN	SDLK_z
#define K_ZOOMOUT	SDLK_x

//default sizes
// sprites
#define SPRITE_BASE	16
#define ASPECT_RATIO	4
#define SPRITE_SIZE	SPRITE_BASE*ASPECT_RATIO
// terrain
#define SPRITES_WIDTH	30
#define SPRITES_HEIGHT	20
#define TERRAIN_BORDER	48*ASPECT_RATIO
#define TERRAIN_WIDTH	SPRITES_WIDTH*SPRITE_SIZE
#define TERRAIN_HEIGHT	SPRITES_HEIGHT*SPRITE_SIZE
// window
#define WINDOW_SPRITES_WIDTH	20
#define WINDOW_SPRITES_HEIGHT	12
#define WINDOW_WIDTH		WINDOW_SPRITES_WIDTH*SPRITE_SIZE
#define WINDOW_HEIGHT		WINDOW_SPRITES_HEIGHT*SPRITE_SIZE

//sprites index
#define CHARACTER	0
#define BUSH16		1
#define TREEFANCY4048	2

//colors constants
#define BG_R	0x6F
#define BG_G	0xFF
#define BG_B	0x7F
#define GRID_R	0x94
#define GRID_G	0x94
#define GRID_B	0x49
#define GRID_A	0x4F


//keywords
typedef enum{	North,East,South,West	} Direction;

//utilitary structs
typedef struct{	int x,y;	}vect;
typedef struct{	int x,y,w,h;	}rect;

typedef struct{	int		w,h;
		SDL_Texture*	tex;	}Texture;
typedef struct Instance{
		int		x,y;
		Texture*	tex;
		struct Instance	*previous,*next;	}Instance;

//context structs
typedef struct {
		int zoom;
		int grid_on;
		vect camera;
		Texture* textable;	} Ctxt_disp;
typedef struct {
		Direction facing;
		vect plpos;		} Ctxt_game;
typedef struct {
		int nt;
		Instance* instlist;	} Ctxt_map;

//other structures
typedef struct {
	int camera;
	int up,left,down,right;
} Keys;



// gen.c
void generate_terrain(Ctxt_map* mc, Texture* textable, float p,int offs);

// sprite.c
Texture* load_textable(SDL_Renderer* renderer);
void free_textable(Texture* textable);
void addinst(Instance** instlist, Texture* tex, int x,int y);
void free_instlist(Instance* instlist);

// draw.c
void draw(SDL_Renderer*, Ctxt_disp*, Ctxt_map*, Ctxt_game*);

// logic.c
void movement_keydown(int sym, Keys* keys, Ctxt_game* gc);
void movement_keyup(int sym, Keys* keys, Ctxt_game* gc);
void player_movement(Keys* keys, Ctxt_game* gc, Ctxt_disp* dc);
void camera_movement(Keys* keys, Ctxt_game* gc, Ctxt_disp* dc);
