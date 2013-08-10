#ifndef __enemy_H__
#define __enemy_H__

#include <SDL/SDL.h>
#include "map.h"

/**
 * \brief State enumerator of an animation
 * each member describle the direction enemies are looking
 */
typedef enum{
	UP,		//!< use sprite that look north
	DOWN,		//!< use sprite that look south
	LEFT,		//!< use sprite that look west
	RIGHT,	//!< use sprite that look east
	STAY,		//!< use sprite that look south
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
typedef struct enemy{
	SDL_Surface *spriteSheet;									//!< spriteSheet as a SDL_Surface
	SDL_Rect position;											//!< current enemy position on map
	AnimationState animationState;							//!< current looking direction of ennemy
	EnemyAnimation *animation[AnimationStateLenght];	//!< animation tab
}Enemy;

/**
 * create a new enemy
 * \param enemySprite path to enemy sprite sheet
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

#endif /* __enemy_H__ */

