#ifndef __shoot_H__
#define __shoot_H__
#include "enemy.h"
#include "tower.h"
/**
 * A shooting manager connects towers and enemys to know if a tower can shoot an enemy
 */
typedef struct{
	EnemySwag *enemys;											//!< a list of enemy to manage
	Tower *(*towers)[MaxWidthTower][MaxHeightTower];	//!< a list of tower to manage
}ShootManager;

/**
 * Check if an enemy can be shoot
 * \param enemy the enemy to shoot
 * \param tower the tower which will may shoot the enemy
 * \return 1 if the enemy can be shoot
 */
int isEnemyInRange(Enemy *enemy, Tower *tower);

/**
 * Function to search and destroy enemy
 * \param shootManager entity that know each tower and each enemy
 */
void shootEnemy(ShootManager *shootManager);


/**
 * function called when a tower can hit an enemy
 * \param tower the tower which can hit the enemy
 * \param enemy the enemy which will be hitten
 */
void hitEnemy(Tower *tower, Enemy *enemy);

/**
 * create a shoot manager that connect towers to theirs target
 * \param towers a list of tower
 * \param enemys a list of enemy
 * \return the shooting manager
 */
ShootManager* newShootManager(Tower *(*tower)[MaxWidthTower][MaxHeightTower], EnemySwag *enemys);

#endif /* __shoot_H__ */

