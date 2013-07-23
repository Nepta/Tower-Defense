#ifndef __animation_H__
#define __animation_H__

#include <SDL/SDL.h>

typedef struct enemyAnimation{
	SDL_Rect animation;
	struct enemyAnimation *nextAnimation;
}EnemyAnimation;



#endif /* __animation_H__ */

