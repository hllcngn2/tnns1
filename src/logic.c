#include "tnns.h"

void movement_keydown(int sym, Keys* keys, Ctxt_game* gc){
switch(sym){
case K_UP:     keys->up =1;
	if(!keys->camera) gc->facing =North;	break;
case K_LEFT:   keys->left =1;
	if(!keys->camera) gc->facing =West;	break;
case K_DOWN:   keys->down =1;
	if(!keys->camera) gc->facing =South;	break;
case K_RIGHT:  keys->right =1;
	if(!keys->camera) gc->facing =East;	break;
default:					break;}	return;}

void movement_keyup(int sym, Keys* keys, Ctxt_game* gc){
switch(sym){
case K_UP:     keys->up =0;
	if(!keys->camera){
		if(keys->left)		gc->facing =West;
		else if(keys->down)	gc->facing =South;
		else if(keys->right)	gc->facing =East;}	break;
case K_LEFT:   keys->left =0;
	if(!keys->camera){
		if(keys->up)		gc->facing =North;
		else if(keys->down)	gc->facing =South;
		else if(keys->right)	gc->facing =East;}	break;
case K_DOWN:   keys->down =0;
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
