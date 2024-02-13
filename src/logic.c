#include "tnns.h"

void movement_keydown(int sym, Keys* keys, Ctxt_game* gc){
switch(sym){
case K_UP:     keys->up    =1;
	if(!keys->camera) gc->facing =North;	break;
case K_LEFT:   keys->left  =1;
	if(!keys->camera) gc->facing =West;	break;
case K_DOWN:   keys->down  =1;
	if(!keys->camera) gc->facing =South;	break;
case K_RIGHT:  keys->right =1;
	if(!keys->camera) gc->facing =East;	break;
default:					break;}	return;}

void movement_keyup(int sym, Keys* keys, Ctxt_game* gc){
switch(sym){
case K_UP:     keys->up    =0;
	if(!keys->camera){
		if(keys->left)		gc->facing =West;
		else if(keys->down)	gc->facing =South;
		else if(keys->right)	gc->facing =East;}	break;
case K_LEFT:   keys->left  =0;
	if(!keys->camera){
		if(keys->up)		gc->facing =North;
		else if(keys->down)	gc->facing =South;
		else if(keys->right)	gc->facing =East;}	break;
case K_DOWN:   keys->down  =0;
	if(!keys->camera){
		if(keys->up)		gc->facing =North;
		else if(keys->left)	gc->facing =West;
		else if(keys->right)	gc->facing =East;}	break;
case K_RIGHT:  keys->right =0;
	if(!keys->camera){
		if(keys->up)		gc->facing =North;
		else if(keys->left)	gc->facing =West;
		else if(keys->down)	gc->facing =South;}	break;
default:							break;}
return;}

void player_movement(Keys* keys, Ctxt_game* gc, Ctxt_disp* dc){
if (keys->up    && gc->plpos.y>-8*ASPECT_RATIO)
	gc->plpos.y-=1*dc->zoom;
if (keys->left  && gc->plpos.x>0)
	gc->plpos.x-=1*dc->zoom;
if (keys->down  && gc->plpos.y<TERRAIN_HEIGHT-24*ASPECT_RATIO-1)
	gc->plpos.y+=1*dc->zoom;
if (keys->right && gc->plpos.x<TERRAIN_WIDTH-16*ASPECT_RATIO-1)
	gc->plpos.x+=1*dc->zoom;	return;}

void camera_movement(Keys* keys, Ctxt_game* gc, Ctxt_disp* dc){
if(keys->up    && gc->plpos.y+dc->camera.y-(WINDOW_HEIGHT-16*ASPECT_RATIO)/2
		>-TERRAIN_BORDER)
	dc->camera.y-=2*dc->zoom;
if(keys->left  && gc->plpos.x+dc->camera.x-(WINDOW_WIDTH-16*ASPECT_RATIO)/2
		>-TERRAIN_BORDER)
	dc->camera.x-=2*dc->zoom;
if(keys->down  && gc->plpos.y+dc->camera.y-(WINDOW_HEIGHT-16*ASPECT_RATIO)/2
		<TERRAIN_HEIGHT+TERRAIN_BORDER-WINDOW_HEIGHT)
	dc->camera.y+=2*dc->zoom;
if(keys->right && gc->plpos.x+dc->camera.x-(WINDOW_WIDTH-16*ASPECT_RATIO)/2
		<TERRAIN_WIDTH+TERRAIN_BORDER-WINDOW_WIDTH)
	dc->camera.x+=2*dc->zoom;	return;}
