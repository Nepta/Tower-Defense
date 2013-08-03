#include "inputInterface.h"
#include <stdio.h>
#include <SDL/SDL.h>

int pollMouseClick(){
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.key.keysym.sym){
		case SDLK_ESCAPE:
			return 1;
		default:
			break;
	}
 return 0;
}
