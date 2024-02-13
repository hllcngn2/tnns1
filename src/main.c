#include "tnns.h"

#ifdef main//avoid WinMain error
#undef main//on windows
#endif

int main(int ac, char **av){
//RNG init
srand(time(NULL));

//SDL init
SDL_Init(SDL_INIT_VIDEO |SDL_INIT_TIMER |SDL_INIT_NOPARACHUTE);
SDL_Window   *window =SDL_CreateWindow("tnns",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN |SDL_WINDOW_BORDERLESS);
SDL_Renderer *renderer =SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED |SDL_RENDERER_PRESENTVSYNC);

// loading sprites into display context struct
Ctxt_disp* dc =malloc(sizeof(Ctxt_disp));
{ int grid_on =0; vect camera =(vect){0,0};
*dc =(Ctxt_disp){ASPECT_RATIO, grid_on, camera, NULL};
dc->tex =malloc(sizeof(SDL_Texture*)*N_SPRITE);

//  character
SDL_Surface *s_char =SDL_LoadBMP("ass/char_16x24-sprites.bmp");
SDL_SetColorKey(s_char,SDL_TRUE,
		SDL_MapRGB(s_char->format,0x6F,0xFF,0x7F));
SDL_Texture *t_char =SDL_CreateTextureFromSurface(renderer, s_char);
SDL_FreeSurface(s_char);
dc->tex[CHARACTER] =t_char;
//  small bush
SDL_Surface *bush16 =SDL_LoadBMP("ass/bush_16.bmp");
SDL_SetColorKey(bush16,SDL_TRUE,
		SDL_MapRGB(bush16->format,0x6F,0xFF,0x7F));
SDL_Texture *t_bush16 =SDL_CreateTextureFromSurface(renderer, bush16);
SDL_FreeSurface(bush16);
dc->tex[BUSH16] =t_bush16;
//  fancy tree
SDL_Surface *treefancy4048 =SDL_LoadBMP("ass/tree_fancy_40x48.bmp");
SDL_SetColorKey(treefancy4048,SDL_TRUE,
		SDL_MapRGB(treefancy4048->format,0x6F,0xFF,0x7F));
SDL_Texture *t_treefancy4048
	=SDL_CreateTextureFromSurface(renderer,treefancy4048);
SDL_FreeSurface(treefancy4048);
dc->tex[TREEFANCY4048] =t_treefancy4048; }


//inline arguments parsing
float p; int offs;
if (ac>1) p =atof(av[1]);	else p =GEN_DEFAULT_P;
if (ac>2) offs =atoi(av[2]);	else offs =GEN_DEFAULT_OFFS;
if (offs !=-1) offs *=ASPECT_RATIO;
//other variables
Keys keys =(Keys){0,0,0,0,0};
//context
Ctxt_game* gc =malloc(sizeof(Ctxt_game));
{ vect plpos =(vect){(TERRAIN_WIDTH-16*ASPECT_RATIO)/2,
	 	     (TERRAIN_HEIGHT-24*ASPECT_RATIO)/2};
Direction facing =South;
*gc =(Ctxt_game){facing, plpos}; }


//terrain generation
Ctxt_map* mc =malloc(sizeof(Ctxt_map));
mc->t_sprite_v =generate_terrain(&(mc->nt), p, offs);




//main loop
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
	case K_CAMERA: keys.camera =1;	break;
	case K_ZOOMIN:	if (dc->zoom>1) dc->zoom--;	break;
	case K_ZOOMOUT:	if (dc->zoom<8) dc->zoom++;	break;
	case K_UP:
	case K_LEFT:
	case K_DOWN:
	case K_RIGHT:
		movement_keydown(e.key.keysym.sym,&keys,gc); break;
	default:			break;}
else if (e.type ==SDL_KEYUP) switch(e.key.keysym.sym){
	case K_CAMERA: keys.camera =0;
		dc->camera =(vect){0,0};	break;
	case K_UP:
	case K_LEFT:
	case K_DOWN:
	case K_RIGHT:
		 movement_keyup(e.key.keysym.sym,&keys,gc); break;
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
free(mc->t_sprite_v); free(mc);
for (int i=0; i<N_SPRITE; i++)
	SDL_DestroyTexture(dc->tex[i]); free(dc);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();	return 0;}
