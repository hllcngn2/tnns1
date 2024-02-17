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

//loading sprites into display context struct
Ctxt_disp* dc =malloc(sizeof(Ctxt_disp));
{ int grid_on =0; vect camera =(vect){0,0};
*dc =(Ctxt_disp){ASPECT_RATIO, grid_on, camera, NULL};
dc->textable =load_textable(renderer); }

//inline arguments parsing
float p; int offs;
if (ac>1) p =atof(av[1]);	else p =GEN_DEFAULT_P;
if (ac>2) offs =atoi(av[2]);	else offs =GEN_DEFAULT_OFFS;
if (offs !=-1) offs *=ASPECT_RATIO;
//other variables
Keys keys =(Keys){0,0,0,0,0};
//game context
Ctxt_game* gc =malloc(sizeof(Ctxt_game));
{ vect plpos =(vect){(TERRAIN_WIDTH-16*ASPECT_RATIO)/2,
	 	     (TERRAIN_HEIGHT-24*ASPECT_RATIO)/2};
Direction facing =South;
*gc =(Ctxt_game){facing, plpos}; }


//terrain generation
Ctxt_map* mc =malloc(sizeof(Ctxt_map));
mc->instlist =NULL;
generate_terrain(mc, dc->textable, p, offs);



//main loop
int terminate =0;
SDL_Event e;
while(!terminate){

// event handling
while(SDL_PollEvent(&e)){
if (e.type ==SDL_QUIT)
	terminate++;

else if (e.type ==SDL_KEYDOWN) switch(e.key.keysym.sym){
	case K_QUIT:	terminate++;			break;

	case K_GRID:	dc->grid_on =(!dc->grid_on)?1:0; break;
	case K_CAMERA:	keys.camera =1;			break;
	case K_ZOOMIN:	if (dc->zoom>1) dc->zoom--;	break;
	case K_ZOOMOUT:	if (dc->zoom<8) dc->zoom++;	break;

	case K_UP:
	case K_LEFT:
	case K_DOWN:
	case K_RIGHT:
		movement_keydown(e.key.keysym.sym,&keys,gc); break;
	default:					break;}

else if (e.type ==SDL_KEYUP) switch(e.key.keysym.sym){
	case K_CAMERA: keys.camera =0;
		dc->camera =(vect){0,0};		break;

	case K_UP:
	case K_LEFT:
	case K_DOWN:
	case K_RIGHT:
		 movement_keyup(e.key.keysym.sym,&keys,gc); break;
	default:					break;}}

// updates
if (keys.camera) camera_movement(&keys,gc,dc);
else		 player_movement(&keys,gc,dc);

// displaying
draw(renderer, dc, mc, gc);
SDL_RenderPresent(renderer);

}//end of main loop


free(gc);
free_instlist(mc->instlist); free(mc);
free_textable(dc->textable); free(dc);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();	return 0;}
