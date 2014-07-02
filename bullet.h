#ifndef __bullet_H__
#define __bullet_H__

#include <SDL/SDL.h>

/**
 * a bullet
 */
typedef struct{
	double positionX;		//!< postion (x) of tower's bullet
	double positionY;		//!< postion (y) of tower's bullet
	SDL_Rect target;				//!< postion of tower's target
}Bullet;

/**
 * bullet creation function, called by a tower when an enemy is spotted
 * \return the created bullet or NULL if there aren't enemy in range
 */
Bullet* createBullet(Tower *tower);

#endif /* __bullet_H__ */

