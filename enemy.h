#ifndef __enemy_H__
#define __enemy_H__

#include <SDL/SDL.h>
#include "jsonParser.h"
#include "map.h"

/**
 * \brief State enumerator of an animation
 * each member describle the direction enemies are looking
 * \see enemy.json for value order
 */
typedef enum{
	UP = 0,		//!< use sprite that look north
	LEFT = 1,		//!< use sprite that look west
	DOWN = 2,		//!< use sprite that look south
	RIGHT = 3,	//!< use sprite that look east
	STAY = 4,		//!< use sprite that look south
	AnimationStateLenght	//!< lenght of an AnimationState enmumeration
}AnimationState;

/**
 *	\brief Animation for an Enemy
 *	List of sprite (position on a spriteSheet to display an animation
 * implemented with a looping list
 */
typedef struct enemyAnimation{
	SDL_Rect animation;							//!< current sprite to display
	struct enemyAnimation *nextAnimation;	//!< next sprite on spriteSheet
}EnemyAnimation;


/**
 * \brief Enemy structure
 * describle an enemy with it sprite sheet and position, life ...
 */
typedef struct{
	SDL_Surface *spriteSheet;									//!< spriteSheet as a SDL_Surface
	SDL_Rect position;											//!< current enemy position on map
	EnemyAnimation *animation[AnimationStateLenght];	//!< animation tab
	//!< \attention don't touch layout of the upper part (needed for coin animation hack)
	int life;														//!< life of an enemy
	AnimationState animationState;							//!< current looking direction of ennemy
	SDL_Rect spriteSize;											//!< size of each tile in sprite sheet
}Enemy;

/**
 * A swag of ennemy that pop in the same time
 * for wave capabilities
 */
typedef struct enemySwag{
	int swagSize;						//!< size of the swag
	int isEmpty;						//!< tell if all enemy of a swag have been killed
	struct enemySwag *nextSwag;	//!< next wave of ennemy
	Enemy enemy[];						//!< Enemy list of the swag
}EnemySwag;

/**
 * create a new enemy
 * \param enemyName name of the enemy in the config file
 * \return the newly created enemy
 */
Enemy *newEnemy(char *enemySprite);

/**
 * Add a sprite to an enemy animation list at a specific looking direction
 * \param enemy the enemy to add animation
 * \param animation the sprite postion on sprite sheet
 * \param state enemy looking direction for animation
 */
void addEnemyAnimation(Enemy *enemy, SDL_Rect animation, AnimationState state);

/**
 * get the new looking direction from it's old and new position
 * \param oldPosition old position of enemy
 * \param newPosition new position of enemy
 * \return the new looking direction to obtain next animation state
 */
AnimationState getState(Position oldPosition, Position newPosition);

/**
 * get new position of enemy according to the path finding algorithm
 * and the new sprite in animation
 * \param enemy the enemy to update
 * \param map a map containing a path
 */
void updateEnemy(Enemy *enemy, Map **map);

/**
 * load ennemy with all its animation from its sprite sheet
 * \param enemy the enemy to load animation
 * \param jsonFile json configuration file where tile information are stocked
 * \param it iterator for the json parsing system
 */
void initEnemyAnimation(Enemy *enemy, TokenIterator *it, char* jsonFile);

/**
 * create a swag of ennemy by copying the one passed as argument
 * \param enemy the enemy to be copied
 * \param swagSize the size (number of ennemy) in the swag
 * \return a swag of enemy
 */
EnemySwag* createEnemySwag(Enemy *enemy, int swagSize);

/**
 * draw an enemy on screen
 * \param enemy the enemy to draw
 * \param screen screen where enemy will be draw
 */
void drawEnemy(Enemy *enemy, SDL_Surface *screen);

#endif /* __enemy_H__ */

