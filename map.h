#ifndef __map_H__
#define __map_H__

#include <SDL/SDL.h>
#include "enemy.h"

typedef struct{
	int x;
	int y;
}Position;

typedef struct Map{
	int x; int y;
	Position path;
	int hasTower;
}Map;

SDL_Surface* loadMap(char* mapName);
void initEnemyAnimation(Enemy *enemy);
Map** initMap();
#endif /* __map_H__ */

