#ifndef __interfaces_H__
#define __interfaces_H__

typedef struct interfaces Interface;
typedef struct fieldInterface FieldInterface;
typedef struct menu Menu;

/**
 * Container for interface in the game (menu, hud ...)
 */
struct interfaces{
	Menu *menu;	//!< the main menu on the right (for now)
	FieldInterface *field; //!< the main zone where enemy move and tower are built
};

#endif /* __interfaces_H__ */

