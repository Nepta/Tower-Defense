#ifndef __menu_H__
#define __menu_H__

typedef struct{
	SDL_Surface *sprite;
	SDL_Rect position;
}MenuItem;

typedef struct{
	MenuItem currentItem;
	int isUpdated;
	MenuItem items[5];
}Menu;

#endif /* __menu_H__ */

