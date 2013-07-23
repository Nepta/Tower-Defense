#ifndef __map_H__
#define __map_H__

#include <SDL/SDL.h>
#include "enemy.h"

SDL_Surface* loadMap(char* mapName);
void initEnemyAnimation(Enemy *enemy);
#endif /* __map_H__ */

