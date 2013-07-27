#ifndef __gameEngine_H__
#define __gameEngine_H__

SDL_Surface* loadMap(char* mapName);
void initEnemyAnimation(Enemy *enemy);
Map** initMap();

#endif /* __gameEngine_H__ */

