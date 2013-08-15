#ifndef __map_H__
#define __map_H__

#include <SDL/SDL.h>

/**
 * A position structure, to locate in 2D map
 */
typedef struct{
	int x;	//<! x coordinate
	int y;	//<! y coordinate
}Position;

/**
 * Base element for 2D map, it contain a x,y coordinate system, some flag
 * (if there are tower ...) and a parent element for pathfinding facilities
 */
typedef struct Map{
	int x; int y;		//<! x coordinate //<! y coordinate
	Position parent;	//<! pathfinding facilities
	int hasTower;		//<! tower flag
}Map;

#endif /* __map_H__ */

