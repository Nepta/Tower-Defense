#include "shoot.h"
#include <stdio.h>
#include <math.h>

int isEnemyInRange(Enemy *enemy, Tower *tower){
	int x = enemy->position.x;
	int y = enemy->position.y;
	int i = tower->towerBox.x;
	int j = tower->towerBox.y;
	int r = tower->range;
	int towerToEnemyDistance = ((x-i)*(x-i)) + ((y-j)*(y-j));
	return towerToEnemyDistance <= r*r ? 1 : 0;
}

void shootEnemy(ShootManager *shootManager){
	Tower *(*towers)[MaxWidthTower][MaxHeightTower] = shootManager->towers;
	EnemySwag *enemys = shootManager->enemys;
	for(int i=0; i<MaxWidthTower; i++){
		for(int j=0; j<MaxHeightTower; j++){
			if((*towers)[i][j] != NULL){
				if(enemys->isEmpty != 1){
					for(int k=0; k<enemys->swagSize; k++){
						if(enemys->enemy[k].life > 0){
							if(isEnemyInRange(&enemys->enemy[k],(*towers)[i][j])){
								hitEnemy((*towers)[i][j], &enemys->enemy[k]);
								break; // a tower can hit only one enemy
							}
						}
					}
				}
			}
		}
	}
}

void hitEnemy(Tower *tower, Enemy *enemy){
	int isTargetAcquired = tower->target.x != tower->towerBox.x || tower->target.y != tower->towerBox.y;
	if(isTargetAcquired){
		int isTargetReached = (int)tower->bulletPositionX == tower->target.x && (int)tower->bulletPositionY == tower->target.y;
		if(isTargetReached){
		 	enemy->life--;
		 	tower->bulletPositionX = tower->towerBox.x;
		 	tower->bulletPositionY = tower->towerBox.y;
			tower->target.x = tower->towerBox.x;
			tower->target.y = tower->towerBox.y;
		}else{
			// get direction vector of bullet
			float bulletDirectionX = tower->target.x - tower->bulletPositionX;
			float bulletDirectionY = tower->target.y - tower->bulletPositionY;
			//normalize direction vector
			float bulletDirectionNorme = sqrt(pow(bulletDirectionX,2) + pow(bulletDirectionY,2));
			bulletDirectionX /= bulletDirectionNorme;
			bulletDirectionY /= bulletDirectionNorme;
			tower->bulletPositionX += bulletDirectionX;
			tower->bulletPositionY += bulletDirectionY;
		}
	}else{
		tower->target.x = enemy->position.x;
		tower->target.y = enemy->position.y;
	}
}

ShootManager* newShootManager(Tower *(*towers)[MaxWidthTower][MaxHeightTower], EnemySwag *enemys){
	ShootManager *shootManager = malloc(sizeof (ShootManager));
	shootManager->enemys = enemys;
	shootManager->towers = towers;
 return shootManager;
}

