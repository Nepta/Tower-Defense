#include "tower.h"
#include <SDL/SDL.h>
#include <stdlib.h>

Tower* newTower(SDL_Surface *sprite, int x, int y){
	Tower *tower = malloc(sizeof (Tower));
	tower->sprite = sprite;
	tower->towerBox.x = x;
	tower->towerBox.y = y;
 return tower;
}



