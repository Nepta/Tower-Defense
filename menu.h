#ifndef __menu_H__
#define __menu_H__

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#define ItemNumbers 3 //!< number of item (tower type) in the menu
#define MaxDescriptionLenght 32

/**
 * Selectable item of the menu (tower to be build) definition (position, sprite...)
 */
typedef struct{
	SDL_Color color;
	TTF_Font *font;
	SDL_Surface *sprite;
}MenuText;

typedef struct{
	SDL_Surface *sprite; //!< sprite of an item in the menu
	char* description;
	SDL_Rect position; //!< position of the item in the menu
}MenuItem;

/**
 * Menu definition with all item it contain, current item selected and text displayed
 */
typedef struct{
	SDL_Surface *background;		//!< background image of the menu
	SDL_Surface *blackTile;			//!< ... because i'm stupid (use the background you morron !)
	MenuItem *currentItem;			//!< the current selected item, which need more description
	MenuText *text;
	int isUpdated;						//!< if the menu need to be redraw
	MenuItem *items[ItemNumbers];	//!< list of item in the menu
}Menu;

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
void clickOnMenu(Menu *menu, int x, int y);

MenuText* initTextArea();
void drawMenuText(MenuText *text, MenuItem *currentItem);

#endif /* __menu_H__ */

