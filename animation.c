#include "animation.h"

void addEnemyAnimation(SDL_Rect animation, EnemyAnimation *animationList){
	EnemyAnimation *firstAnimation = animationList;
	while(animationList->nextAnimation != firstAnimation){
		animationList = animationList->nextAnimation;
	}
	EnemyAnimation *newAnimation = malloc(sizeof (EnemyAnimation));
	newAnimation->animation = animation;
	newAnimation->nextAnimation = firstAnimation;
	animationList->nextAnimation = newAnimation;
}
