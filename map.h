#ifndef __map_H__
#define __map_H__

#include <SDL/SDL.h>

typedef struct{
	int x;
	int y;
}Position;

typedef struct Map{
	int x; int y;
	Position parent;
	int hasTower;
}Map;

#endif /* __map_H__ */

