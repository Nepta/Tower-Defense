#ifndef __menu_H__
#define __menu_H__

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "interfaces.h"

#define ItemNumbers 4 //!< number of item (tower type) in the menu
#define MaxDescriptionLenght 32 //!< maximum length of the description text

/**
 * Selectable item of the menu (tower to be build) definition (position, sprite...)
 * \attention can be useless
 */
typedef struct{
	SDL_Color color;		//!< color the text will be displayed
	TTF_Font *font;		//!< description text font
	SDL_Surface *sprite; //!< text converted in image to be displayed
}MenuText;

/**
 * Individual item of the menu
 */
typedef struct{
	SDL_Surface *sprite; //!< sprite of an item in the menu
	char* description;	//!< description of an item
	SDL_Rect position;	//!< position of the item in the menu
	int value;				//!< a value for a menu item (like tower price or initial money)
}MenuItem;

/**
 * Menu definition with all item it contain, current item selected and text displayed
 */

struct menu{
	SDL_Surface *background;		//!< background image of the menu
	SDL_Surface *blackTile;			//!< black tile used to "erase" previous selected tower
	MenuItem *currentItem;			//!< the current selected item, which need more description
	MenuText *text;					//!< description text for current selected tower
	int isUpdated;						//!< if the menu need to be redraw
	MenuItem *items[ItemNumbers];	//!< list of item in the menu
};

/**
 * Create a menu and populate it with items
 * \return the menu created
 */
Menu* createMenu();

/**
 * create an item to be inserted into menu
 * \param x x position of the item in the menu
 * \param y y position of the item in the menu
 * \param sprite image resource of the item
 * \return the created menu item
 */
MenuItem* createMenuItem(const char* sprite, const char* description, int x, int y);

/**
 * tell the menu need to be redraw in the next draw loop
 * \param menu menu that need redraw
 */
void updateMenu(Menu *menu);

/**
 * draw a menu with all its item
 * \param menu menu which is draw
 */
void drawMenu(Menu *menu);

/**
 * draw a menu item on a surface
 * \param item item to draw
 * \param surfaceToDraw surface to draw the item
 */
void drawMenuItem(MenuItem *item, SDL_Surface *surfaceToDraw);

/**
 * function called every time user someone click on menu
 * \param menu the menu that is clicked on
 * \param x x position of the click (relative to the menu)
 * \param y y position of the click (relative to the menu)
 */
void clickOnMenu(Interface *interfaces, int x, int y);

/**
 * create a imaged text for a menu item
 * return text as image and some information to blit
 */
MenuText* initTextArea();

/**
 * draw the text of an menu item and it's icon
 * \param text the text of the menu item to be displayed
 * \param currentItem the item to be iconified
 */
void drawMenuText(MenuText *text, MenuItem *currentItem);

#endif /* __menu_H__ */

