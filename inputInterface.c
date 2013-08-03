#include "inputInterface.h"
#include <stdio.h>
#include <SDL/SDL.h>

int pollMouseClick(Interface interfaces){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE){
					return 1;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.x > mapWidth){
					int x = event.button.x - mapWidth;
					int y = event.button.y;
					clickOnMenu(interfaces.menu, x,y);
				}
				break;
			default:
				break;
		}
	}
 return 0;
}


