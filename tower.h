#ifndef __tower_H__
#define __tower_H__

#include <SDL/SDL.h>
#include "map.h"
#include "interfaces.h"
#include "enemy.h"

#define MaxWidthTower 25	//!< for a 800 x 600 map we can only put 25 size 32 towers in a line
#define MaxHeightTower 18	//!< for a 800 x 600 map we can only put 18 size 32 towers in a column

/**
 * A tower type
 */
typedef struct{
	SDL_Rect towerBox;			//!< position and size of the tower
	SDL_Surface *sprite;			//!< sprite of the tower
	double bulletPositionX;		//!< postion (x) of tower's bullet
	double bulletPositionY;		//!< postion (y) of tower's bullet
	SDL_Rect target;				//!< postion of tower's target
	double range;					//!< the range of which a tower can shoot an enemy
	Enemy *targetedEnemy;		//!< ennemy the tower is targeting
}Tower;

/**
 * a tower manager check if a tower can be placed and sanitize the environement
 * redo pathFinding if necessary, take money for tower creation ...
 */
typedef struct{
	Map **workPlace; 			//!< place were manager set tower
	Tower* towers[MaxWidthTower][MaxHeightTower];	//!< tower list
}TowerManager;

/**
 * function to retrieve tower in the tower map
 * \param x x position of the tower
 * \param y y position of the tower
 * \return zone where the tower sit
 */
Position getTowerZone(int x, int y);

/**
 * function that create a tower
 * \param sprite the tower Sprite
 * \param towerBox position and size of the tower
 * \param range the range a tower can shoot enemy
 * \return the constructed Tower
 */
Tower* newTower(SDL_Surface *sprite, SDL_Rect towerBox, int range);

/**
 * create a tower manager
 * \param map a map to manage
 * \return a tower manager
 */
TowerManager* newTowerManager(Map **map);

/**
 * place a tower in the field and what it imply if we can
 * \param field the field to place tower
 * \param x x position of the tower
 * \param y y position of the tower
 * \return 1 if a tower has been placed
 */
int placeTower(Interface* interfaces, int x, int y);

/**
 * tell if two square are overlapping
 * \param rect1 the first square
 * \param rect2 the second square
 * \return 1 if the two square are overlapping
 */
int isOverlapping(SDL_Rect rect1, SDL_Rect rect2);

/**
 * blit all the tower and their shoot in the workPlace
 * \param field the field where tower must be blit
 */
void updateTower(FieldInterface *field);

/**
 * target an enemy to shoot at him
 * \param
 */
void targetEnemy(Tower *tower, Enemy *enemy);

#endif /* __tower_H__ */

