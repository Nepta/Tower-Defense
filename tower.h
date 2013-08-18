#ifndef __tower_H__
#define __tower_H__

#include <SDL/SDL.h>
#include "map.h"

/**
 * A tower type
 */
typedef struct{
	SDL_Rect towerBox;	//!< position en size of the tower
	SDL_Surface *sprite;	//!< sprite of the tower
}Tower;

/**
 * a tower manager check if a tower can be placed and sanitize the environement
 * redo pathFinding if necessary, take money for tower creation ...
 */
typedef struct{
	Map **workPlace; 			//!< place were manager set tower
	Tower *towers[25][18];	//!< tower list (for a 800 x 600 map we can only put 25 x 18 size 32 towers)
}TowerManager;

/**
 * function that create a tower
 * \param sprite the tower Sprite
 * \param x x position of the tower
 * \param y y position of the tower
 * \return the constructed Tower
 */
Tower* newTower(SDL_Surface *sprite, int x, int y);

#endif /* __tower_H__ */

