#include "bullet.h"

Bullet* createBullet(Tower *tower){
	if(tower->targetedEnemy != NULL){
		Bullet *bullet = malloc(sizeof (Bullet));
		bullet->target = tower->target;
		bullet->target.w = towerBox.w;
		bullet->target.h = towerBox.h;			//FIXME still usefull?
		bullet->positionX = tower->towerBox.x;
		bullet->positionY = tower->towerBox.y;
		return bullet;
	}else{
		return NULL;
	}
}
