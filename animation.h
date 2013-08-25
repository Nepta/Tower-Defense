#ifndef __animation_H__
#define __animation_H__

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
}Animation;

#endif /* __animation_H__ */

