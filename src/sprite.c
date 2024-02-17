#include "tnns.h"

Texture* load_textable(SDL_Renderer* renderer){
Texture* textable =malloc(sizeof(Texture)*N_SPRITE);
//TODO load from a table of strings
//  character
SDL_Surface *s_char =SDL_LoadBMP("ass/char_16x24-sprites.bmp");
SDL_SetColorKey(s_char,SDL_TRUE,
		SDL_MapRGB(s_char->format,0x6F,0xFF,0x7F));
SDL_Texture *t_char =SDL_CreateTextureFromSurface(renderer, s_char);
SDL_FreeSurface(s_char);
textable[0] =(Texture){16,24,t_char};
//  small bush
SDL_Surface *bush16 =SDL_LoadBMP("ass/bush_16.bmp");
SDL_SetColorKey(bush16,SDL_TRUE,
		SDL_MapRGB(bush16->format,0x6F,0xFF,0x7F));
SDL_Texture *t_bush16 =SDL_CreateTextureFromSurface(renderer, bush16);
SDL_FreeSurface(bush16);
textable[1] =(Texture){16,16,t_bush16};
//  fancy tree
SDL_Surface *treefancy4048 =SDL_LoadBMP("ass/tree_fancy_40x48.bmp");
SDL_SetColorKey(treefancy4048,SDL_TRUE,
		SDL_MapRGB(treefancy4048->format,0x6F,0xFF,0x7F));
SDL_Texture *t_treefancy4048
	=SDL_CreateTextureFromSurface(renderer,treefancy4048);
SDL_FreeSurface(treefancy4048);
textable[2] =(Texture){40,48,t_treefancy4048};
return textable;}

void free_textable(Texture* textable){
for (int i=0; i<N_SPRITE; i++)
	SDL_DestroyTexture(textable[i].tex);	return;}


void addinst(Instance** instlist, Texture* tex, int x,int y){
Instance* inst =malloc(sizeof(Instance));
inst->tex =tex;
inst->x =x;	inst->y =y;
inst->next =(*instlist);
if (!*instlist)	inst->previous =NULL;
else {	inst->previous =(*instlist)->previous;
	if ((*instlist)->previous)
		(*instlist)->previous->next =inst;
	if ((*instlist)->next)
		(*instlist)->next->previous =inst;}
(*instlist) =inst;	return;}

void free_instlist(Instance* instlist){
if (!instlist)		return;
//free_instlist(instlist->previous);
free_instlist(instlist->next);
free(instlist);		return;}
