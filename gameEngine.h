#ifndef __gameEngine_H__
#define __gameEngine_H__


/**
 * load a map background into the game
 * \param path to the map image
 */
SDL_Surface* loadMap(char* mapName);

/**
 * load ennemy with all its animation from its sprite sheet
 * \param enemy the enemy to load animation
 */
void initEnemyAnimation(Enemy *enemy);

/**
 * \brief Create a map.
 *
 * \return The array on the map, in order to use it.
 */
Map** initMap();

#endif /* __gameEngine_H__ */

